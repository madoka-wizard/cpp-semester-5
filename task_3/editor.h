#pragma once

#include <string>
#include "box.h"

namespace tli_window_manager {
class Observer {
public:
    virtual void set_position(int) = 0;
};

class Scroll : public Box, public Observer {
public:
    explicit Scroll(int scroll_height);

    Scroll(const Scroll &other);

    Scroll(Scroll &&other) noexcept;

    Scroll &operator=(Scroll other) noexcept;

    friend void swap(Scroll &first, Scroll &second);

    void layout() override;

    void print(Canvas &canvas, int row, int col) const override;

    Box *clone() const override;

    void set_position(int slider_position) override;

private:
    int scroll_height_;
    int slider_position_;
};

class Text : public Observer, public Box {
public:
    Text(int width, int height, std::string initial_str = "");

    Text(const Text &other);

    Text(Text &&other) noexcept;

    Text &operator=(Text other) noexcept;

    friend void swap(Text &first, Text &second);

    void layout() override;

    void print(Canvas &canvas, int row, int col) const override;

    void move_cursor_left();

    void move_cursor_up();

    void move_cursor_right();

    void move_cursor_down();

    void move_cursor_to_pos(int row, int col);

    void decrease_index();

    void increase_index();

    Position current_position() const;

    void insert_new_char(char c);

    Box *clone() const override;

    void set_position(int cursor_position) override;

    int cursor_position() const;

private:
    std::string buffer_;
    int frame_width_{};
    int frame_height_{};
    int cursor_position_;
    int index_;
};

class TextEditor {
public:
    TextEditor(int width, int height, std::string initial_string = "");

    void handle_scroll(int position);

    void handle_button_press(char button);

    void update();

    ~TextEditor();

    int get_cursor_position() const;

private:
    bool insert_mode_;
    Canvas canvas;
    Text text;
    Scroll scroll;
};
} // namespace tli_window_manager
