#include <u.h>
#include <libc.h>

int indentselect(Rune*, uint, uint, uint, uint*, uint*);

static void
checktab(char *name, char *text, uint q, uint tabstop, int wantok, uint want0, uint want1)
{
	Rune *s;
	uint n, got0, got1;
	int gotok;

	s = runesmprint("%s", text);
	n = runestrlen(s);
	got0 = got1 = ~0;
	gotok = indentselect(s, n, q, tabstop, &got0, &got1);
	free(s);
	if(gotok != wantok)
		sysfatal("indentselecttest: %s: got ok %d; want %d", name, gotok, wantok);
	if(gotok && (got0 != want0 || got1 != want1))
		sysfatal("indentselecttest: %s: got %ud,%ud; want %ud,%ud", name, got0, got1, want0, want1);
}

static void
check(char *name, char *text, uint q, int wantok, uint want0, uint want1)
{
	checktab(name, text, q, 8, wantok, want0, want1);
}

void
main(void)
{
	check("siblings and children", "top\n\ta\n\tb\n\t\tc\n\td\nend\n", 9, 1, 4, 17);
	check("nested level", "top\n\ta\n\tb\n\t\tc\n\t\td\n\te\nend\n", 13, 1, 10, 18);
	check("internal blank line", "top\n  a\n\n  b\nend\n", 11, 1, 4, 13);
	check("exclude boundary blanks", "top\n\n  a\n  b\n\nend\n", 10, 1, 5, 13);
	check("spaces and tabs by columns", "top\n        a\n\tb\nend\n", 15, 1, 4, 17);
	checktab("configured tab width", "top\n    a\n\tb\nend\n", 11, 4, 1, 4, 13);
	check("CRLF blank line", "top\r\n  a\r\n\r\n  b\r\nend\r\n", 14, 1, 5, 17);
	check("last line without newline", "top\n  a\n  b", 11, 1, 4, 11);
	check("top level selects file", "a\n  child\nb\n", 0, 1, 0, 12);
	check("indented blank current line", "hello\n  world\n  this\n  is\n  \n", 28, 1, 6, 29);
	check("tab-indented example", "hello\n\tworld\n\tthis\n\tis\n\tme", 26, 1, 6, 26);
	check("out of range", "a\n", 3, 0, 0, 0);
	checktab("invalid tab width", "a\n", 0, 0, 0, 0, 0);
	exits(nil);
}
