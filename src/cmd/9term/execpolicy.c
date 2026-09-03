#include <u.h>
#include <libc.h>

int
winexecsendback(int builtin, int tag, uint q0, uint q1,
	int expanded, uint eq0, uint eq1)
{
	return builtin || (tag && q0==q1 && (!expanded || eq0==eq1));
}
