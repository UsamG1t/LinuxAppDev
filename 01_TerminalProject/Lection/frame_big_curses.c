#include <curses.h>
#include <locale.h>

int main(void) {
    WINDOW* win;
    WINDOW* frame;
    char c = 0;

    setlocale(LC_ALL, "");

    initscr();
    noecho();
    cbreak();

    move(4, 10);
    printw("window:");
    refresh();

    frame = newwin(LINES - 8, COLS - 18, 4, 9);
    box(frame, 0, 0);
    mvwaddstr(frame, 0, (int)((COLS - 25) / 2), "Рамка");
    wrefresh(frame);

    win = newwin(LINES - 10, COLS - 20, 5, 10);
    keypad(win, TRUE);
    scrollok(win, TRUE);

    while((c = wgetch(win)) != 27) {
        wprintw(win, "  %d: %s\n", c, keyname(c));
        // box(win, 0, 0);
        wrefresh(win);
    }

    delwin(win);
    endwin();
    return 0;
}
