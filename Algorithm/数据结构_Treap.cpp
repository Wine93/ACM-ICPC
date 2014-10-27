# include<cstdio>
# include<cstdlib>
# include<climits>
using namespace std;

const int N=100005;
int root,treap_size,value[N],key[N],weight[N],size[N],chd[N][2]; //key:rand value  

void update(int &x)
{
	size[x]=size[chd[x][0]]+weight[x]+size[chd[x][1]];
}

void rotate(int &x,int t)   //0:right 1:left
{
	int y=chd[x][t];
	chd[x][t]=chd[y][t^1];
	chd[y][t^1]=x;
	update(x);
	update(y);
	x=y;
}

void insert(int &x,int v)
{
	if(x)
	{
		if(value[x]==v)
			weight[x]++;
		else
		{
			int t=value[x]<v;
			insert(chd[x][t],v);
			if(key[chd[x][t]]<key[x])
				rotate(x,t);
		}
	}
	else        //null node
	{
		x=treap_size++;
		key[x]=rand();  //the fix value
		value[x]=v;
		weight[x]=1;
		chd[x][0]=chd[x][1]=0;
	}
	update(x);
}

void erase(int &x,int v)
{
	if(value[x]==v)
	{
		if(weight[x]>1)
			weight[x]--;
		else
		{
			if(!chd[x][0]&&!chd[x][1])   //left and right chd is null
			{
				x=0;
				return;
			}
			rotate(x,key[chd[x][0]]>key[chd[x][1]]);
			erase(x,v);
		}
	}
	else
		erase(chd[x][value[x]<v],v);
	update(x);
}

int select(int &x,int s)   //search the sth value 
{
	if(size[chd[x][0]]>=s)
		return select(chd[x][0],s);
	if(s<=size[chd[x][0]]+weight[x])
		return value[x];
	return select(chd[x][1],s-(size[chd[x][0]]+weight[x]));
}

int rank(int &x,int v)   //the v's rank
{
	if(!x)
		return 0;
	if(value[x]==v)
		return size[chd[x][0]]+1;
	if(v<value[x])
		return rank(chd[x][0],v);
	return size[chd[x][0]]+weight[x]+rank(chd[x][1],v);  //size[chd[x][0]]+1+rank(chd[x][1],v)
}

void init()
{
	root=0;
	treap_size=1;
	size[0]=0;
	key[0]=INT_MAX;
}
