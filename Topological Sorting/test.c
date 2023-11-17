#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MVNum 100
int indegree[MVNum] = { 0 };

//������ջ
//StackNode����ջ��� *StackList��������ջ
typedef struct StackNode {
	int data;
	struct StackNode* next;
}StackNode, * StackList;
//��ջ����Pop
StackList Pop(StackList S, int* e) {
	StackList p;
	p = S;
	//ջ�ձ���
	if (!p)
		return false;
	*e = p->data;//��ջֵ����e
	S = S->next;
	free(p);
	return S;
}
//��ջ����Push
StackList Push(StackList S, int e) {
	StackList p;
	p = (StackNode*)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S;
	S = p;
	return S;
}

//�ڽӱ� ����ͼ
//�߱�ṹ
typedef struct EdgeNode {
	int adjvex;
	struct EdgeNode* next;
}EdgeNode;
//������Ϣ
typedef struct VertexNode {
	char data;
	struct EdgeNode* first;
}VertexNode;
//�ڽӱ�ṹ��ͼ
typedef struct GraphadjList {
	VertexNode adjList[100];
	int numV, numE;
}GraphadjList;
//�����ڽ�������
void CreatALGraph(GraphadjList* G) {
	G->numV = 6;
	G->numE = 8;
	char datas[] = { 'A','B','C','D','E','F' };
	int edge[][2] = { {0,1},{0,2},{0,3},{2,1},{2,4},{3,4},{5,3} ,{5,4} };
	EdgeNode* e;
	int vi, vj;
	//�����߱�
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
//������������ TopoSort
//topoָ�봫��������洢���������������
int TopoSort(GraphadjList G, int* topo) {
	StackList S;//����ջָ��
	EdgeNode* p;//��ʱָ�룬�洢���ָ��Ľ��
	int index;//�洢ɾ�������Ϣ
	int m = 0;//�±� ���ڴ洢�������У�
	S = NULL;
	for (int i = 0; i < G.numV; i++) {
		if (indegree[i] == 0) {
			S = Push(S, i);
		}
	}
	while (S) {//ջ��Ϊ�վͼ�����
		S = Pop(S, &index);
		topo[m] = index;
		m++;
		//ɾ�� index���ڵĵ�����-1
		p = G.adjList[index].first;
		while (p != NULL) {
			--indegree[p->adjvex];//�ٽ�����ȼ�һ
			if (indegree[p->adjvex] == 0)
				S = Push(S, p->adjvex);
			p = p->next;
		}
	}
	topo[m] = -1;//-1�����β
	//�ж�һ���Ƿ�ɻ�
	if (m < G.numV)
		return 0;
	else
		return 1;
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