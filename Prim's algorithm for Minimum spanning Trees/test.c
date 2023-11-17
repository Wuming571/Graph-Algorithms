#include <stdio.h>
#include <stdbool.h>
#define INF 65535

int g[105][105];//g二维数组存放邻接矩阵来存储图
int nv, ne;
int dist[105];//dist用来代表未添加到最小生成树中点在B集合中到 A集合的距离
bool vi[105];//0代表没有添加到生成树中

void prim() {
	//让第一个结点到A集合，最为最小生成树的根节点
	dist[0] = 0;
	vi[0] = 1;
	for (int i = 1; i < nv; i++)
		dist[i] = g[0][i];
	//开始顺着起始点寻找权值最小的点
	int minn;//保存找到点p的编号，邻接点
	int tmpd;//保存dist的值,最小权值
	for (int i = 1; i < nv; i++) {
		minn = -1;
		tmpd = INF;
		for (int j = 0; j < nv; j++) {
			//确保是在B集合中，并且权值要更小
			if (vi[j] == 0 && dist[j] < tmpd) {
				minn = j;
				tmpd = dist[j];
			}
		}
		if (minn == -1)
			return;
		printf("把点%d的，通过权为%d的边加入到生成树中\n", minn, tmpd);
		//对B集合进行更新，更改临近点的权值
		vi[minn] = true;
		for (int j = 1; j < nv; j++)
			dist[j] = (dist[j] < g[minn][j]) ? dist[j] : g[minn][j];
	}
}

int main() {
	//创建邻接矩阵
	scanf_s("%d%d", &nv, &ne);
	for (int i = 0; i < nv; i++) {
		for (int j = 0; j < nv; j++) {
			if (i == j)
				g[i][j] = 0;
			else
				g[i][j] = g[j][i] = INF;
		}
	}
	int x, y, wi;
	for (int i = 0; i < ne; i++) {
		scanf_s("%d%d%d", &x, &y, &wi);
		g[x][y] = g[y][x] = wi;
	}
	//B中集合到A的距离全部初始化为无穷大
	for (int i = 0; i < nv; i++) 
		dist[i] = INF;
	prim();
	return 0;
}