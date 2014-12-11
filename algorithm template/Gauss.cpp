/*
 * [高斯消元_浮点数]
 * 1.a数组为左边系数矩阵, ans数组为等式右边常数(ex: ax + b = 0 应转为 ax = -b)
 * 2 equ为方程个数, var为未知数个数
 * 3.a和x数组下标都从0开始
 * 4.无解返回0, 有解返回1, 最终答案保存在x数组
 * 5.复杂度为O(n^3), n为变量个数
 */

# define MAXN 305
# define eps 1e-12

int gauss(double a[][MAXN], double x[], int equ, int var)
{
    int i, j, r, l, maxr;
    for(r = 0, l = 0; r < equ && l < var; r++, l++)
    {
        maxr = r;    //找出改列下绝对值最大的一行
        for(i = r + 1; i < equ; i++)
            if(fabs(a[i][l]) > fabs(a[maxr][l]))
                maxr = i;
        if(fabs(a[maxr][l]) < eps)   //注意, 无解返回0
            return 0;
        if(maxr != r)    //与当前行交换
        {
            for(j = l; j < var; j++) 
                swap(a[r][j], a[maxr][j]);
            swap(x[r], x[maxr]);
        }
        x[r] /= a[r][l];   
        for(j = l + 1; j < var; j++) 
            a[r][j] /= a[r][l];
        a[r][l] = 1;
        for(i = 0; i < equ; i++)
        {
            if (i == r) continue;
            x[i] -= x[r] * a[i][l];
            for(j = l + 1; j < var; j++)
                a[i][j] -= a[r][j] * a[i][l];
            a[i][l] = 0;
        }
    }
    return 1;
}
