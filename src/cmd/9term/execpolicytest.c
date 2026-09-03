#include <u.h>
#include <libc.h>

int winexecsendback(int, int, uint, uint, int, uint, uint);

static void
check(int got, int want, char *name)
{
	if(got != want)
		sysfatal("%s: got %d, want %d", name, got, want);
}

void
main(void)
{
	check(winexecsendback(1, 1, 0, 0, 1, 10, 20), 1,
		"built-in acme command");
	check(winexecsendback(0, 1, 5, 5, 1, 10, 300), 0,
		"long expanded tag text");
	check(winexecsendback(0, 1, 10, 300, 0, 0, 0), 0,
		"long selected tag text");
	check(winexecsendback(0, 1, 5, 5, 0, 0, 0), 1,
		"empty tag execution");
	check(winexecsendback(0, 0, 5, 5, 0, 0, 0), 0,
		"body execution");
	exits(nil);
}
