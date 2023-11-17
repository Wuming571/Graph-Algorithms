#include <stdio.h>
//#include <stdlib.h>
#define INF 65535

int g[105][105];
int nv, ne, v;//v是源点
int dist[105], path[105];
int ch[105];
void dijkstra() {
	for (int i = 0; i < ne; i++)
	{
		dist[i] = g[v][i];
		if (g[v][i] != INF)
		{
			path[i] = v;
		}
	}
	int minn;//最小的dist 
	int k;//最小dist值是k点 
	for (int i = 1; i < nv; i++)
	{
		minn = INF;
		for (int j = 0; j < nv; j++)//找最小的dist 
		{
			if (ch[j] == 0 && dist[j] < minn)
			{
				minn = dist[j];
				k = j;
			}

		}
		ch[k] = 1;
		for (int j = 0; j < nv; j++)
		{
			if (ch[j] == 0 && dist[k] + g[k][j] < dist[j])
			{
				dist[j] = dist[k] + g[k][j];
				path[j] = k;
			}
		}

	}

}

int main()
{
	int x, y, w;
	scanf_s("%d %d", &nv, &ne);
	for (int i = 0; i < nv; i++)
	{
		for (int j = 0; j < nv; j++)
		{
			if (i == j)g[i][j] = g[j][i] = 0;
			else
				g[i][j] = g[j][i] = INF;
		}
	}
	for (int i = 0; i < ne; i++)
	{
		scanf_s("%d %d %d", &x, &y, &w);
		g[x][y] = g[y][x] = w;
	}
	scanf_s("%d", &v);//输入起点
	for (int i = 0; i < nv; i++)
	{
		dist[i] = INF;
	}

	dist[v] = 0;
	ch[v] = 1;
	path[v] = v;

	dijkstra();

	for (int i = 0; i < nv; i++)
	{
		printf("源点%d到%d的最短路径长度是:%d----", v, i, dist[i]);
		//倒序输出最短路径
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
/*
9 16
0 1 1
0 2 5
1 2 3
1 3 7
1 4 5
2 4 1
2 5 7
3 4 2
3 6 3
4 5 3
4 6 6
4 7 9
5 7 5
6 7 2
6 8 7
7 8 4
0
*/
