#include <u.h>
#include <libc.h>

enum {
	Maxexpandedpath = 64*1024,
};


static int
isnamefirst(int c)
{
	return c == '_' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z';
}

static int
isnamechar(int c)
{
	return isnamefirst(c) || c >= '0' && c <= '9';
}

static int
append(char **out, size_t *nout, size_t *cap, char *s, size_t n)
{
	void *p;
	size_t need, max;

	max = ~(size_t)0;
	if(*nout > Maxexpandedpath || n > Maxexpandedpath-*nout)
		return 0;
	need = *nout+n+1;
	if(need > *cap){
		while(need > *cap){
			if(*cap > max/2)
				*cap = need;
			else
				*cap *= 2;
		}
		p = realloc(*out, *cap);
		if(p == nil)
			sysfatal("expandenvpath: out of memory");
		*out = p;
	}
	memmove(*out+*nout, s, n);
	*nout += n;
	(*out)[*nout] = 0;
	return 1;
}

/* Expand $name and ${name}, leaving references to unset variables intact. */
char*
expandenvpath(char *path)
{
	char *out, *value, *name;
	size_t cap, end, i, inlen, j, n, nout;
	int braced;

	inlen = strlen(path);
	if(inlen > Maxexpandedpath)
		return nil;
	cap = inlen+1;
	if(cap < 32)
		cap = 32;
	out = malloc(cap);
	if(out == nil)
		sysfatal("expandenvpath: out of memory");
	nout = 0;
	out[0] = 0;
	for(i=0; path[i]!=0;){
		if(path[i] != '$'){
			if(!append(&out, &nout, &cap, path+i, 1)){
				free(out);
				return nil;
			}
			i++;
			continue;
		}
		j = i+1;
		braced = path[j] == '{';
		if(braced)
			j++;
		if(!isnamefirst((uchar)path[j])){
			if(!append(&out, &nout, &cap, path+i, 1)){
				free(out);
				return nil;
			}
			i++;
			continue;
		}
		n = 1;
		while(isnamechar((uchar)path[j+n]))
			n++;
		if(braced && path[j+n] != '}'){
			if(!append(&out, &nout, &cap, path+i, 1)){
				free(out);
				return nil;
			}
			i++;
			continue;
		}
		end = j+n+(braced ? 1 : 0);
		name = malloc(n+1);
		if(name == nil)
			sysfatal("expandenvpath: out of memory");
		memmove(name, path+j, n);
		name[n] = 0;
		value = getenv(name);
		free(name);
		if(value == nil){
			if(!append(&out, &nout, &cap, path+i, end-i)){
				free(out);
				return nil;
			}
		}else{
			if(!append(&out, &nout, &cap, value, strlen(value))){
				free(value);
				free(out);
				return nil;
			}
			free(value);
		}
		i = end;
	}
	return out;
}
