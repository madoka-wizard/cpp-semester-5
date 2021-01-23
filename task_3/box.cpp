#include "box.h"
#include <iostream>

namespace tli_window_manager {
// Box
Box::Box() : width_{0}, height_{0} {}

Box::Box(Box &&other) noexcept:
        width_{std::exchange(other.width_, 0)}, height_{std::exchange(other.height_, 0)} {}

int Box::width() const {
    return width_;
}

int Box::height() const {
    return height_;
}

Box::~Box() = default;

// CharBox
CharBox::CharBox(char data) : data_{data} {}

CharBox::CharBox(const CharBox &other) : CharBox(other.data_) {}

CharBox::CharBox(CharBox &&other) noexcept: Box(std::move(other)), data_{std::exchange(other.data_, 0)} {}

CharBox &CharBox::operator=(CharBox other) noexcept {
    swap(*this, other);
    return *this;
}

void swap(CharBox &first, CharBox &second) {
    using std::swap;
    swap(first.width_, second.width_);
    swap(first.height_, second.height_);
    swap(first.data_, second.data_);
}

Box *CharBox::clone() const {
    return new CharBox(*this);
}

void CharBox::layout() {
    width_ = 1;
    height_ = 1;
}

void CharBox::print(Canvas &canvas, int row, int col) const {
    canvas[row][col] = data_;
}

CharBox::~CharBox() = default;

// TableBox
TableBox::TableBox(int rows, int cols) : rows_{rows}, cols_{cols}, table_(rows, std::vector<std::pair<Box *, Position>>(
        cols, std::make_pair(nullptr, std::make_pair(0, 0))
)) {}

TableBox::TableBox(const TableBox &other) : TableBox(other.rows_, other.cols_) {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (other.table_[i][j].first) {
                table_[i][j].first = other.table_[i][j].first->clone();
            }
        }
    }
}

TableBox::TableBox(TableBox &&other) noexcept:
        Box(std::move(other)), rows_{std::exchange(other.rows_, 0)}, cols_{std::exchange(other.cols_, 0)} {
    table_.swap(other.table_);
}

TableBox &TableBox::operator=(TableBox other) noexcept {
    swap(*this, other);
    return *this;
}

void swap(TableBox &first, TableBox &second) {
    using std::swap;
    swap(first.width_, second.width_);
    swap(first.height_, second.height_);
    swap(first.rows_, second.rows_);
    swap(first.cols_, second.cols_);
    first.table_.swap(second.table_);
}

void TableBox::layout() {
    std::vector<int> row_sizes(rows_, 0);
    std::vector<int> col_sizes(cols_, 0);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (table_[i][j].first) {
                table_[i][j].first->layout();
                row_sizes[i] = std::max(row_sizes[i], table_[i][j].first->height());
                col_sizes[j] = std::max(col_sizes[j], table_[i][j].first->width());
            }
        }
    }

    int current_col = 0;
    int current_row = 0;
    for (int i = 0; i < rows_; ++i) {
        current_col = 0;
        for (int j = 0; j < cols_; ++j) {
            if (table_[i][j].first) {
                table_[i][j].second = std::make_pair(current_row, current_col);
            }
            current_col += col_sizes[j];
        }
        current_row += row_sizes[i];
    }

//    for (int i = 0; i < rows_; ++i) {
//        for (int j = 0; j < cols_; ++j) {
//            std::cout << '(' << table_[i][j].second.first << ", " << table_[i][j].second.second << ") ";
//        }
//        std::cout << '\n';
//    }
//    std::cout << '\n';

    width_ = current_col;
    height_ = current_row;
}

void TableBox::print(Canvas &canvas, int row, int col) const {
    for (const auto &current_row : table_) {
        for (const auto &[box, pos] : current_row) {
            if (box) {
                box->print(canvas, pos.first + row, pos.second + col);
            }
        }
    }
}

Box *TableBox::clone() const {
    return new TableBox(*this);
}

void TableBox::add(Box *box, int row, int col) {
    delete table_[row][col].first;
    table_[row][col].first = box->clone();
}

TableBox::~TableBox() {
    for (const auto &row : table_) {
        for (auto &[box, pos] : row) {
            delete box;
        }
    }
}

// FrameBox
FrameBox::FrameBox(Box *box) : box_{box->clone()} {}

FrameBox::FrameBox(const FrameBox &other) : FrameBox(other.box_) {}

FrameBox::FrameBox(FrameBox &&other) noexcept: Box(std::move(other)), box_{std::exchange(other.box_, nullptr)} {}

FrameBox &FrameBox::operator=(FrameBox other) noexcept {
    swap(*this, other);
    return *this;
}

void swap(FrameBox &first, FrameBox &second) {
    using std::swap;
    swap(first.width_, second.width_);
    swap(first.height_, second.height_);
    swap(first.box_, second.box_);
}

void FrameBox::layout() {
    box_->layout();
    width_ = box_->width() + 2;
    height_ = box_->height() + 2;
}

void FrameBox::print(Canvas &canvas, int row, int col) const {
    canvas[row][col] = '+';
    canvas[row + height_ - 1][col] = '+';
    canvas[row + height_ - 1][col + width_ - 1] = '+';
    canvas[row][col + width_ - 1] = '+';
    for (int i = 1; i < width_ - 1; ++i) {
        canvas[row][col + i] = '-';
        canvas[row + height_ - 1][col + i] = '-';
    }
    for (int j = 1; j < height_ - 1; ++j) {
        canvas[row + j][col] = '|';
        canvas[row + j][col + width_ - 1] = '|';
    }
    box_->print(canvas, row + 1, col + 1);
}

Box *FrameBox::clone() const {
    return new FrameBox(*this);
}

FrameBox::~FrameBox() {
    delete box_;
}

// Utilities
void show_box(Canvas &canvas, Box *box, int row, int col) {
    box->layout();
    box->print(canvas, row, col);
    for (const auto &current_row : canvas) {
        for (auto c : current_row) {
            std::cout << c;
        }
        std::cout << '\n';
    }
}
} // namespace tli_window_manager
