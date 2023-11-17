#include <stdio.h>
#include <stdlib.h>
#define INF 65535
/*找最小生成树---->选出n-1条边：

1.选出n-1条权值尽量小的边： 每次都选新的最小的边E---基于贪心
2. 其中不能出现环 ：   采用并查集，判断一下 E的两个端点是不是属于同一个连通集合：(1)yes,说明E不能选  (2)no, 说明要选E

Kruskal的思路 ---贪心（贪婪）思想 ：趋利避害   目光短浅

时间复杂度：在并查集采用路径压缩的基础上 O(eloge) ----适合 稀疏图
*/

//邻接矩阵存图--带权无向图 
int g[105][105];//假设最多有100个点
int nv, ne;
typedef struct {
	int u, v;//端点 
	int w;//权值 	
}Edge;
Edge e[5005];
void sorte(int l, int r)
{
	//选择
	int minn;
	Edge tmp;
	for (int i = l; i < r; i++)
	{
		minn = i;
		for (int j = i + 1; j < r; j++)
		{
			if (e[minn].w > e[j].w)
			{
				minn = j;
			}

		}
		tmp = e[i];
		e[i] = e[minn];
		e[minn] = tmp;
	}
	//输出排序之后的结果；
	printf("按权值升序排列：\n");
	for (int i = 0; i < r; i++)
	{
		printf("(%d %d) %d\n", e[i].v, e[i].u, e[i].w);
	}
}
int find(int* f, int z)
{
	while (z != f[z])
	{
		z = f[z];
	}
	return z;
}
void Kruskal()
{
	int f[105];
	for (int i = 0; i < nv; i++)
	{
		f[i] = i;
	}
	printf("以下是最小生成树的边：\n");
	for (int i = 0; i < ne; i++)
	{
		int fu = find(f, e[i].u);
		int fv = find(f, e[i].v);

		if (fu != fv)
		{
			f[fv] = fu;//合并 
			printf("(%d %d) %d\n", e[i].v, e[i].u, e[i].w);
		}
	}

}
int main()
{
	scanf_s("%d %d", &nv, &ne);
	for (int i = 0; i < nv; i++)
		for (int j = 0; j < nv; j++)
		{
			if (i == j)
			{
				g[i][j] = g[j][i] = 0;
			}
			else {
				g[i][j] = g[j][i] = INF;
			}
		}
	int x, y, wi;
	int k = 0;//边数组下标 
	for (int i = 0; i < ne; i++)
	{
		scanf_s("%d %d %d", &x, &y, &wi);
		g[x][y] = g[y][x] = wi;
		e[k].v = x;
		e[k].u = y;
		e[k].w = wi;
		k++;
	}
	sorte(0, k);
	Kruskal();

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





