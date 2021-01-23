#pragma once

#include <utility> // std::swap, std::pair, std::make_pair
#include <vector> // std::vector
#include <algorithm> // std::max

namespace tli_window_manager { // TLI = Text Line Interface
using Canvas = std::vector<std::vector<char>>;
template<typename T> using Matrix = std::vector<std::vector<T>>;
using Position = std::pair<int, int>; // pos.first - row number, pos.second - column number

class Box {
public:
    Box();

    Box(Box &&other) noexcept;

    int width() const;

    int height() const;

    virtual void layout() = 0;

    virtual void print(Canvas &canvas, int row, int col) const = 0;

    virtual Box *clone() const = 0;

    virtual ~Box() = 0;

protected:
    int width_;
    int height_;
};

class CharBox : public Box {
public:
    explicit CharBox(char data = '\0');

    CharBox(const CharBox &other);

    CharBox(CharBox &&other) noexcept;

    CharBox &operator=(CharBox other) noexcept;

    friend void swap(CharBox &first, CharBox &second);

    Box *clone() const override;;

    void layout() override;

    void print(Canvas &canvas, int row, int col) const override;;

    ~CharBox() override;

private:
    char data_;
};

class TableBox : public Box {
public:
    TableBox(int rows, int cols);

    TableBox(const TableBox &other);

    TableBox(TableBox &&other) noexcept;

    TableBox &operator=(TableBox other) noexcept;

    friend void swap(TableBox &first, TableBox &second);

    void layout() override;

    void print(Canvas &canvas, int row, int col) const override;;

    Box *clone() const override;;

    void add(Box *box, int row, int col);

    ~TableBox() override;

private:
    int rows_;
    int cols_;
    Matrix<std::pair<Box *, Position>> table_;
};

class FrameBox : public Box {
public:
    explicit FrameBox(Box *box);;

    FrameBox(const FrameBox &other);

    FrameBox(FrameBox &&other) noexcept;

    FrameBox &operator=(FrameBox other) noexcept;

    friend void swap(FrameBox &first, FrameBox &second);

    void layout() override;

    void print(Canvas &canvas, int row, int col) const override;;

    Box *clone() const override;;

    ~FrameBox() override;;

private:
    Box *box_;
};

void show_box(Canvas &canvas, Box *box, int row, int col);
} // namespace tli_window_manager
