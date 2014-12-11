/* [常用技巧]
 * 1. 当希望某个点必须留流经时, 你可以进行拆点, 流量为一个较大的负数, 因为是求最小费用, 网络流并会"必须"流向这条边
 * 2. 当求解的是最小(大)费用流, 并不一定是要最大流的时候, 只需要在源点流出的点和汇点连接一条费用为0的边即可.
 * 3. 当费用为二次或者三次之类的函数的话, 若函数是单调的, 则可以通过拆边来整合出费用, 比如 x^2 可拆成 1,3,5,7,9... and so on
 */


const int maxn = 5005;
const int maxm = 500005;     //边数量要4倍
const int inf = INT_MAX;
int num, head[maxn], father[maxn], dis[maxn], vis[maxn];
queue<int> q;

struct node
{
	int u, v, f, c;
	int next;
}e[maxm];

inline void add(int u, int v, int f, int c)
{
	e[num].u = u;
	e[num].v = v;
	e[num].f = f;
	e[num].c = c;
	e[num].next = head[u];
	head[u] = num++;
}    //f:flow c:cost

void addedge(int u, int v, int f, int c)
{
	add(u, v, f, c);
	add(v, u, 0, -c);
}

int spfa(int s, int t, int n)
{
	int i, u, v;
	memset(vis, 0, sizeof(vis));
	memset(father, -1, sizeof(father));
	for(i = 0; i <= n + 1; i++)
		dis[i] = inf;
	dis[s] = 0;
	vis[s] = 1;
	q.push(s);
	while(!q.empty())
	{
		u=q.front();
		q.pop();
		for(i = head[u]; i != -1; i = e[i].next)
		{
			v = e[i].v;
			if(e[i].f && dis[u] + e[i].c < dis[v])
			{
				dis[v] = dis[u] + e[i].c;
				father[v] = i;
				if(!vis[v])
				{
					q.push(v);
					vis[v] = 1;
				}
			}
		}
		vis[u] = 0;
	}
	return dis[t] != inf;
}

int minCostMaxflow(int s, int t, int n)
{
	int i, minflow = inf, mincost = 0;
	while(spfa(s, t, n))
	{
		for(i = father[t]; i != -1; i = father[e[i].u])
			if(e[i].f < minflow)
				minflow = e[i].f;
		for(i = father[t]; i != -1; i = father[e[i].u])
		{
			e[i].f -= minflow;
			e[i^1].f += minflow;
			mincost += minflow * e[i].c;
		}
	}
	return mincost;
}

void init()
{
	num = 0;
	memset(head, -1, sizeof(head));
}
