/**************************************************************
    Problem: BZOJ 1500 [NOI2005]维修数列
    User: Wine93
    Language: C++
    Result: Accepted
    Time:7284 ms
    Memory:26688 kb
    Url: http://61.187.179.132/JudgeOnline/problem.php?id=1500
****************************************************************/

# define LL long long 
# define inf 1<<29
# define keytree (chd[chd[root][1]][0])
# define N 500005
   
int fa[N], chd[N][2], val[sz[N];  
int root,tot1,tot2;
int q[N],s[N];   //回收内存 
int num[N];
int sam[N],sum[N],lx[N],rx[N],mx[N];    
bool rev[N];
   
/*
 * Splay Tree
 * 所处理的数组下标为1-N，为实现方便，在0和N+1的位置增加一个key为keyInf的结点
 * select()函数中的kth与实际下边的关系如下
 * keyInf - num - num - num - num - keyInf
 *     0     1     2     3     4     5
 * 另外用0节点替换空节点
 * 
 * 注意1.每次插入,修改，翻转等操作后需要旋转keytree到根节点,以维护相关值 splay(keytree,0).删除操作特外,PushUp进行更新
 * 注意2.初始化节点0的相关值必须根据题意调整,如mx,lx,rx...
 * 注意3.PushDown操作时,只要该节点打上标记了,就必须更新该节点的相关值,懒惰标记只是起到标记作用(可查看rev操作)
 */
  
/*
 *  更新关键字
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
 *  标记下放
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
 * 旋转操作, t=0 表示左旋, t=1 表示右旋
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
 * 旋转使x成为goal的子节点，若goal为0则x旋转为根节点
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
 * 找到位置为k的节点,返回其值,并将其升至x的儿子
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
 * 将以x为根的整棵子树删除掉,并回收内存
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
 * 在x节点处生成一个新的节点,值为x,父节点为f,之前删除的节点会放到s中以便再利用
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
 * 用num数组中[l,r]区间内的值建树
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
 *   进行初始化工作,根据题意调整0节点的相关值,其他不需要挑战呢个
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
 *   1.在pos后插入tot个数据(tot个数据存于num数组中)
 */
 
void Insert(int pos,int tot)   
{
    select(pos,0);
    select(pos+1,root);
    build(keytree,1,tot,chd[root][1]);
    splay(keytree,0);
}
  
/*
 *   2.删除从pos开始的tot个数据
 */
void Delete(int pos,int tot)  //2.删除 
{
    select(pos-1,0);
    select(pos+tot,root);
    erase(keytree);
    PushUp(chd[root][1]);
    PushUp(root);
}
  
/*
 *   3.从pos开始的tot个数据都转变成c
 */
void MakeSame(int pos,int tot,int c)  
{
    select(pos-1,0);
    select(pos+tot,root);
    update_sam(keytree,c);
    splay(keytree,0);
}
  
/*
 *   4.从pos开始的tot个数据进行翻转
 */
void Reverse(int pos,int tot)   
{
    select(pos-1,0);
    select(pos+tot,root);
    update_rev(keytree);
    splay(keytree,0);
}
  
/*
 *   5.获取从pos开始的tot个数据和
 */
void GetSum(int pos,int tot)   //5.求和
{
    select(pos-1,0);
    select(pos+tot,root);
    printf("%d\n",sum[keytree]);
}
  
 /*
 *   6.最大自序列和
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
