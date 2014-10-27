/**************************************************************
    Problem: BZOJ 1500 [NOI2005]ά������
    User: Wine93
    Language: C++
    Result: Accepted
    Time:7284 ms
    Memory:26688 kb
    Url: http://61.187.179.132/JudgeOnline/problem.php?id=1500
****************************************************************/
 
# include<cstdio>
# include<algorithm>
   
using std::swap;
using std::max;
   
# define LL long long 
# define inf 1<<29
# define keytree (chd[chd[root][1]][0])
# define N 500005
   
int fa[N],chd[N][2],val[N],sz[N];  
int root,tot1,tot2;
int q[N],s[N];   //�����ڴ� 
int num[N];
int sam[N],sum[N],lx[N],rx[N],mx[N];    
bool rev[N];
   
/*
 * Splay Tree
 * ������������±�Ϊ1-N��Ϊʵ�ַ��㣬��0��N+1��λ������һ��keyΪkeyInf�Ľ��
 * select()�����е�kth��ʵ���±ߵĹ�ϵ����
 * keyInf - num - num - num - num - keyInf
 *     0     1     2     3     4     5
 * ������0�ڵ��滻�սڵ�
 * 
 * ע��1.ÿ�β���,�޸ģ���ת�Ȳ�������Ҫ��תkeytree�����ڵ�,��ά�����ֵ splay(keytree,0).ɾ����������,PushUp���и���
 * ע��2.��ʼ���ڵ�0�����ֵ��������������,��mx,lx,rx...
 * ע��3.PushDown����ʱ,ֻҪ�ýڵ���ϱ����,�ͱ�����¸ýڵ�����ֵ,������ֻ���𵽱������(�ɲ鿴rev����)
 */
  
/*
 *  ���¹ؼ���
 */
void PushUp(int x)
{
    int lson=chd[x][0],rson=chd[x][1];
    sz[x]=sz[lson]+1+sz[rson];
    sum[x]=sum[lson]+val[x]+sum[rson];
    mx[x]=max(mx[lson],mx[rson]);
    mx[x]=max(mx[x],max(0,rx[lson])+val[x]+max(0,lx[rson]));
    lx[x]=max(lx[lson],sum[lson]+val[x]+max(0,lx[rson]));
    rx[x]=max(rx[rson],sum[rson]+val[x]+max(0,rx[lson]));
}
   
void update_rev(int x)
{
    if(x)
    {
        rev[x]^=1;
        swap(chd[x][0],chd[x][1]);
        swap(lx[x],rx[x]);
    }
}
  
void update_sam(int x,int c)
{
    if(x)
    {
        sam[x]=1;
        val[x]=c;
        sum[x]=sz[x]*c;
        mx[x]=lx[x]=rx[x]=max(c,sz[x]*c);
    }
}
  
/*
 *  ����·�
 */
void PushDown(int x)  
{
    if(rev[x])
    {
        update_rev(chd[x][0]);
        update_rev(chd[x][1]);
        rev[x]=0;
    }
    if(sam[x])
    {
        update_sam(chd[x][0],val[x]);
        update_sam(chd[x][1],val[x]);
        sam[x]=0;
    }
}
  
/*
 * ��ת����, t=0 ��ʾ����, t=1 ��ʾ����
 */
void rotate(int x,int t)
{
    int y=fa[x];
    PushDown(y);
    PushDown(x);
    chd[y][!t]=chd[x][t];
    fa[chd[x][t]]=y;
    fa[x]=fa[y];
    if(fa[x])
        chd[fa[y]][chd[fa[y]][1]==y]=x;
    chd[x][t]=y;
    fa[y]=x;
    PushUp(y);
}
  
/*
 * ��תʹx��Ϊgoal���ӽڵ㣬��goalΪ0��x��תΪ���ڵ�
 */
void splay(int x,int goal)    
{
    PushDown(x);
    while(fa[x]!=goal)
    {
        if(fa[fa[x]]==goal)
            rotate(x,chd[fa[x]][0]==x);
        else
        {
            int y=fa[x],z=fa[y];
            int t=(chd[z][0]==y);
            if(chd[y][t]==x)
                rotate(x,!t),rotate(x,t);
            else
                rotate(y,t),rotate(x,t);
        }
    }
    PushUp(x);
    if(goal==0)   
        root=x;
}
  
/*
 * �ҵ�λ��Ϊk�Ľڵ�,������ֵ,����������x�Ķ���
 */
int select(int k,int goal)   
{
    int x=root;
    PushDown(x);
    while(sz[chd[x][0]]!=k)
    {
        if(k<sz[chd[x][0]])
            x=chd[x][0];
        else
        {
            k-=(sz[chd[x][0]]+1);
            x=chd[x][1];
        }
        PushDown(x);
    }
    int kth=val[x];
    splay(x,goal);
    return kth;
} 
  
