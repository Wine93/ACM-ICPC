/*
 * 1. 使用前先调用init();
 * 2. 2^17=131072
 *    2^18=262144
 * 3. 调用dfs时注意第一个fa为0还是1(计算dep时需要做出调整,防止数组越界)
 */

const int MAXN = 100005;  //节点个数
const int Pow = 18;

vector<int> edge[MAXN];   //边
int dep[MAXN];            //节点深度
int p[MAXN][Pow];         //第(2^j)个父节点

void dfs(int u, int fa)
{
	int i, v;
	dep[u] = dep[fa] + 1;
	p[u][0] = fa;
	for (i = 1; i < Pow; i++)
		p[u][i] = p[p[u][i - 1]][i - 1];
	for (i = 0; i < edge[u].size(); i++)
	{
		v = edge[u][i];
		if (v == fa) continue;
		dfs(v, u);
	}
}

int lca(int a, int b)
{
	int i, del;
	if (dep[a] > dep[b])    
		swap(a, b);
	if (dep[a] < dep[b])   //调整a,b至同一深度
	{
		del = dep[b] - dep[a];
		for (i = 0; i < Pow; i++)
			if (del & (1 << i))
				b = p[b][i];
	}
	if (a != b)    //二分求lca
	{
		for (i = Pow - 1; i >= 0; i--)
			if (p[a][i] != p[b][i])
				a = p[a][i], b = p[b][i];
		a = p[a][0], b = p[b][0];
	}
	return a;
}

void init()
{
    int i;
    for (i = 0; i < MAXN; i++)
        edge[i].clear();
    dep[0] = 0;
}
