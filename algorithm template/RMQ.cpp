/*
注意: n, m最大为300
      先调用initLog(只需要调用一次), 再调用initRMQ;
*/
class RMQ
{
public:
    static const int MAXN = 305;
    static const int MAXM = 9;
    int dp[MAXN][MAXN][MAXM][MAXM];
    int Log2[MAXN];
    
    void initLog()
    {
        int i; 
        Log2[1] = 0;
        for(i = 2; i < MAXN; i++)
            Log2[i] = Log2[i-1] + !((i - 1)&i);
    }
    
    //下标范围[1, 1] - [n, m], 传递N大小可根据实际情况修改
    void initRMQ(int a[][MAXN], int n, int m)
    {
        int i, j, k, l;
        for(k = 0; (1<<k) <= n; k++)
            for(l = 0; (1<<l) <= m; l++)
                for(i = 1; i + (1<<k) - 1 <= n; i++)
                    for(j = 1; j + (1<<l) - 1 <= m; j++)
                    {
                        if(k == 0 && l == 0) dp[i][j][k][l] = a[i][j];
                        else if(k == 0) dp[i][j][k][l] = max (dp[i][j][k][l - 1], dp[i][j + (1 << l - 1)][k][l - 1]);
                        else if(l == 0) dp[i][j][k][l] = max (dp[i][j][k - 1][l], dp[i + (1 << k - 1)][j][k - 1][l]);
                        else
                        {
                            int a = max (dp[i][j][k - 1][l - 1], dp[i][j + (1 << l - 1)][k - 1][l - 1]);
                            int b = max (dp[i + (1 << k - 1)][j][k - 1][l - 1], dp[i + (1 << k - 1)][j + (1 << l - 1)][k - 1][l - 1]);
                            dp[i][j][k][l] = max(a, b);
                        }
                    }
    }
    
    int getmax(int x1, int y1, int x2, int y2)
    {
        int k = Log2[x2 - x1 + 1];
        int l = Log2[y2 - y1 + 1];
        int a = max (dp[x1][y1][k][l], dp[x2 - (1 << k) + 1][y1][k][l]);
        int b = max (dp[x1][y2 - (1 << l) + 1][k][l], dp[x2 - (1 << k) + 1][y2 - (1 << l) + 1][k][l]);
        return max(a, b);
    }
}rmq;
