#include "editor.h"
#include <iostream>
#include <utility>

namespace tli_window_manager {
// Scroll
Scroll::Scroll(int scroll_height) : slider_position_{0}, scroll_height_{scroll_height} {}

Scroll::Scroll(const Scroll &other) : scroll_height_{other.scroll_height_}, slider_position_{other.slider_position_} {}

Scroll::Scroll(Scroll &&other) noexcept:
        Box(std::move(other)), slider_position_{std::exchange(other.slider_position_, 0)},
        scroll_height_{std::exchange(other.scroll_height_, 0)} {}

Scroll &Scroll::operator=(Scroll other) noexcept {
    swap(*this, other);
    return *this;
}

void swap(Scroll &first, Scroll &second) {
    using std::swap;
    swap(first.width_, second.width_);
    swap(first.height_, second.height_);
    swap(first.scroll_height_, second.scroll_height_);
    swap(first.slider_position_, second.slider_position_);
}

void Scroll::layout() {
    width_ = 1;
    height_ = scroll_height_;
}

void Scroll::print(Canvas &canvas, int row, int col) const {
    canvas[row][col] = '~';
    canvas[row + height_ - 1][col] = '~';
    for (int i = 1; i < height_ - 1; ++i) {
        canvas[row + i][col] = '|';
    }
    canvas[row + slider_position_ + 1][col] = '*';
}

Box *Scroll::clone() const {
    return new Scroll(*this);
}

void Scroll::set_position(int slider_position) {
    slider_position_ = slider_position;
}

// Text
Text::Text(int width, int height, std::string initial_str) : frame_width_{width}, buffer_{std::move(initial_str)},
                                                             frame_height_{height}, cursor_position_{0}, index_{0} {}

Text::Text(const Text &other) : frame_width_{other.frame_width_}, frame_height_{other.frame_height_},
                                cursor_position_{other.cursor_position_}, index_{other.index_},
                                buffer_{other.buffer_} {}

Text::Text(Text &&other) noexcept: Box(std::move(other)), cursor_position_{std::exchange(other.cursor_position_, 0)},
                                   index_{std::exchange(other.index_, 0)}, buffer_{std::move(other.buffer_)} {}

Text &Text::operator=(Text other) noexcept {
    swap(*this, other);
    return *this;
}

void swap(Text &first, Text &second) {
    using std::swap;
    swap(first.frame_width_, second.frame_width_);
    swap(first.frame_height_, second.frame_height_);
    swap(first.width_, second.width_);
    swap(first.height_, second.height_);
    swap(first.cursor_position_, second.cursor_position_);
    swap(first.index_, second.index_);
    swap(first.buffer_, second.buffer_);
}

void Text::layout() {
    width_ = frame_width_;
    height_ = frame_height_;
}

void Text::print(Canvas &canvas, int row, int col) const {
    int current_row = 0;
    int current_col = 0;
    for (int i = index_; i < buffer_.size(); ++i) {
        if (i == cursor_position_) {
            canvas[row + current_row][col + current_col] = '|';
            current_col++;
        }

        if (buffer_[i] == '\n') {
            current_row++;
            current_col = 0;
            if (current_row == height_) {
                break;
            }
        } else {
            canvas[row + current_row][col + current_col] = buffer_[i];
            current_col++;
        }
    }
    if (cursor_position_ == buffer_.size() && current_row < height_) {
        canvas[row + current_row][col + current_col] = '|';
    }
}

void Text::move_cursor_left() {
    if (cursor_position_ > 0) {
        if (cursor_position_ == index_) {

        }
        --cursor_position_;
    }
}

void Text::move_cursor_up() {
    if (cursor_position_ == 0) { return; }

    int i = cursor_position_;
    do {
        --i;
    } while (i != 0 && buffer_[i] != '\n');
    if (i == 0) {
        cursor_position_ = 0;
        return;
    }

    int j = i;
    do {
        --j;
    } while (j != 0 && buffer_[j] != '\n');

//    ASSERT(cursor_position_ - i, current_position().second);
    if (i - j <= cursor_position_ - i) {
        cursor_position_ = i;
    } else {
        cursor_position_ = (cursor_position_ - i) + j;
    }
}

void Text::move_cursor_right() {
    if (cursor_position_ != buffer_.size()) {
        ++cursor_position_;
    }
}

void Text::move_cursor_down() {
    int i = cursor_position_;
    int size = buffer_.size();
    while (i != size && buffer_[i] != '\n') { ++i; }
    if (i == size) {
        cursor_position_ = i;
        return;
    }

    int j = i;
    do {
        ++j;
    } while (j != size && buffer_[j] != '\n');
    cursor_position_ = i + 1 + std::min(current_position().second, j - i - 1);
}

void Text::move_cursor_to_pos(int row, int col) {}

void Text::decrease_index() {}

void Text::increase_index() {}

Position Text::current_position() const {
    int row = 0;
    for (int i = index_; i < cursor_position_; ++i) {
        if (buffer_[i] == '\n') {
            ++row;
        }
    }

    int col = 0;
    for (int i = cursor_position_; i > index_; --i) {
        if (buffer_[i] != '\n') {
            ++col;
        } else {
            break;
        }
    }
    return std::make_pair(row, col);
}

Box *Text::clone() const {
    return new Text(*this);
}

void Text::set_position(int cursor_position) {
    cursor_position_ = cursor_position;
}

void Text::insert_new_char(char c) {
    buffer_.insert(cursor_position_, 1, c);
}

int Text::cursor_position() const {
    return cursor_position_;
}

// TextEditor
TextEditor::TextEditor(int width, int height, std::string initial_string) :
        text(width - 1, height, std::move(initial_string)), scroll(height),
        canvas(height + 2, std::vector<char>(width + 2, ' ')), insert_mode_{false} {
}

void TextEditor::handle_button_press(char button) {
    if (button == '~') {
        insert_mode_ = !insert_mode_;
        return;
    }

    if (insert_mode_) {
        text.insert_new_char(button);
        text.move_cursor_right();
    } else {
        switch (button) {
            case 'j': {
                text.move_cursor_down();
                break;
            }
            case 'k': {
                text.move_cursor_up();
                break;
            }
            case 'h': {
                text.move_cursor_left();
                break;
            }
            case 'l': {
                text.move_cursor_right();
                break;
            }
            default: {
                break;
            }
        }
    }
}

void TextEditor::update() {
    for (auto &row : canvas) {
        row.assign(row.size(), ' ');
    }

    TableBox table(1, 2);
    table.add(&text, 0, 0);
    table.add(&scroll, 0, 1);

    FrameBox frame(&table);
    std::cout.flush();
    std::cout << "\x1B[2J\x1B[H";
    show_box(canvas, &frame, 0, 0);
}

int TextEditor::get_cursor_position() const {
    return text.cursor_position();
}

void TextEditor::handle_scroll(int position) {
    scroll.set_position(position);
}

TextEditor::~TextEditor() = default;
}
