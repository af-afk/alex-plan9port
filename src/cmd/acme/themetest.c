#include <u.h>
#include <libc.h>
#include "theme.h"
#undef exits

static void
check(int ok, char *msg)
{
	if(!ok)
		sysfatal("themetest: %s", msg);
}

void
main(void)
{
	Theme *t;

	check(!themedark(), "theme does not start in day mode");
	check(themeiskey(0x1c), "control-backslash is not the theme key");
	check(!themeiskey('\\'), "plain backslash is the theme key");

	t = themetoggle();
	check(themedark(), "first toggle did not enable night mode");
	check(t->tag[ThemeBack] == 0x242a30ff, "wrong night tag background");
	check(t->tag[ThemeText] == 0xe8e6e3ff, "wrong night tag text");
	check(t->body[ThemeBack] == 0x1e1e1eff, "wrong night body background");
	check(t->body[ThemeText] == 0xe8e6e3ff, "wrong night body text");

	t = themetoggle();
	check(!themedark(), "second toggle did not restore day mode");
	check(t == nil, "day mode unexpectedly returned a solid palette");

	exits(nil);
}
