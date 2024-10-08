#include <curses.h>
#include <locale.h>

int main(void) {
	WINDOW* win;
	char c = 0;

	setlocale(LC_ALL, "");

	initscr();
	noecho();
	cbreak();

	move(4, 10);
	printw("window:"); // TODO: переделать пример - мы рисуем бокс внутри окна и перекрывает первую строку
	refresh();

	win = newwin(LINES - 10, COLS - 20, 5, 10);
	keypad(win, TRUE);
	scrollok(win, TRUE);

	box(win, 0, 0); // TODO: Переделать пример: у нас скроллится box
	wmove(win, 1, 1);

	while((c = wgetch(win)) != 27) {
		wprintw(win, "  %d: %s\n", c, keyname(c));
		box(win, 0, 0);
		wrefresh(win);
	}

	delwin(win);
	endwin();
	return 0;
}
