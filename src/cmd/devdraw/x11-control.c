#include <u.h>
#include <libc.h>

int
x11controlkey(int k, int control)
{
	if(control)
		k &= 0x9f;
	return k;
}