/*
 * ����xΪ������������ɾ����,�������ڴ�
 */
void erase(int x)   
{
    int f=fa[x],head=0,tail=0;
    for(q[tail++]=x;head<tail;head++)
    {
        s[tot2++]=q[head];
        if(chd[q[head]][0])
            q[tail++]=chd[q[head]][0];
        if(chd[q[head]][1])
            q[tail++]=chd[q[head]][1];                  
    }
    chd[f][chd[f][1]==x]=0;
    PushUp(f);
}
  
/*
 * ��x�ڵ㴦����һ���µĽڵ�,ֵΪx,���ڵ�Ϊf,֮ǰɾ���Ľڵ��ŵ�s���Ա�������
 */
void newnode(int &x,int v,int f)   
{
    if(tot2)
        x=s[--tot2];
    else
        x=++tot1;
    chd[x][0]=chd[x][1]=0;
    sum[x]=mx[x]=val[x]=v;
    lx[x]=rx[x]=max(0,v);
    sam[x]=rev[x]=0;
    fa[x]=f;
    sz[x]=1;
}
  
/*
 * ��num������[l,r]�����ڵ�ֵ����
 */
void build(int &x,int l,int r,int f)   
{
    if(l<=r)
    {
        int m=(l+r)>>1;
        newnode(x,num[m],f);
        build(chd[x][0],l,m-1,x);
        build(chd[x][1],m+1,r,x);
        PushUp(x);
    }
}  
  
/*
 *   ���г�ʼ������,�����������0�ڵ�����ֵ,��������Ҫ��ս�ظ�
 */
void init()
{
    chd[0][0]=chd[0][1]=fa[0]=sz[0]=0;
    root=tot1=tot2=0;
    sum[0]=rev[0]=0;
    mx[0]=lx[0]=rx[0]=-inf;
    newnode(root,-1,0);
    newnode(chd[root][1],-1,root);
    sz[root]=2;
}
  
/*
 *   1.��pos�����tot������(tot�����ݴ���num������)
 */
 
void Insert(int pos,int tot)   
{
    select(pos,0);
    select(pos+1,root);
    build(keytree,1,tot,chd[root][1]);
    splay(keytree,0);
}
  
/*
 *   2.ɾ����pos��ʼ��tot������
 */
void Delete(int pos,int tot)  //2.ɾ�� 
{
    select(pos-1,0);
    select(pos+tot,root);
    erase(keytree);
    PushUp(chd[root][1]);
    PushUp(root);
}
  
/*
 *   3.��pos��ʼ��tot�����ݶ�ת���c
 */
void MakeSame(int pos,int tot,int c)  
{
    select(pos-1,0);
    select(pos+tot,root);
    update_sam(keytree,c);
    splay(keytree,0);
}
  
/*
 *   4.��pos��ʼ��tot�����ݽ��з�ת
 */
void Reverse(int pos,int tot)   
{
    select(pos-1,0);
    select(pos+tot,root);
    update_rev(keytree);
    splay(keytree,0);
}
  
/*
 *   5.��ȡ��pos��ʼ��tot�����ݺ�
 */
void GetSum(int pos,int tot)   //5.���
{
    select(pos-1,0);
    select(pos+tot,root);
    printf("%d\n",sum[keytree]);
}
  
 /*
 *   6.��������к�
 */
void MaxSum()     
{
    select(0,0);
    select(sz[root]-1,root);
    printf("%d\n",mx[keytree]);
}
  
int main()
{
    int i,j,n,m,pos,tot,l,r,c;
    char op[20];
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        init();
        for(i=1;i<=n;i++)
            scanf("%d",&num[i]);
        build(keytree,1,n,chd[root][1]);
        splay(keytree,0);
        for(i=1;i<=m;i++)
        {
            scanf("%s",op);
            if(op[2]=='S')
            {
                scanf("%d%d",&pos,&tot);
                for(j=1;j<=tot;j++)
                    scanf("%d",&num[j]);
                Insert(pos,tot);
            }
            else if(op[2]=='L')
            {
                scanf("%d%d",&pos,&tot);
                Delete(pos,tot);
            }
            else if(op[2]=='K')
            {
                scanf("%d%d%d",&pos,&tot,&c);
                MakeSame(pos,tot,c);
            }
            else if(op[2]=='V')
            {
                scanf("%d%d",&pos,&tot);
                Reverse(pos,tot);
            }
            else if(op[2]=='T')
            {
                scanf("%d%d",&pos,&tot);
                GetSum(pos,tot);
            }
            else
                MaxSum();
        }
    }
    return 0;
}