#include <curses.h>

int main(void) {
	initscr();

	move(LINES/2, COLS/3);
	addstr("Hello!");
	getch(); // Функция ввода с экрана; автоматически изначально обновляет экран для показа

	endwin();
	return 0;
}

