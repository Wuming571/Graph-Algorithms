#include <stdio.h>
#include <stdbool.h>
#define INF 65535

// 邻接矩阵用来存图
int g[105][105];
// 点数 边数 源点
int nv, ne, v;
// dist点到源点的最短距离
int dist[105];
// path点的中转结点
int path[105];
// ch是否在最短路径中
bool ch[105];

void dijkstra()
{
    // 对源点邻接点进行初始化
    for (int i = 0; i < ne; i++) {
        dist[i] = g[v][i];
        if (g[v][i] != INF) {
            path[i] = v;
        }
    }
    // 存储dist值最小点信息
    int minn;// minn
    int k;// k
    // 开始进行查找
    for (int i = 1; i < nv; i++) {
        minn = INF;
        // 找到最小的dist
        for (int j = 0; j < nv; j++) {
            if (ch[j] == false && dist[j] < minn) {
                minn = dist[j];
                k = j;
            }
        }
        ch[k] = true;
        // 新的k点作为中转点 k临近点进行更新
        for (int j = 0; j < nv; j++) {
            if (ch[j] == false && dist[k] + g[k][j] < dist[j]) {
                dist[j] = dist[k] + g[k][j];
                path[j] = k;

            }
        }
    }
}

int main()
{
    int x, y, w;
    scanf_s("%d%d", &nv, &ne);
    for (int i = 0; i < nv; i++)
    {
        for (int j = 0; j < nv; j++)
        {
            if (i == j)
                g[i][j] = g[j][i] = 0;
            else
                g[i][j] = g[j][i] = INF;
        }
    }
    for (int i = 0; i < ne; i++)
    {
        scanf_s("%d%d%d", &x, &y, &w);
        g[x][y] = g[y][x] = w;
    }
    // 输入源点，并对源点进行初始化
    scanf_s("%d", &v);
    for (int i = 0; i < nv; i++) {
        dist[i] = INF;
    }
    dist[v] = 0;
    ch[v] = true;
    path[v] = v;

    dijkstra();

    // 进行逆序的输出路径
    for (int i = 0; i < nv; i++)
    {
        printf("%d %d %d  ", v, i, dist[i]);
        int j = i;
        printf("%d->", i);
        while (path[j] != j)
        {
            printf("%d->", path[j]);
            j = path[j];
        }
        printf("\n");
    }

    return 0;
}