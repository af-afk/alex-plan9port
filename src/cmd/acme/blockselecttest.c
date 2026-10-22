#include <u.h>
#include <libc.h>

int blockselect(Rune*, uint, uint, uint, uint*, uint*);

static void
check(char *name, char *text, uint q0, uint q1, int wantok, uint want0, uint want1)
{
	Rune *s;
	uint n, got0, got1;
	int gotok;

	s = runesmprint("%s", text);
	n = runestrlen(s);
	got0 = got1 = ~0;
	gotok = blockselect(s, n, q0, q1, &got0, &got1);
	free(s);
	if(gotok != wantok)
		sysfatal("blockselecttest: %s: got ok %d; want %d", name, gotok, wantok);
	if(gotok && (got0 != want0 || got1 != want1))
		sysfatal("blockselecttest: %s: got %ud,%ud; want %ud,%ud", name, got0, got1, want0, want1);
}

void
main(void)
{
	check("parentheses", "x(a + b)y", 4, 4, 1, 2, 7);
	check("brackets", "x[a + b]y", 4, 4, 1, 2, 7);
	check("braces", "x{a + b}y", 4, 4, 1, 2, 7);
	check("innermost mixed block", "f({a[b]c})", 5, 5, 1, 5, 6);
	check("repeat selects parent block", "f({a[b]c})", 5, 6, 1, 3, 8);
	check("repeat selects next parent block", "f({a[b]c})", 3, 8, 1, 2, 9);
	check("repeat at outermost block", "f({a[b]c})", 2, 9, 0, 0, 0);
	check("repeat through same delimiters", "f((x))", 3, 4, 1, 2, 5);
	check("outer block after inner", "f({a[b]c})", 8, 8, 1, 3, 8);
	check("selection inside block", "x(foo[bar]baz)y", 7, 8, 1, 6, 9);
	check("cursor after opening", "x()y", 2, 2, 1, 2, 2);
	check("cursor outside", "x(a)y", 5, 5, 0, 0, 0);
	check("unclosed block", "x(a", 3, 3, 0, 0, 0);
	check("quasiquotes", "x`a + b`y", 4, 4, 1, 2, 7);
	check("double quotes", "x\"a + b\"y", 4, 4, 1, 2, 7);
	check("single quotes", "x'a + b'y", 4, 4, 1, 2, 7);
	check("escaped double quote", "x\"a\\\"b\"y", 5, 5, 1, 2, 6);
	check("escaped single quote", "x'a\\'b'y", 5, 5, 1, 2, 6);
	check("escaped quasiquote", "x`a\\`b`y", 5, 5, 1, 2, 6);
	check("single quote after apostrophe", "don't 'quote'", 9, 9, 1, 7, 12);
	check("quote expands to parent block", "f(\"x\")", 3, 4, 1, 2, 5);
	check("cursor outside quotes", "x\"a\"y", 5, 5, 0, 0, 0);
	check("unclosed quote", "x\"a", 3, 3, 0, 0, 0);
	exits(nil);
}
