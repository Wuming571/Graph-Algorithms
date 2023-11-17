#include <stdio.h>
#include <stdlib.h>
#define ERROR 0
#define MVNum 100
int indegree[MVNum] = { 0 }; // 结点的入度个数

// 创建栈
typedef struct StackNode
{
	int data;
	struct StackNode* next;
} StackNode, * StackList;
// 出栈函数
StackList Pop(StackList S, int* e)
{
	StackList p;
	p = S;
	if (!p)
		return ERROR;
	*e = p->data;
	S = S->next;
	free(p);
	return S;
}
// 入栈函数：
StackList Push(StackList S, int e)
{
	StackList p;
	p = (StackNode*)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S;
	S = p;
	return S;
}

//邻接表

//边表结点
typedef struct EdgeNode {
	int adjvex;//邻接的结点的下标
	struct EdgeNode* next;//指向下一个边
	int weight;//权值
}EdgeNode;
//顶点的信息，指向边表结点
typedef struct VertexNode {
	char data;//基本的数据，顶点域存放结点信息
	struct EdgeNode* first;
}VertexNode;
//邻接表结构，存图包含顶点的信息
typedef struct GraphadjList {
	VertexNode adjList[100];//顶点表的结点数组
	int numV, numE;//顶点个数和边的个数
}GraphadjList;
//无向图的邻接表的创建
void CreatALGraph(GraphadjList* G) {

	G->numV = 6; // 6个顶点
	G->numE = 8; // 8条边

	char datas[] = { 'A', 'B', 'C', 'D', 'E', 'F' }; // 顶点数据
	int edges[][2] = { {0, 1}, {0, 2}, {0, 3}, {2, 1}, 
		{2, 4}, {3, 4}, {5, 3}, {5, 4} }; // 边的连接情况

	EdgeNode* e;
	int vi, vj;

	//建立边表
	for (int i = 0; i < G->numE; i++) {
		G->adjList[i].data = datas[i];
		G->adjList[i].first = NULL;
	}
	for (int i = 0; i < G->numV; i++) {
		//这里输入的就是结点的位置，不需要在找下标
		vi = edges[i][0];
		vj = edges[i][1];
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex = vj;
		//找到要建立关系结点的下表		
		//进行头插法插入
		e->next = G->adjList[vi].first;
		G->adjList[vi].first = e;
		indegree[vj]++;
	}
}

int TopoSort(GraphadjList G, int* topo)
{
	StackList S; // 声明一个栈指针
	EdgeNode* p;
	int index;
	int m = 0; // 下标 用于存储拓扑序列
	S = NULL;
	for (int i = 0; i < G.numV; i++)
	{
		if (indegree[i] == 0)
		{
			S = Push(S, i);
		}
	}

	while (S) // 栈不为空 就继续跑
	{
		S = Pop(S, &index);
		topo[m] = index;
		m++;
		// 删边 index相邻的点的入度-1
		p = G.adjList[index].first;
		while (p != NULL)
		{
			--indegree[p->adjvex];
			if (indegree[p->adjvex] == 0)
			{
				S = Push(S, p->adjvex);
			}
			p = p->next;
		}
	}
	topo[m] = -1; //-1代表结尾
	// 判断一下是否成环
	if (m < G.numV)
	{
		// 成环
		return 0;
	}
	else
	{
		// 不成环
		return 1;
	}
}

int main()
{
	GraphadjList G;
	int topo[99] = { 0 };
	CreatALGraph(&G);
	if (TopoSort(G, topo))
	{
		for (int i = 0; topo[i] != -1; i++)
		{
			printf("%c ", G.adjList[topo[i]].data);
		}
	}

	return 0;
}
/*
6 8

A B C D E F

A B
A C
A D
C B
C E
D E
F D
F E
*/
