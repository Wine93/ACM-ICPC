# include<map>
# include<set>
# include<list>
# include<cmath>
# include<queue>
# include<stack>
# include<vector>
# include<string>
# include<cstdio>
# include<cstring>
# include<iostream>
# include<algorithm>
# include<functional>
using namespace std;

typedef pair<int,int> PII;
# define INF 1<<30
# define LL long long
# define MOD 1000000007
# define VI vector<int>
# define VLL vector<LL>
# define VPII vector<PII>
# define VS vector<string>
# define PII pair<int,int>

# define F first
# define S second
# define mp make_pair
# define pb push_back
# define lb lower_bound
# define up upper_bound
# define lowbit(x)(x&-x)
# define lson l,m,rt<<1
# define rson m+1,r,rt<<1|1
# define clr(x) (x).clear()
# define sz(x) ((int)(x).size())
# define all(x) (x).begin(),(x).end()
# define mem(x,y) memset(x,y,sizeof(x))
# define rep(i,a,b) for(i=(a);i<=(b);i++))
# define forall(it,c) for(typeof((c).begin())it=(c).begin();it!=(c).end();it++)

/*
 * [二维几何基本函数]  [lrj版]
 * 注意1: 使用前必须调入<math.h>头文件
 * 
 *  函数列表:
 *  (1).基本定义
 *  Point(double x, double y)
 *  Circle(Point c, double r)
 *  Line(Point p, Vector v)
 *  
 *  (2)向量运算
 *  [1]两向量点积         double Dot(Vector a, Vector b) 
 *  [2]两向量的叉积       double Cross(Vector a, Vector b)
 *  [3]向量的长度         double Length(Vector a)
 *  [4]向量的极角         double angle(Vector v)
 *  [5]两向量的转角       double Angle(Vector a, Vector b)
 *  [6]向量绕起点旋转     Vector Rotate(Vector a, double rad)
 *  [7]向量的单位法向量   Vector Normal(Vector a)
 *
 *  (3)点和直线
 *  [8].二直线交点(参数式)         Point GetLineIntersection(Point p, Vector v, Point q, Vector w)
 *  [9].线段规范相交判断(两点式)   bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) 
 *  [10].点到直线的距离(两点式)    double DistanceToLine(Point p, Point a, Point b)
 *  [11].点到线段最近点的距离      double DistanceToSegment(Point p, Point a, Point b)
 *  [12].点在直线上的投影(二点式)  Point GetLineProjection(Point p, Point a, Point b)
 *  [13].点在线段上的判断(二点式)  bool OnSegment(Point p, Point a1, Point a2) 
 *
 *  (4)多边形
 *  [14]三角形有向面积的两倍  double Area2(Point a, Point b, Point c)
 *  [15]多边形有向面积 点[0, n)   double PolygonArea(Point p[], int n)
 *
 *  (5)与圆和球相关的计算问题
 *  [16]直线与圆的交点         		int GetLineCircleIntersection(Line l, Circlr c, Point &p1, Point &p2, vector<Point> &ans)
 *  [17]两圆相交(求交点)       		int GetCircleCirlceIntersection(Circle c1, Circle c2, vector<Point> &ans)
 *  [18]过定点作圆的切线       		int GetTangents(Point p, Circle c, Vector v[])
 *  [19]两圆的公切线(判断两圆关系)	int GetTangents(Circle c1, Circle c2, Point a[], Point b[])
 *  [20]三角形内切圆                	Circle InCircle(Point p1, Point p2, Point p3)
 *  [21]三角形外接圆                	Circle OutCircle(Point p1, Point p2, Point p3)
 *
 *  (6)二维几何常用算法
 *  [22]点在多边形内判断            int IsPointInPolygon(Point p, Point poly[], int n) 
 *  [23]计算凸包                    int ConvexHull(Point p[], int n, Point ans[])
 */

const double eps = 1e-10;
const double PI = acos(-1.0);

//精度控制
int dcmp(double x)
{
    if (fabs(x) < eps)
        return 0;
    else
        return x < 0 ? -1 : 1;
}

struct Point
{
    double x, y;
    Point(double xx = 0, double yy = 0): x(xx), y(yy) {};

    Point operator + (const Point &b)const
    {
        return Point(x + b.x, y + b.y);
    }

    Point operator - (const Point &b)const
    {
        return Point(x - b.x, y - b.y);
    }

    Point operator * (double p)
    {
        return Point(x * p, y * p);
    }

    Point operator / (double p)
    {
        return Point(x / p, y / p);
    }

    bool operator < (const Point &b)
    {
        return x < b.x || (x == b.x && y < b.y);
    }

    bool operator == (const Point &b)
    {
        return dcmp(x - b.x) == 0 && dcmp(y - b.y) == 0;
    }
};
typedef Point Vector;   //Vector: 向量

struct Circle
{
    Point c;
    double r;
    Circle() {};
    Circle(Point cc, double rr) : c(cc), r(rr) {};
    Point point(double a)
    {
        return Point(c.x + cos(a) * r, c.y + sin(a) * r);
    }
};

