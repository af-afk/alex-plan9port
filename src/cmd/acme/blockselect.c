#include <u.h>
#include <libc.h>

int
blockselect(Rune *s, uint n, uint q0, uint q1, uint *sel0, uint *sel1)
{
	static Rune left[] = { '(', '[', '{' };
	static Rune right[] = { ')', ']', '}' };
	uint best, close, i, limit, open;
	int depth, found, p;

	if(q0 > q1 || q1 > n)
		return 0;
	found = 0;
	best = 0;
	for(p=0; p<nelem(left); p++){
		limit = q0;
		for(;;){
			depth = 0;
			open = n;
			for(i=limit; i>0; i--){
				if(s[i-1] == right[p])
					depth++;
				else if(s[i-1] == left[p]){
					if(depth == 0){
						open = i-1;
						break;
					}
					depth--;
				}
			}
			if(open == n)
				break;
			depth = 1;
			close = n;
			for(i=open+1; i<n; i++){
				if(s[i] == left[p])
					depth++;
				else if(s[i] == right[p] && --depth == 0){
					close = i;
					break;
				}
			}
			if(close != n && q1 <= close && (q0 == q1 || open+1 != q0 || close != q1)){
				if(!found || open > best){
					found = 1;
					best = open;
					*sel0 = open+1;
					*sel1 = close;
				}
				break;
			}
			limit = open;
		}
	}
	return found;
}
