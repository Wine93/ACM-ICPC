/*   [算法名称] 后缀数组
 *   [复 杂 度] O(nlogn) 
 *   [说    明]
 *   1.insert进的全部数都必须大于0,如出现特殊情况,可根据题意将原数加上某个数使之大于0
 *   2.getsa()函数中的m默认为256 m=max{init[i]}+1,可根据题意更改
 *   3.输入的数据从下标0开始存储在init数组.第size位则自动添加上个0
 *   4.询问lcp时输入a,b必须不同
 *   5.所有的字符存在[0,size]内,并非[0,size)
 *   6.将height数组分组,可确保前缀相同
 */
class SuffixArray
{
public:
    static const int maxn = 220000;
    int init[maxn];//将初始数据,保存在init里,并保证每个数字都比0大
    int X[maxn];
    int Y[maxn];
    int Rank[maxn]; //名次数组,从0开始
    int sa[maxn]; //sa从1开始,因为最后一个字符(最小的)排在第0位 [0,size]
    int high[maxn]; //high从1开始,表示的是sa[i]和sa[i+1] [0,size)
    int buc[maxn];
    int log2[maxn];
    int best[maxn][20];
    int size;
    //初始数据个数
    void clear()
    {
        size  =0;
    }

    //输入一个数
    void insert(int n)
    {
        init[size++] = n;
    }

    bool cmp(int *r, int a, int b, int l)
    {
        return (r[a] == r[b] && r[a + l] == r[b + l]);
    }

    //当需要反复询问两个后缀的最长公共前缀时用到RMQ
    //n为字符串长度, m为最大值
    void getsa(int m = 256)
    {
        init[size] = 0;
        int i, l, p, *x=X, *y=Y, n = size + 1;
        for(i = 0; i < m; i++)
            buc[i] = 0;
        for(i = 0; i < n; i++)
            buc[x[i] = init[i]]++;
        for(i = 1; i < m; i++)
            buc[i] += buc[i - 1];
        for(i = n - 1; i >= 0; i--)
            sa[--buc[x[i]]] = i;
        for(l = 1, p = 1; p < n; m = p, l *= 2)
        {
            p = 0; 
            for(i = n - l; i < n; i++)
                y[p++] = i;
            for(i = 0; i < n; i++)
                 if(sa[i] >= l)
                    y[p++] = sa[i] - l;
            for(i = 0; i < m; i++)
                buc[i] = 0;
            for(i = 0; i < n; i++)
                buc[x[y[i]]]++;
            for(i = 1; i < m; i++)
                buc[i] += buc[i-1];
            for(i = n - 1; i >= 0; i--)
                sa[--buc[x[y[i]]]] = y[i];
            for(swap (x, y), x[sa[0]] = 0, i = 1, p = 1; i < n; i++)
                x[sa[i]] = cmp(y, sa[i - 1], sa[i], l) ? p - 1 : p++;
        } 
    }

    void gethigh()
    {
        int i, j, h = 0, n = size;
        for(i = 1; i <= n; i++)
            Rank[sa[i]] = i;
        high[0] = 0;
        for(i = 0; i < n; i++)
        {
            if(h > 0) h--; 
            j = sa[Rank[i] - 1];
            for( ; i + h < n && j + h < n && init[i + h] == init[j + h]; h++);
            high[Rank[i] - 1] = h;
        } 
    }

    //预处理每个数字的Log值,常数优化,用于RMQ
    void initLog()
    {
        int i;  
        log2[0] = -1;
        for(i = 1; i < maxn; i++)
            log2[i] = (i & (i - 1)) ? log2[i - 1] : log2[i - 1] + 1;
    }

    //初始化RMQ
    void initRMQ()
    {
        int i, j, limit, n = size;
        initLog();
        for(i = 0; i < n; i++)
            best[i][0] = high[i];
         for(j = 1; j <= log2[n]; j++)
          {
              limit = n - (1 << j); 
              for(i = 0; i <= limit; i++)
              best[i][j] = min (best[i][j - 1], best[i + (1 << j - 1)][j - 1]);
          } 
      }

    //询问a,b后缀的最长公共前缀 用lcp之前,先初始化RMQ
    int lcp(int a,int b)
    {
        int t;
        a = Rank[a];
        b = Rank[b];
        if(a > b)
            swap (a, b);
        b--;
        t = log2[b - a + 1];
        return min (best[a][t], best[b - (1 << t) + 1][t]);
    } 
}SA;


