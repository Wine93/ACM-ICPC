# include<cstdio>
# include<cstring>
using namespace std;

const int maxn=500005;
const int N=26;     //���ӽڵ����,�����������

class ACAutomaton
{
private:
	int chd[maxn][N];
	int key[maxn];
	int fail[maxn];
	int Q[maxn];
	int ID[128];
	int sz;
public:
	void init()
	{
		sz=1,fail[0]=0;
		memset(chd[0],0,sizeof(chd[0]));
		for(int i=0;i<N;i++)
			ID[i+' ']=i;
	}

	//��ȨֵΪval���ַ���a���뵽trie��
	void insert(char *s,int val)
	{
		int p=0;
		for(;*s;s++)
		{
			int c=ID[*s];
			if(!chd[p][c])
			{
				memset(chd[sz],0,sizeof(chd[sz]));
				key[sz]=0;
				chd[p][c]=sz++;
			}
			p=chd[p][c];
		}
		key[p]=val;
	}

	//����AC�Զ���,ȷ��ÿ���ڵ��Ȩֵ�Լ�״̬ת��
	void build_ac()
	{
		int i,*s=Q,*e=Q;
		for(i=0;i<N;i++)
			if(chd[0][i])
			{
				*e++=chd[0][i];
				fail[chd[0][i]]=0;
			}
		while(s!=e)
		{
			int u=*s++;
			for(i=0;i<N;i++)
			{
				int &v=chd[u][i];
				if(v)
				{
					fail[v]=chd[fail[u]][i];
					//����һ�д���Ҫ������Ŀ����val�ĺ�����д
					key[v]|=key[fail[v]];
					*e++=v;
				}
				else
					v=chd[fail[u]][i];
			}
		}
	}
}AC;