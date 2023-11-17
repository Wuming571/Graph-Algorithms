#include <stdio.h>
#include <stdlib.h>
#define INF 65535
/*找最小生成树---->选出n-1条边：

1.选出n-1条权值尽量小的边： 每次都选新的最小的边E---基于贪心
2. 其中不能出现环 ：采用并查集，判断一下 E的两个端点是不是属于同一个连通集合：
(1)yes,说明E不能选  (2)no, 说明要选E

Kruskal的思路 ---贪心（贪婪）思想 ：趋利避害   目光短浅

时间复杂度：在并查集采用路径压缩的基础上 O(eloge) ----适合 稀疏图
*/

//邻接矩阵存图——带权无向图
int g[105][105];//假设最多100个点
int nv, ne;

//边集数组来存储升序排列的边表结构？
typedef struct {
	int u, v;//端点
	int w;//权值
}Edge;

Edge e[5005];

void sorte(int l, int r) {
	//选择
	int minn;
	Edge tmp;
	for (int i = l; i < r; i++) {
		minn = i;
		for (int j = i + 1; j < r; j++) {
			if (e[minn].w > e[j].w)
				minn = j;
		}
		tmp = e[i];
		e[i] = e[minn];
		e[minn] = tmp;
	}
	//输出排序之后的结果
	printf("按权值升序排列：\n");
	for (int i = 0; i < r; i++)
		printf("(%d %d) %d\n", e[i].v, e[i].u, e[i].w);
}
//并查集中
int find(int* f, int z) {
	while (z != f[z])
		z = f[z];
	return z;
}

void Kruskal() {
	int f[105];
	for (int i = 0; i < nv; i++) {
		f[i] = i;
	}
	printf("以下是最小生成树的边：\n");
	//根据并查集判断是否形成环
	for (int i = 0; i < ne; i++) {
		int fu = find(f, e[i].u);
		int fv = find(f, e[i].v);
		//看看两个结点是否在同一个集合中
		if (fu != fv) {
			f[fv] = fu;
			printf("(%d %d) %d\n", e[i].v, e[i].u, e[i].w);
		}
	}
}

int main() {
	//用邻接矩阵创建图
	scanf_s("%d%d", &nv, &ne);
	//对二维边表数组进行初始化
	for (int i = 0; i < nv; i++) {
		for (int j = 0; j < nv; j++) {
			if (i == j) {
				g[i][j] = g[j][i] = 0;
			}
			else {
				g[i][j] = g[j][i] = INF;
			}
		}
	}
	//弧头，弧尾，权值
	int x, y, wi;
	int k = 0;//边数组的下标
	//进行创建
	for (int i = 0; i < ne; i++) {
		scanf_s("%d%d%d", &x, &y, &wi);
		g[x][y] = g[y][x] = wi;
		//先把数据整体输入边集数组中
		e[k].v = x;
		e[k].u = y;
		e[k].w = wi;
		k++;
	}
	sorte(0, k);
	Kruskal();

	return 0;
}