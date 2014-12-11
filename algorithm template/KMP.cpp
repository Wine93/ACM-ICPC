# define N 10005
int next[N];
char s[N], ch[N];

void getnext(char *s)
{
    int i = 0, j = -1, len = strlen(s);
    next[0] = -1;
	for(i = 1; i < len; i++
	{
		while(j >= 0 && s[j + 1] != s[i])
			j = next[j];
		if(s[j + 1] == s[i])
			j++;
		next[i] = j;
	}
}

int kmp(char *s, char *ch)
{
    getnext(ch);
    int len = strlen(s), m = strlen(ch);
    int i, j = -1, res = 0;
	for(i = 0; i < len; i++)
	{
		while(j >= 0 && s[i] != ch[j + 1])
			j = next[j];
		if(s[i] == ch[j + 1])
			j++;
		if(j + 1 == m)
		{
			res++;
			j = -1;    
		}
	}
	return res;
}

