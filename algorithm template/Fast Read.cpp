
//输入外挂，使用double a,readdouble(a)即可
bool readdouble(double &ret){
	int sgn;
	double bit=0.1;
	char c;
	c=getchar();
	if(c==EOF)return true;
	while(c!='-'&&c!='.'&&(c<'0'||c>'9'))c=getchar();
	sgn=(c=='-')?-1:1;
	ret=(c=='-')?0:(c-'0');
	while((c=getchar())>='0'&&c<='9')ret=ret*10+(c-'0');
	if(c==' '||c=='\n'){ret*=sgn;return true;}
	while((c=getchar())>='0'&&c<='9')ret+=(c-'0')*bit,bit/=10;
	ret*=sgn;
	return false;
}

//输入外挂，使用方法 int a;a=Scan();
int readint()  
{  
    int res=0,ch;  
    while(!((ch=getchar())>='0'&&ch<='9'))  
    {  
       if(ch==EOF)  return 1<<30;  
    }  
    res=ch-'0';  
    while((ch=getchar())>='0'&&ch<='9')  
        res=res*10+(ch-'0');  
    return res ;  
}  


inline void printInt(int64 x) {
	if (!x) {
		puts("0");
		return;
	}
	static int digits[30];
	int p = 0;
	while (x)
		digits[p++] = x % 10, x /= 10;
	for (int i = p - 1; i >= 0; --i) {
		putchar('0' + digits[i]);
	}
	putchar('\n');
}