struct Line
{
    Point p;
    Vector v;
    Line() {};
    Line(Point pp, Vector vv) : p(pp), v(vv) {};
    Point point(double a)
    {
        return p + v * a;
    }
};

//[1]两向量点积
double Dot(Vector a, Vector b)
{
    return a.x * b.x + a.y * b.y;
}

//[2]两向量叉积
double Cross(Vector a, Vector b)
{
    return a.x * b.y - a.y * b.x;
}

//[3]向量长度
double Length(Vector a)
{
    return sqrt(Dot(a, a));
}

//[4]向量的极角
double angle(Vector v)
{
    return atan2(v.y, v.x);
}

//[5]两向量夹角 单位:PI 范围:[0, PI]
double Angle(Vector a, Vector b)
{
    return acos(Dot(a, b) / Length(a) / Length(b));
}

//[6]向量绕起点旋转 (rad为逆时针旋转的角 单位:弧度)
//1.x' = x * cosa - y * sina; y' = x * sina + y * cosa; 
//2.若顺时针旋转, rad取负即可
Vector Rotate(Vector a, double rad)
{
    return Vector(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}

//[7]向量的单位法向量
Vector Normal(Vector a)
{
    double L = Length(a);
    return Vector(-a.y / L, a.x / L);
}

//[8]两直线交点
//调用前请确保两条直线p+tv和q+tv有唯一的交点。当且仅当Cross(v,w)非0
Point GetLineIntersection(Point p, Vector v, Point q, Vector w)
{
    Vector u = p - q;
    double t = Cross(w, u) / Cross(v, w);
    return p + v * t;
}

//[9]判断线段(a1a2, b1b2)是否相交(规范相交)
//规范相交:每条线段的两个端点都在另一条线段的两侧
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = Cross(a2 - a1, b1 - a1);
    double c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1);
    double c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

//[10]点到直线的距离 
double DistanceToLine(Point p, Point a, Point b)
{
    Vector v1 = b - a, v2 = p - a;
    return fabs(Cross(v1, v2) / Length(v1));   //如果不取绝对值, 得到的是有向距离
}

//[11]点到线段最近点的距离
double DistanceToSegment(Point p, Point a, Point b)
{
    if (a == b) return Length(p - a);
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else return fabs(Cross(v1, v2) / Length(v1));
}

//[12]点p在直线ab上的投影点
Point GetLineProjection(Point p, Point a, Point b)
{
    Vector v = b - a;
    return a + v * (Dot(v, p - a) / Dot(v, v));
}

//[13]判断点p是否在线段a1a2上
bool OnSegment(Point p, Point a1, Point a2) 
{
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}

//[14]三角形面积*2
double Area2(Point a, Point b, Point c)
{
    return Cross(b - a, c - a);
}

//[15]多边形的有向面积  点范围[0, n)
double PolygonArea(Point p[], int n)
{
    int i;
    double area = 0;
    for (i = 1; i < n - 1; i++)
        area += Cross(p[i] - p[0], p[i + 1] - p[0]);
    return area / 2;   
}

//[16]直线与圆的交点
int GetLineCircleIntersection(Line l, Circle c1, Point &p1, Point &p2, vector<Point> &ans)
{
    double t1, t2;
    double a = l.v.x, b = l.p.x - c1.c.x, c = l.v.y, d = l.p.y - c1.c.y;
    double e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - c1.r * c1.r;
    double delta = f * f - 4 * e * g;
    if (dcmp(delta) < 0) return 0;   //相离
    if (dcmp(delta) == 0)  //相切
    {
        t1 = t2 = -f / (2 * e);
        p1 = p2 = l.point(t1);
        ans.push_back(p1);
        return 1;
    }
    t1 = (-f - sqrt(delta)) / (2 * e);
    t2 = (-f + sqrt(delta)) / (2 * e);
    p1 = l.point(t1);
    p2 = l.point(t2); 
    ans.push_back(p1);
    ans.push_back(p2);
    return 2;
}


//[17]两圆相交交点
//返回值 -1:两圆重合 0:两圆相离  1:两圆相切  2:两圆相交
int GetCircleCirlceIntersection(Circle c1, Circle c2, vector<Point> &ans)
{
    double d = Length(c1.c - c2.c);
    if (dcmp(d) == 0)
    {
        if (dcmp(c1.r - c2.r) == 0) return -1;  //两圆重合
        return 0;
    }
    if (dcmp(c1.r + c2.r - d) < 0) return 0;           //两圆相离
    if (dcmp(fabs(c1.r - c2.r) - d) > 0) return 0;    //两圆内含
    double a = angle(c2.c - c1.c);   //向量c1c2的极角
    double da = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));  //c1c2到c1p1的角
    Point p1 = c1.point(a - da), p2 = c1.point(a + da);
    ans.push_back(p1);
    if (p1 == p2) return 1;
    ans.push_back(p2);
    return 2;
}

