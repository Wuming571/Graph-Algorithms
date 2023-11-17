#include <stdio.h>
#include <stdbool.h>
#define INF 65535
/*
最小生成树---prim算法：选点，也在选边
维护一个dist[]，点到生成树的距离，初始化无穷
1.选起点加到生成树中
2。用起点去更新 与起点直接相连，并且还未加入到生成树中的点的dist
3.n-1次循环：（1）选dist值最小的点（p点）加入生成树，用p点更新 与p点直接相连，并且还未加入到生成树中的点的dist
时间复杂度： O(V^2) ----适合 稠密图
*/
// 邻接矩阵存图--带权无向图
int g[105][105]; // 假设最多有100个点
int dist[105];
bool vi[105]; // 0 代表没有加入到生成树
int nv, ne;

void prim()
{
    dist[0] = 0;
    vi[0] = 1;
    for (int i = 1; i < nv; i++)
        dist[i] = (dist[i] < g[0][i]) ? dist[i] : g[0][i];
    int minn;
    int tmpd;
    for (int i = 1; i < nv; i++) // 循环nv-1次
    {
        minn = -1;  // 保存 p点的编号
        tmpd = INF; // 保存dist值
        for (int j = 0; j < nv; j++)
        {
            if (vi[j] == 0 && dist[j] < tmpd)
            {
                minn = j;
                tmpd = dist[j];
            }
        }
        if (minn == -1)
            return;
        printf("本次把点%d，通过边权为 %d的边加入到生成树中\n", minn, tmpd);
        vi[minn] = 1;
        for (int j = 1; j < nv; j++)
            dist[j] = (dist[j] < g[minn][j]) ? dist[j] : g[minn][j];
    }
}
int main()
{
    scanf_s("%d %d", &nv, &ne);

    for (int i = 0; i < nv; i++)
        for (int j = 0; j < nv; j++)
        {
            if (i == j)
                g[i][j] = g[j][i] = 0;
            else
                g[i][j] = g[j][i] = INF;
        }
    for (int i = 0; i < nv; i++)
        dist[i] = INF;
    int x, y, wi;
    for (int i = 0; i < ne; i++)
    {
        scanf_s("%d %d %d", &x, &y, &wi);
        g[x][y] = g[y][x] = wi;
    }
    prim();

    return 0;
}
/*
测试用例：讲义上的图
9 15
0 1 3
0 5 4
1 6 6
6 5 7
1 2 8
1 8 5
2 8 2
2 3 12
8 3 11
6 3 14
6 7 9
5 4 18
3 7 6
7 4 1
3 4 10
*/
