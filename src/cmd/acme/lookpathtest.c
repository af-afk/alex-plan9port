#include <u.h>
#include <libc.h>

char *lookaccesspath(char*, char*);

static void
checkpath(char *prefix, char *name, char *want)
{
	char *got;

	got = lookaccesspath(prefix, name);
	if(strcmp(got, want) != 0)
		sysfatal("lookpathtest: prefix %s name %s: got %s; want %s", prefix == nil ? "<nil>" : prefix, name, got, want);
	free(got);
}

void
main(void)
{
	checkpath("/n/goblin", "/usr/local/sbin/begin-rfqhub.sh", "/n/goblin/usr/local/sbin/begin-rfqhub.sh");
	checkpath("/n/goblin", "relative/file", "relative/file");
	checkpath(nil, "/usr/local/sbin/begin-rfqhub.sh", "/usr/local/sbin/begin-rfqhub.sh");
	exits(nil);
}
