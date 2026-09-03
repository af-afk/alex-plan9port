#include <u.h>
#include <libc.h>
#include <draw.h>
#include <thread.h>
#include <cursor.h>
#include <mouse.h>
#include <keyboard.h>
#include <frame.h>
#include <fcall.h>
#include <plumb.h>
#include <libsec.h>
#include "dat.h"
#include "fns.h"
#undef exits

static void
check(int ok, char *msg)
{
	if(!ok)
		sysfatal("zeroxlocktest: %s", msg);
}

void
main(void)
{
	File shared, other;
	Window source, clone, unrelated;
	Text et, selected;

	memset(&shared, 0, sizeof shared);
	memset(&other, 0, sizeof other);
	memset(&source, 0, sizeof source);
	memset(&clone, 0, sizeof clone);
	memset(&unrelated, 0, sizeof unrelated);
	memset(&et, 0, sizeof et);
	memset(&selected, 0, sizeof selected);

	source.body.file = &shared;
	clone.body.file = &shared;
	unrelated.body.file = &other;

	et.w = &clone;
	selected.w = &source;
	check(!zeroxneedslock(&et, &selected), "clone of locked file would be relocked");

	selected.w = &unrelated;
	check(zeroxneedslock(&et, &selected), "different file would not be locked");

	selected.w = nil;
	check(!zeroxneedslock(&et, &selected), "text without a window would be locked");

	et.w = nil;
	selected.w = &source;
	check(zeroxneedslock(&et, &selected), "selected file needs locking without an execution window");

	exits(nil);
}
