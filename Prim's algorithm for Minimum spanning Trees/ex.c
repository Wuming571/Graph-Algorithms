#include <stdio.h>
#include <stdbool.h>
#define INF 65535

//g二维数组存放邻接矩阵来存储图
int g[105][105];
int nv, ne;
//dist用来代表未添加到最小生成树中点在B集合中到 A集合的距离
int dist[105];
//0代表没有添加到生成树中
bool vi[105];

void prim() {
	//让第一个结点到A集合，最为最小生成树的根节点
	dist[0] = 0;
	vi[0] = 1;
	for (int i = 1; i < nv; i++)
		dist[i] = g[0][i];
	//开始顺着起始点寻找权值最小的点
	int minn;
	int tmpd;

	for (int i = 1; i < nv; i++) {
		//这两行代码是必须有的，在每找到一个结点的时候需要重新，
		// 对暂存的编号和权值进行初始化
		minn = -1;//保存找到点p的编号，邻接点int minn;	
		tmpd = INF;//保存dist的值,最小权值
		for (int j=0; j < nv; j++) {
			//确保是在B集合中，并且权值要更小
			if (vi[j] == false && dist[j] < tmpd) {
				minn = j;
				tmpd = dist[j];	
			}

		}
		//入过未找到说明该连通图已找完
	if (minn == -1)
		return;
	printf("%d %d\n", minn, tmpd);
	vi[minn] = true;
	for (int j = 1; j < nv; j++) {
		if (dist[j] > g[minn][j])
			dist[j] = g[minn][j];
	}
		//对B集合进行更新，更改临近点的权值
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
	for (int i = 0; i < nv; i++) {
		dist[i] = INF;
	}
	prim();

	return 0;
}