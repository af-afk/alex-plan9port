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

int
zeroxneedslock(Text *et, Text *t)
{
	/* winlock locks every window that shares the body File. */
	if(t==nil || t->w==nil)
		return FALSE;
	if(et==nil || et->w==nil)
		return TRUE;
	return t->w->body.file != et->w->body.file;
}
