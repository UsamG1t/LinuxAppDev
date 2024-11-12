#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"

int main(int argc, char *argv[])
{
	int i;
	char *dir;

	dir = dirname(realpath(argv[0], NULL));
	setlocale (LC_ALL, "");
	bindtextdomain ("ahello", LOCALE_PATH);
	textdomain ("ahello");

	/* Simple text */
	puts(_("Hello World\n"));

	for(i=0; i<6; i++)
		/* Plural example */
		printf(ngettext("Hello, %d World\n", "Hello, %d Worlds\n", i), i);

	return 0;
}