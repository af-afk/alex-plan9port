#include <u.h>
#include <libc.h>

char *expandenvpath(char*);

static void
checkexpand(char *path, char *want)
{
	char *got;

	got = expandenvpath(path);
	if(strcmp(got, want) != 0)
		sysfatal("envexpandtest: path %s: got %s; want %s", path, got, want);
	free(got);
}

void
main(void)
{
	char *got, *longpath;

	putenv("HOME", "/tmp");
	putenv("ACME_COMPLETE_HOME", "/tmp/acme-home");
	checkexpand("$HOME/Down", "/tmp/Down");
	checkexpand("$ACME_COMPLETE_HOME/Down", "/tmp/acme-home/Down");
	checkexpand("${ACME_COMPLETE_HOME}/Down", "/tmp/acme-home/Down");
	checkexpand("prefix/$ACME_COMPLETE_HOME/Down", "prefix//tmp/acme-home/Down");
	checkexpand("plain/path", "plain/path");
	checkexpand("$ACME_COMPLETE_UNSET/Down", "$ACME_COMPLETE_UNSET/Down");

	longpath = malloc(64*1024+2);
	memset(longpath, 'a', 64*1024+1);
	longpath[64*1024+1] = 0;
	got = expandenvpath(longpath);
	if(got != nil)
		sysfatal("envexpandtest: oversized path was accepted");
	free(longpath);
	exits(nil);
}
