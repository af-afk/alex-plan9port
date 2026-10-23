#include <u.h>
#include <libc.h>

static uint
linestart(Rune *s, uint q)
{
	while(q > 0 && s[q-1] != '\n')
		q--;
	return q;
}

static uint
lineend(Rune *s, uint n, uint q)
{
	while(q < n && s[q] != '\n')
		q++;
	if(q < n)
		q++;
	return q;
}

static uint
lineindent(Rune *s, uint n, uint q, uint tabstop, int *blank)
{
	uint col;

	col = 0;
	while(q < n && s[q] != '\n'){
		if(s[q] == ' ')
			col++;
		else if(s[q] == '\t')
			col += tabstop-col%tabstop;
		else if(s[q] == '\r' && (q+1 == n || s[q+1] == '\n'))
			;
		else{
			*blank = 0;
			return col;
		}
		q++;
	}
	*blank = 1;
	return col;
}

int
indentselect(Rune *s, uint n, uint q, uint tabstop, uint *sel0, uint *sel1)
{
	uint end, indent, p, start, x;
	int blank;

	if(q > n || tabstop == 0)
		return 0;
	start = linestart(s, q);
	indent = lineindent(s, n, start, tabstop, &blank);
	end = lineend(s, n, start);

	p = start;
	while(p > 0){
		x = linestart(s, p-1);
		if(lineindent(s, n, x, tabstop, &blank) < indent && !blank)
			break;
		if(!blank)
			start = x;
		p = x;
	}

	p = end;
	while(p < n){
		x = lineend(s, n, p);
		if(lineindent(s, n, p, tabstop, &blank) < indent && !blank)
			break;
		if(!blank)
			end = x;
		p = x;
	}

	*sel0 = start;
	*sel1 = end;
	return 1;
}
