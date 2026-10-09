#include <u.h>
#include <libc.h>

int
winrunebyteoffset(char *s, int nb, uint nr)
{
	int n, w;
	uint i;
	Rune r;

	n = 0;
	for(i=0; i<nr && n<nb; i++){
		w = chartorune(&r, s+n);
		n += w;
	}
	if(i != nr)
		return -1;
	return n;
}