//[18]过定点作圆的切线 v[i]是第i条切线的向量(下标从1开始) 返回切线条数
int GetTangents(Point p, Circle c, Vector v[])
{
    Vector u = c.c - p;
    double dist = Length(u);
    if (dist < c.r) return 0;   //p在圆内
    else if (dcmp(dist - c.r) == 0)  //p在圆上,只有一条切线
    {
        v[1] = Rotate(u, PI / 2);
        return 1;
    }
    else
    {
        double ang = asin(c.r / dist);
        v[1] = Rotate(u, -ang);
        v[2] = Rotate(u, ang);
        return 2;
    }
}

//[19]两圆的公切线 a[i]和b[i]分别是第i条切线在圆c1和圆c2上的切点(下标从1开始)
//通过返回值判断两圆关系: -1:完全重合 0:内含 1:内切 2:相交 3:外切 4:相离
int GetTangents(Circle c1, Circle c2, Point a[], Point b[])
{
    int cnt = 0;
    if (c1.r < c2.r)
    {
        swap(c1, c2);
        swap(a, b);
    }
    int d2 = (c1.c.x - c2.c.x) * (c1.c.x - c2.c.x) + (c1.c.y - c2.c.y) * (c1.c.y - c2.c.y);
    int rdiff = c1.r - c2.r;
    int rsum = c1.r + c2.r;
    if (d2 < rdiff * rdiff) return 0;   //内含
    double base = atan2(c2.c.y - c1.c.y, c2.c.x - c1.c.x);
    if (d2 == 0 && c1.r == c2.r) return -1;   //无限多条切线
    if (d2 == rdiff * rdiff)   //内切, 一条内切线
    {
        a[1] = c1.point(base), b[1] = c2.point(base); 
        return 1;
    }
    double ang = acos((c1.r - c2.r) / sqrt(d2));   //有外公切线
    a[1] = c1.point(base + ang), b[1] = c2.point(base + ang);
    a[2] = c1.point(base - ang), b[2] = c2.point(base - ang);
    if (d2 == rsum * rsum)    //外切, 一条内公切线
    {
        a[3] = c1.point(base), b[3] = c2.point(PI + base);
        return 3;
    }
    if (d2 > rsum * rsum)   //相离, 两条内公切线
    {
        double ang = acos((c1.r + c2.r) / (sqrt(d2)));
        a[3] = c1.point(base + ang), b[3] = c2.point(PI + base + ang);
        a[4] = c1.point(base - ang), b[4] = c2.point(PI + base - ang);
        return 4;
    }
    return 2;
}

//[20]三角形外接圆
Circle OutCircle(Point p1, Point p2, Point p3)
{
    double bx = p2.x - p1.x, by = p2.y - p1.y;
    double cx = p3.x - p1.x, cy = p3.y - p1.y;
    double d = 2 * (bx * cy - by * cx);
    double px = (cy * (bx * bx + by * by) - by * (cx * cx + cy * cy)) / d + p1.x;
    double py = (bx * (cx * cx + cy * cy) - cx * (bx * bx + by * by)) / d + p1.y;
    Point p = Point(px, py);
    return Circle(p, Length(p1 - p));
}

//[21]三角形内切圆
Circle InCircle(Point p1, Point p2, Point p3)
{
    double a = Length(p2 - p3);
    double b = Length(p3 - p1);
    double c = Length(p1 - p2);
    Point p = (p1 * a + p2 * b + p3 * c) / (a + b + c); 
    return Circle(p, DistanceToLine(p, p1, p2));
}

//[22]点在多边形内判断
//(1)点编号 [0, n)
//(2)返回值: -1:在边界上 1:在内部 0:在外部
int IsPointInPolygon(Point p, Point poly[], int n)
{
    int i, k, d1, d2, wn = 0;
    for (i = 0; i < n; i++)
    {
        if (OnSegment(p, poly[i], poly[(i + 1) % n])) return -1;   //在边界上
        k = dcmp(Cross(poly[(i + 1) % n] - poly[i], p - poly[i]));
        d1 = dcmp(poly[i].y - p.y);
        d2 = dcmp(poly[(i + 1) % n].y - p.y); 
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if (wn != 0) return 1;   //内部
    return 0;   //外部
}

//[23]计算凸包    切记:输入不能有重复点
//(1)输入点数组为p, 下标[0,n)! 凸包数组为ans, 下标[0,m). 函数返回凸包顶点数!
//(2)输入不能有重复点, 函数执行完之后输入点的顺序被破坏
//(3)如果希望在凸包的边上有输入点, 把两个 <= 改成 <
//(4)精度要求高时建议用dcmp比较
//(5)时间复杂度: O(nlogn)

int cmp(const Point &a, const Point &b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

int ConvexHull(Point p[], int n, Point ans[])
{
    int i, k, m = 0;
    sort (p, p + n, cmp);   //先比较x坐标, 再比较y坐标
    for (i = 0; i < n; i++)
    {
        while (m > 1 && dcmp(Cross(ans[m - 1] - ans[m - 2], p[i] - ans[m - 2])) <= 0) m--; 
        ans[m++] = p[i];
    }
    k = m;
    for (i = n - 2; i >= 0; i--)
    {
        while (m > k && dcmp(Cross(ans[m - 1] - ans[m - 2], p[i] - ans[m - 2])) <= 0) m--;
        ans[m++] = p[i];
    }
    if (n > 1) m--;
    return m;
}

