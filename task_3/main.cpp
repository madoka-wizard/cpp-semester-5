#include "box.h"
#include "editor.h"
#include "utils.h"
#include <vector> // std::vector
#include <unordered_map> // std::unordered_map
#include <iostream>

namespace {
void test_task_1() {
    using namespace tli_window_manager;
    Canvas canvas(15, std::vector<char>(15, ' '));

    std::unordered_map<char, CharBox> alphabet;
    for (char i = 'a'; i <= 'z'; ++i) {
        alphabet[i] = CharBox(i);
    }

    TableBox tBox1(2, 2);
    tBox1.add(&alphabet['a'], 0, 0);
    tBox1.add(&alphabet['b'], 0, 1);
    tBox1.add(&alphabet['c'], 1, 0);
    tBox1.add(&alphabet['d'], 1, 1);

    FrameBox fBox(&tBox1);

    TableBox tBox2(1, 5);
    tBox2.add(&alphabet['f'], 0, 0);
    tBox2.add(&alphabet['g'], 0, 1);
    tBox2.add(&alphabet['h'], 0, 2);
    tBox2.add(&alphabet['i'], 0, 3);
    tBox2.add(&alphabet['j'], 0, 4);

    TableBox tBox3(1, 5);
    tBox3.add(&alphabet['a'], 0, 0);
    tBox3.add(&alphabet['b'], 0, 1);
    tBox3.add(&alphabet['c'], 0, 2);
    tBox3.add(&alphabet['d'], 0, 3);
    tBox3.add(&alphabet['e'], 0, 4);

    TableBox tBox4(2, 7);
    tBox4.add(&alphabet['a'], 0, 0);
    tBox4.add(&alphabet['b'], 0, 1);
    tBox4.add(&alphabet['c'], 0, 2);
    tBox4.add(&alphabet['d'], 0, 3);
    tBox4.add(&alphabet['e'], 0, 4);
    tBox4.add(&alphabet['f'], 1, 0);
    tBox4.add(&alphabet['g'], 1, 1);
    tBox4.add(&alphabet['h'], 1, 2);
    tBox4.add(&alphabet['i'], 1, 3);
    tBox4.add(&alphabet['j'], 1, 4);
    tBox4.add(&alphabet['k'], 1, 5);
    tBox4.add(&alphabet['l'], 1, 6);

    TableBox tBox(2, 2);
    tBox.add(&fBox, 0, 0);
    tBox.add(&tBox2, 0, 1);
    tBox.add(&tBox3, 1, 0);
    tBox.add(&tBox4, 1, 1);

    show_box(canvas, &tBox, 2, 3);
}

void test_task_2_1() {
    using namespace tli_window_manager;
    TextEditor editor(30, 10, "ab\nab\n");
    editor.handle_button_press('j');
    editor.handle_button_press('j');
    editor.handle_button_press('k');
    ASSERT(editor.get_cursor_position(), 3);
}

void test_task_2_2() {
    using namespace tli_window_manager;
    TextEditor editor(30, 10, "ab\nab\n\n");
    editor.handle_button_press('j');
    editor.handle_button_press('j');
    editor.handle_button_press('j');
    editor.handle_button_press('k');
    ASSERT(editor.get_cursor_position(), 6);
}

void test_task_2_3() {
    using namespace tli_window_manager;
    TextEditor editor(30, 10, "");
    editor.handle_button_press('k');
    ASSERT(editor.get_cursor_position(), 0);
    editor.handle_button_press('j');
    ASSERT(editor.get_cursor_position(), 0);
}

void test_task_2_4() {
    using namespace tli_window_manager;
    TextEditor editor(30, 10, "\n");
    editor.handle_button_press('l');
    editor.handle_button_press('l');
    editor.handle_button_press('l');
    ASSERT(editor.get_cursor_position(), 1);
}

void test_task_2_5() {
    using namespace tli_window_manager;
    TextEditor editor(30, 10, "\n");
    editor.handle_button_press('l');
    editor.handle_button_press('l');
    editor.handle_button_press('l');
    editor.handle_button_press('k');
    ASSERT(editor.get_cursor_position(), 0);
}
}

int main() {
    test_task_1();
//    std::ios_base::sync_with_stdio(false);

    test_task_2_1();
    test_task_2_2();
    test_task_2_3();
    test_task_2_4();
    test_task_2_5();
    using namespace tli_window_manager;
    TextEditor editor(30, 10, "\n");
    editor.update();
    for (char c; std::cin.get(c);) {
        editor.handle_button_press(c);
        editor.update();
    }
    return EXIT_SUCCESS;
}
