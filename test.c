#include <ncurses.h>

int main() {
    initscr();          // Initialize ncurses
    raw();              // Disable line buffering
    keypad(stdscr, TRUE); // Enable special key codes

    nodelay(stdscr, TRUE); // Set getch to non-blocking mode

    printw("Press keys. Press 'q' to quit.\n");

    int ch;
    while ((ch = getch()) != 'q') {
        if (ch != ERR) {
            // A key is pressed
            printw("Key pressed: %c (%d)\n", ch, ch);
        } else {
            // No key pressed
        }
        refresh();
    }

    endwin(); // End ncurses

    return 0;
}
