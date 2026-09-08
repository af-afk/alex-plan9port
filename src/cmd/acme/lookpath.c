#include <u.h>
#include <libc.h>

/*
 * Return the host path used to decide whether an Acme filename exists.
 * Keep the displayed/event filename unchanged; completeprefix is only the
 * local filesystem root for rooted names in this window.
 */
char*
lookaccesspath(char *completeprefix, char *name)
{
	char *p;
	int nprefix, nname;

	nprefix = completeprefix == nil ? 0 : strlen(completeprefix);
	while(nprefix > 1 && completeprefix[nprefix-1] == '/')
		nprefix--;
	nname = strlen(name);
	p = malloc(nprefix+nname+1);
	if(p == nil)
		sysfatal("lookaccesspath: out of memory");
	if(nprefix > 0 && name[0] == '/'){
		memmove(p, completeprefix, nprefix);
		memmove(p+nprefix, name, nname+1);
	}else
		memmove(p, name, nname+1);
	return p;
}
