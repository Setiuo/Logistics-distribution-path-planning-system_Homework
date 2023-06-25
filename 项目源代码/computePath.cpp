#include<iostream>
#include<map>
#include<stdlib.h>
#include<ctime>
#include <math.h>
using namespace std;
int task;//送货点任务数
int n;
int s_bird = 50;//粒子数量
int sum = 100;//更新次数
double Map[100][100];//送货点不超过100
double r1 = 100;
double r2 = 100;///百分之r1，r2
double inf = 9999999;
struct Swap
{
    int x, y;
};
struct best
{
    double ans;
    int x[409];
} gbest, pbest[1009];//粒子群和粒子的最优解

struct bird//粒子
{
    int x[100];///n维坐标
    Swap v[100];///交换序
    int sv;
} p[1009];

struct Point
{
    double x, y;
};
Point  dot[110];

void init(int num, int _dot[110][2])//初始化城市模型（图）
{
    task = num;
    n = task;

    for (int i = 1; i <= n; i++){
       dot[i].x = _dot[i][0];
       dot[i].y = _dot[i][1];
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            Map[i][j] = sqrt((dot[i].x - dot[j].x) * (dot[i].x - dot[j].x) + (dot[i].y - dot[j].y) * (dot[i].y - dot[j].y));
        }
    }

}
void init_niziqun()//初始化粒子群
{

    for (int i = 1; i <= s_bird; i++)///初始化位置
    {
        ///初始化位置------------------------
        pbest[i].ans = inf;
        int now_task[109];
        for (int j = 1; j <= n; j++)
        {
            now_task[j] = (rand() % 1000);///1000以内的整数
        }
        int now_adr[109];
        for (int j = 1; j <= n; j++)
        {
            now_adr[j] = j;///第i个点
        }
        // double now_ans=0;
        for (int k = 1; k <= n; k++)///对每个点按优先级进行排序
        {
            for (int j = k + 1; j <= n; j++)
            {
                if (now_task[k] > now_task[j])
                {
                    swap(now_task[k], now_task[j]);
                    swap(now_adr[k], now_adr[j]);
                }
            }
        }
        for (int j = 1; j <= n; j++)p[i].x[j] = now_adr[j];
        ///初始化速度（交换序）---------------------
        int s_swap = rand() % n + 1;///第i个粒子具有多少个交换算子
        p[i].sv = s_swap;
        for (int j = 1; j <= s_swap; j++)
        {
            int tx = rand() % n + 1, ty = rand() % n + 1;
            while (tx == ty)ty = rand() % n + 1;
            p[i].v[j].x = tx;
            p[i].v[j].y = ty;
        }
    }
    gbest.ans = inf;
}
void value(int adr)//计算一个粒子的答案
{
    double now_ans = 0;
    for (int i = 2; i <= n; i++)now_ans += Map[p[adr].x[i - 1]][p[adr].x[i]];
    now_ans += Map[p[adr].x[n]][p[adr].x[1]];//形成环
    if (now_ans < pbest[adr].ans)//更新该点的最优位置
    {
        pbest[adr].ans = now_ans;
        for (int i = 1; i <= n; i++)pbest[adr].x[i] = p[adr].x[i];
    }

    if (now_ans < gbest.ans)//更新全局最优位置
    {
        gbest.ans = now_ans;
        for (int i = 1; i <= n; i++)gbest.x[i] = p[adr].x[i];

    }
}

void update(int adr)//迭代粒子群
{

    int pbestx[110];
    int px[110];
    map<int, int >pbestp;
    map<int, int >pxp;
    for (int i = 1; i <= n; i++)
    {
        pbestx[i] = pbest[adr].x[i];
        pbestp[pbestx[i]] = i;

        px[i] = p[adr].x[i];
        pxp[px[i]] = i;
    }
    int i = 1;
    while (i <= n)
    {
        if (pbestx[i] != px[i])
        {
            int seekp = pbestp[px[i]];

            swap(pbestx[i], pbestx[seekp]);
            int Tr1 = rand() % 100;
            if (Tr1 < r1) {///以r1/100的概率保留该交换子
                p[adr].sv++;
                p[adr].v[p[adr].sv].x = i;
                p[adr].v[p[adr].sv].y = seekp;
            }
        }
        i++;
    }
    int gbestx[115];
    map<int, int >gbestp;
    for (i = 1; i <= n; i++)
    {
        gbestx[i] = gbest.x[i];
        gbestp[gbest.x[i]] = i;
    }
    i = 1;
    while (i <= n)
    {
        if (gbestx[i] != px[i])
        {
            int seekg = gbestp[px[i]];
            swap(pbest[i], pbest[seekg]);
            int Tr2 = rand() % 100;
            if (Tr2 < r2)
            {
                p[adr].sv++;
                p[adr].v[p[adr].sv].x = i;
                p[adr].v[p[adr].sv].y = seekg;
            }
        }
        i++;
    }
    int ta1[115], ta2[115];
    for (i = 1; i <= n; i++)ta1[i] = i, ta2[i] = i;
    i = 1;
    while (i <= p[adr].sv)
    {
        swap(ta1[p[adr].v[i].x], ta1[p[adr].v[i].y]);
        i++;
    }
    map<int, int >pta;
    for (i = 1; i <= n; i++)
    {
        pta[ta1[i]] = i;
    }
    i = 1;
    p[adr].sv = 0;///重新构造交换序
    while (i <= n)
    {
        if (ta1[i] != i)
        {
            int seekt = pta[i];
            swap(ta1[i], ta1[seekt]);
            p[adr].sv++;
            p[adr].v[p[adr].sv].x = i;
            p[adr].v[p[adr].sv].y = seekt;
        }
        i++;
    }
    for (i = 1; i <= p[adr].sv; i++)
    {
        int swx = p[adr].v[i].x, swy = p[adr].v[i].y;
        swap(p[adr].x[swx], p[adr].x[swy]);
    }
    value(adr);
}
int computePath(int num, int _dot[110][2], int result[110])
{
    double tss = 0;
    init(num, _dot);//读入图
    double Maxans = inf;
    int anskk = 0;
    srand((unsigned)time(NULL));

    init_niziqun();//初始化粒子群


    for (int i = 1; i <= s_bird; i++) value(i);//更新粒子群和粒子的最优值
    sum = 100;
    while (sum--)
    {
        for (int i = 1; i <= s_bird; i++)
        {
            update(i);//迭代粒子群
        }
    }
    if (gbest.ans < Maxans)
        Maxans = gbest.ans;

    for (int i = 1; i <= n; i++){
        result[i]= gbest.x[i];
        cout << dot[gbest.x[i]].x << ' ' << dot[gbest.x[i]].y << endl;///输出路径
    }

    //cout << "最佳答案>>>>>>>>>>>>>>>>>>>" << Maxans << endl;
    return 0;
}
