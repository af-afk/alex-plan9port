#include <u.h>
#include <libc.h>

int x11controlkey(int, int);

static void
check(int got, int want, char *name)
{
	if(got != want)
		sysfatal("x11controltest: %s: got %#ux; want %#ux", name, got, want);
}

void
main(void)
{
	check(x11controlkey(' ', 1), 0, "control-space");
	check(x11controlkey('@', 1), 0, "control-@");
	check(x11controlkey('a', 1), 1, "control-a");
	check(x11controlkey(' ', 0), ' ', "plain space");
	exits(nil);
}
