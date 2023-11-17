#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define MVNum 100
typedef int Status;
typedef char VerTexType;
typedef char OtherInfo;
int indegree[MVNum] = {0}; // 结点的入度个数

// 创建栈
typedef struct StackNode
{
	int data;
	struct StackNode *next;
} StackNode, *StackList;
// 出栈函数
StackList Pop(StackList S, int *e)
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
	p = (StackNode *)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S;
	S = p;
	return S;
}

// 邻接表创建有向图的实现
// 边结点
typedef struct ArcNode
{							 // 链表结点
	int adjvex;				 // 邻接表创建无向网的实现
	struct ArcNode *nextarc; // 指向下一条边的指针
							 // OtherInfo info;       //和边相关的信息
} ArcNode;

// 顶点信息
typedef struct VNode
{						 // 头结点
	VerTexType data;	 // 顶点信息
	ArcNode *firstarc;	 // 指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNum]; // AdjList 表示邻接表类型

typedef struct
{
	AdjList vertices;	// 邻接表头结点数组
	int vexnum, arcnum; // 图的顶点数和弧数
} ALGraph;

// 创建有向图：
int LocateVex(ALGraph *G, VerTexType v) // G带操作的图；v要在图中定位的顶点
{
	int i;
	for (i = 0; i < (G->vexnum); i++)
	{
		if (v == G->vertices[i].data)
			return i; // 顶点存在则返回在头结点数组中的下标；否则返回
	}
}

void CreateUDG(ALGraph *G)
{
	int i, j, k;
	VerTexType v1, v2;
	ArcNode *p1;
	printf("输入总节点数和弧数：\n"); // G带操作的图；v要在图中定位的顶点
	scanf_s("%d %d", &G->vexnum, &G->arcnum);
	fflush(stdin); // 是清空输入缓冲区的
	printf("输入各个节点的值：\n");
	for (i = 0; i < G->vexnum; i++) // 邻接表初始化

	{
		scanf_s("%c", &G->vertices[i].data);
		getchar();
		G->vertices[i].firstarc = NULL;
	}

	for (k = 0; k < G->arcnum; k++)
	{
		// fflush(stdin);   //是清空输入缓冲区的
		scanf_s("%c", &v1);
		getchar();
		scanf_s("%c", &v2);
		getchar();
		i = LocateVex(G, v1); // 返回这两个顶点在顶点数组中的位置
		j = LocateVex(G, v2);
		p1 = (ArcNode *)malloc(sizeof(ArcNode)); // 给邻接表指针分配空间
		p1->adjvex = j;							 // 赋值给p->adjvex指向的顶点域
		p1->nextarc = G->vertices[i].firstarc;	 // nextarc指针域指向i结点的firstarc指针域
		G->vertices[i].firstarc = p1;			 // 将点i的第一条指针指向
		indegree[j]++;
	}
}

int TopoSort(ALGraph G, int *topo)
{
	StackList S; // 声明一个栈指针
	ArcNode *p;
	int index;
	int m = 0; // 下标 用于存储拓扑序列
	S = NULL;
	for (int i = 0; i < G.vexnum; i++)
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
		p = G.vertices[index].firstarc;
		while (p != NULL)
		{
			--indegree[p->adjvex];
			if (indegree[p->adjvex] == 0)
			{
				S = Push(S, p->adjvex);
			}
			p = p->nextarc;
		}
	}
	topo[m] = -1; //-1代表结尾
	// 判断一下是否成环
	if (m < G.vexnum)
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
	ALGraph G;
	int topo[99] = {0};
	CreateUDG(&G);
	if (TopoSort(G, topo))
	{
		for (int i = 0; topo[i] != -1; i++)
		{
			printf("%c ", G.vertices[topo[i]].data);
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
