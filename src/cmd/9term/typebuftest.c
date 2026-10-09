#include <u.h>
#include <libc.h>

int winrunebyteoffset(char*, int, uint);

static void
check(int got, int want, char *name)
{
	if(got != want)
		sysfatal("%s: got %d, want %d", name, got, want);
}

void
main(void)
{
	char mixed[] = "a€b";

	check(winrunebyteoffset(mixed, strlen(mixed), 0), 0,
		"start of buffer");
	check(winrunebyteoffset(mixed, strlen(mixed), 1), 1,
		"after ASCII rune");
	check(winrunebyteoffset(mixed, strlen(mixed), 2), 4,
		"after multibyte rune");
	check(winrunebyteoffset(mixed, strlen(mixed), 3), 5,
		"end of buffer");
	check(winrunebyteoffset(mixed, strlen(mixed), 4), -1,
		"past end of buffer");
	exits(nil);
}
