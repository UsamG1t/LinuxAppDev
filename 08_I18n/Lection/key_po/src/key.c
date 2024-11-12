#include <ncurses.h>
#include <unistd.h>
#include <error.h>
#include <libintl.h>
#include <locale.h>
#include "config.h"

#ifndef DX
#define DX 3
#endif

#define _(STRING) gettext(STRING)

int main(void) {
        WINDOW *win;
        int c = 0;

        setlocale (LC_ALL, "");
        bindtextdomain (PACKAGE, LOCALEDIR);
        textdomain (PACKAGE);
        if (!isatty(0))
                error(1, 0, _("Not a terminal"));
        initscr();
        noecho();
        cbreak();
        printw("%s (%s)", PACKAGE_STRING, PACKAGE_BUGREPORT);
        refresh();

        win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
#ifdef KEYPAD
        keypad(win, TRUE);
#else
        keypad(win, FALSE);
#endif
        scrollok (win, TRUE);
        do {
                wprintw(win, _("  Key: %d, Name: %s\n"), c, keyname(c));
                box(win, 0, 0);
                wrefresh(win);
        } while((c = wgetch(win)) != 27);

        endwin();
	return 0;
}
