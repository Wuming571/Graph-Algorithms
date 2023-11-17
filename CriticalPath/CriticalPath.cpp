#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#define OK 1
#define ERROR 0
#define MVNum 100
typedef int Status;
typedef char VerTexType;
typedef char OtherInfo;
int indegree[MVNum] = { 0 };//结点的入度个数
int m;//************逆序拓扑用(局部变量变全局） 
//创建栈 
typedef struct StackNode {
	int data;
	struct StackNode* next;
}StackNode, * StackList;
//出栈函数 
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
//入栈函数： 
StackList Push(StackList S, int e)
{
	StackList p;
	p = (StackNode*)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S;
	S = p;
	return S;
}

//邻接表创建有向图的实现
//边结点 
typedef struct ArcNode {    //链表结点
	int adjvex;           //邻接表创建无向网的实现
	struct ArcNode* nextarc;    //指向下一条边的指针
	int info;       //*****和边相关的信息--权值*****
}ArcNode;

//顶点信息 
typedef struct VNode {   //头结点
	VerTexType data;   //顶点信息
	ArcNode* firstarc;//指向第一条依附该顶点的边的指针
}VNode, AdjList[MVNum];//AdjList 表示邻接表类型

typedef struct {
	AdjList vertices;     //邻接表头结点数组
	int vexnum, arcnum;   //图的顶点数和弧数
}ALGraph;

//创建有向图：
int LocateVex(ALGraph* G, VerTexType v)  //G带操作的图；v要在图中定位的顶点
{
	int i;
	for (i = 0; i < (G->vexnum); i++)
	{
		if (v == G->vertices[i].data)
			return i;               //顶点存在则返回在头结点数组中的下标；否则返回
	}
}

void CreateUDG(ALGraph* G)
{
	int i, j, k;
	VerTexType v1, v2;
	ArcNode* p1;
	int w;//*****权值***** 
	printf("输入总节点数和弧数：\n"); //G带操作的图；v要在图中定位的顶点
	std::cin >> G->vexnum >> G->arcnum;
	//fflush(stdin);    //是清空输入缓冲区的
	//G->vexnum = 9;
	//G->arcnum = 11;

	printf("输入各个节点的值：\n");
	for (i = 0; i < G->vexnum; i++)   //邻接表初始化
	{
		std::cin>>G->vertices[i].data;
		G->vertices[i].firstarc = NULL;
	}
	printf("输入各条边的数据：\n");//*********
	
	//char vexs[9] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };                                                                                                                                                   // 顶点信息
	//char arcs[11][3] = { {'A', 'B', '6'}, {'A', 'C', '4'}, {'A', 'D', '5'}, {'B', 'E', '1'}, {'C', 'E', '1'}, {'D', 'F', '2'}, {'E', 'G', '9'}, {'E', 'H', '7'}, {'F', 'H', '4'}, {'G', 'I', '2'}, {'H', 'I', '4'} }; // 边信息
	for (int i = 0; i < G->vexnum; i++)                                                                                                                                                                             // 初始化顶点数组
	{
		std::cin >> G->vertices[i].data;
		G->vertices[i].firstarc = NULL;
	}
	for (k = 0; k < G->arcnum; k++)
	{
		std::cin >> v1 >> v2 >> w;
		//v1 = arcs[k][0];
		//v2 = arcs[k][1];
		//w = arcs[k][2] - '0';
		//i = LocateVex(G, v1);   //返回这两个顶点在顶点数组中的位置
		j = LocateVex(G, v2);
		p1 = (ArcNode*)malloc(sizeof(ArcNode));   //给邻接表指针分配空间
		p1->adjvex = j;
		p1->info = w;                       //赋值给p->adjvex指向的顶点域
		p1->nextarc = G->vertices[i].firstarc; //nextarc指针域指向i结点的firstarc指针域  
		G->vertices[i].firstarc = p1;    //将点i的第一条指针指向
		indegree[j]++;
	}
}

int TopoSort(ALGraph G, int* etv, int* topo)
{
	StackList S;//声明一个栈指针
	ArcNode* p;
	int index;
	m = 0;//***********下标 用于存储拓扑序列
	S = NULL;

	for (int i = 0; i < G.vexnum; i++)
	{
		etv[i] = 0;//*********初始化etv数组 
	}

	for (int i = 0; i < G.vexnum; i++)
	{
		if (indegree[i] == 0)
		{
			S = Push(S, i);
		}

	}
	int k;//******下面循环中 index的邻接点 
	while (S)//栈不为空 就继续跑
	{
		S = Pop(S, &index);
		topo[m] = index;
		m++;
		//删边 index相邻的点的入度-1
		p = G.vertices[index].firstarc;
		while (p != NULL)
		{
			k = p->adjvex;//********
			--indegree[k];//********
			if (indegree[k] == 0)//********
			{
				S = Push(S, k);//********
			}
			//********求顶点K最早发生时间
			if (etv[index] + (p->info) > etv[k])
			{
				etv[k] = etv[index] + (p->info);
			}

			p = p->nextarc;

		}

	}
	topo[m] = -1;//-1代表结尾
	//判断一下是否成环
	if (m < G.vexnum)
	{
		//成环
		return 0;
	}
	else
	{
		//不成环
		return 1;
	}
}
//求关键路径 
void CriticalPath(ALGraph G, int* etv, int* ltv)
{
	int topo[99] = { 0 };
	ArcNode* p;
	int ete, lte;//此处其实没必要用数组
	if (TopoSort(G, etv, topo))
	{
		//初始化事件最晚发生时间
		int x = topo[m - 1];//x是拓扑序列的终点，也是图汇点 
		for (int i = 0; i < G.vexnum; i++)
		{
			ltv[i] = etv[x];
		}
		//逆拓扑 求事件最晚发生时间
		while (m != 0)
		{
			m--;
			int gettop = topo[m];
			for (p = G.vertices[gettop].firstarc; p; p = p->nextarc)
			{
				int k = p->adjvex;
				if (ltv[k] - p->info < ltv[gettop])
				{
					ltv[gettop] = ltv[k] - p->info;
				}
			}

		}
		//求活动的最早和最晚,顺便输出关键路径，通过点遍历所有的边，时间复杂度O（E） 
		printf("以下是关键路径：\n");
		for (int i = 0; i < G.vexnum; i++)
		{
			for (p = G.vertices[i].firstarc; p; p = p->nextarc)
			{
				int k = p->adjvex;
				ete = etv[i];
				lte = ltv[k] - p->info;
				if (ete == lte)//输出关键路径的边 
				{
					printf("%c %c : %d\n", G.vertices[i].data, G.vertices[k].data, p->info);
				}
			}
		}

	}

}
int main()
{
	ALGraph G;
	CreateUDG(&G);
	int* ltv = (int*)malloc(G.vexnum * sizeof(int));
	int* etv = (int*)malloc(G.vexnum * sizeof(int));
	CriticalPath(G, etv, ltv);

	return 0;
}
/*
9 11
A B C D E F G H I
A B 6
A C 4
A D 5
B E 1
C E 1
D F 2
E G 9
E H 7
F H 4
G I 2
H I 4

*/
