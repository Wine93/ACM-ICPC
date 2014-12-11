
const int maxn = 500005;
const int N = 26;     //儿子节点个数,根据题意调整

class ACAutomato
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
		sz = 1, fail[0] = 0;
		memset(chd[0], 0, sizeof(chd[0]));
		for(int i = 0;i < N; i++)
			ID[i + ' '] = i;
	}

	//将权值为val的字符串a插入到trie中
	void insert(char *s, int val)
	{
		int p = 0;
		for (; *s; s++)
		{
			int c = ID[*s];
			if (!chd[p][c])
			{
				memset (chd[sz], 0, sizeof(chd[sz]));
				key[sz] = 0;
				chd[p][c] = sz++;
			}
			p = chd[p][c];
		}
		key[p] = val;
	}

	//构建AC自动机,确定每个节点的权值以及状态转移
	void build_ac()
	{
		int i, *s = Q, *e = Q;
		for (i = 0; i < N; i++)
			if (chd[0][i])
			{
				*e++ = chd[0][i];
				fail[chd[0][i]] = 0;
			}
		while (s != e)
		{
			int u = *s++;
			for (i = 0; i < N; i++)
			{
				int &v = chd[u][i];
				if (v)
				{
					fail[v] = chd[fail[u]][i];
					//以下一行代码要根据题目所给val的含义来写
					key[v] |= key[fail[v]];
					*e++ = v;
				}
				else
					v = chd[fail[u]][i];
			}
		}
	}
}AC;
