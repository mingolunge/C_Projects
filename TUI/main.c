#include "ncurses.h"

int main() {
    initscr();              // Start ncurses mode
    cbreak();               // Disable line buffering
    noecho();               // Don't echo typed characters
    keypad(stdscr, TRUE);   // Enable function keys & arrows

    printw("Hello from ncurses! Press any key to exit.");
    refresh();              // Draw to screen
    mvprintw(5, 10, "Text at row 5, col 10");
    WINDOW *win = newwin(10, 20, 3, 3);
    box(win, 0, 0);
    wrefresh(win);

    getch();                // Wait for key
    endwin();               // End ncurses mode

    return 0;
}
