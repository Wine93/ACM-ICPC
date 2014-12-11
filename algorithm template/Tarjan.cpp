
/* 
 * 注意点:
 * 1. 有些图不连通,需多次调用tarjan (dfn为0就调用)
 * 
 */
const int maxn = 10005;
const int maxm = 50005;

int num, head[maxn];
int cnt;   //时间戳, 范围[1, cnt]
int scc;   //强联通个数, 范围[1, scc]
int low[maxn];
int dfn[maxn];
int col[maxn];   //点属于强联通编号
stack<int> stk;

struct node
{
	int u, v, next;
}e[maxm];

void addedge(int u, int v)
{
	e[num].u = u;
	e[num].v = v;
	e[num].next = head[u];
	head[u] = num++;
}

void tarjan(int u)
{
	int i,v;
	stk.push(u);
	dfn[u] = low[u] = cnt++;
	for(i = head[u]; i != -1; i = e[i].next)
	{
		v = e[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(!col[v])
			low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u])
	{
		scc++;
		while(1)
		{
			v = stk.top();
			stk.pop();
			col[v] = scc;
			if(v == u)
				break;
		}
	}
}

void init()
{
	num = 0;
	memset(head, -1, sizeof(head));
	cnt = 1;
	scc = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(col, 0, sizeof(col));
}

