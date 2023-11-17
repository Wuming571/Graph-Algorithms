#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MVNum 100
int indegree[MVNum] = { 0 };

//创建链栈
//StackNode代表栈结点 *StackList代表整个栈
typedef struct StackNode {
	int data;
	struct StackNode* next;
}StackNode, * StackList;
//出栈函数Pop
StackList Pop(StackList S, int* e) {
	StackList p;
	p = S;
	//栈空报错
	if (!p)
		return false;
	*e = p->data;//出栈值赋给e
	S = S->next;
	free(p);
	return S;
}
//入栈函数Push
StackList Push(StackList S, int e) {
	StackList p;
	p = (StackNode*)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S;
	S = p;
	return S;
}

//邻接表 有向图
//边表结构
typedef struct EdgeNode {
	int adjvex;
	struct EdgeNode* next;
}EdgeNode;
//顶点信息
typedef struct VertexNode {
	char data;
	struct EdgeNode* first;
}VertexNode;
//邻接表结构存图
typedef struct GraphadjList {
	VertexNode adjList[100];
	int numV, numE;
}GraphadjList;
//无向邻接链表创建
void CreatALGraph(GraphadjList* G) {
	G->numV = 6;
	G->numE = 8;
	char datas[] = { 'A','B','C','D','E','F' };
	int edge[][2] = { {0,1},{0,2},{0,3},{2,1},{2,4},{3,4},{5,3} ,{5,4} };
	EdgeNode* e;
	int vi, vj;
	//建立边表
	for (int i = 0; i < G->numE; i++) {
		G->adjList[i].data = datas[i];
		G->adjList[i].first = NULL;
	}
	for (int i = 0; i < G->numE; i++) {
		vi = edge[i][0];
		vj = edge[i][1];
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex = vj;
		e->next = G->adjList[vi].first;
		G->adjList[vi].first = e;
		indegree[vj]++;
	}
}
//进行拓扑排序 TopoSort
//topo指针传数组代表，存储最后整个拓扑序列
int TopoSort(GraphadjList G,int* topo){
	StackList S = NULL;//S声明栈指针
	EdgeNode* p;//临时指针p，存储结点指向的结点
	int index;//index存储删除结点信息
	int m = 0;//下标m 用于存储拓扑序列，
	
	//入度为0的先入栈
	for (int i = 0; i < G.numV; i++) {
		if (indegree[i] == 0)
			S = Push(S, i);
	}
	
	//栈不为空就继续跑
	while (S) {
		S = Pop(S, &index);
		topo[m] = index;
		m++;
		p = G.adjList[index].first;
		//删边 index相邻的点的入度-1
		for (int i = 0; i < G.numV; i++) {
			indegree[p->adjvex] - 1;
			p = p->next;
			if (indegree[p->adjvex] == 0)
				S = Push(S, p->adjvex);
		}
	}
	//-1代表结尾
	topo[m + 1] = -1;
	//判断一下是否成环
	if (m == G.numV)
		return true;
	else
		return false;
}

int main() {
	GraphadjList G;
	int topo[99] = { 0 };
	CreatALGraph(&G);
	if (TopoSort(G, topo)) {
		for (int i = 0; topo[i] != -1; i++)
			printf("%c", G.adjList[topo[i]].data);
	}
	return 0;
}