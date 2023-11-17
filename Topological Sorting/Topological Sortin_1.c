#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define MVNum 100
typedef int Status;
typedef char VerTexType;
typedef char OtherInfo;
int indegree[MVNum] = {0}; // ������ȸ���

// ����ջ
typedef struct StackNode
{
	int data;
	struct StackNode *next;
} StackNode, *StackList;
// ��ջ����
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
// ��ջ������
StackList Push(StackList S, int e)
{
	StackList p;
	p = (StackNode *)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S;
	S = p;
	return S;
}

// �ڽӱ�������ͼ��ʵ��
// �߽��
typedef struct ArcNode
{							 // ������
	int adjvex;				 // �ڽӱ�����������ʵ��
	struct ArcNode *nextarc; // ָ����һ���ߵ�ָ��
							 // OtherInfo info;       //�ͱ���ص���Ϣ
} ArcNode;

// ������Ϣ
typedef struct VNode
{						 // ͷ���
	VerTexType data;	 // ������Ϣ
	ArcNode *firstarc;	 // ָ���һ�������ö���ıߵ�ָ��
} VNode, AdjList[MVNum]; // AdjList ��ʾ�ڽӱ�����

typedef struct
{
	AdjList vertices;	// �ڽӱ�ͷ�������
	int vexnum, arcnum; // ͼ�Ķ������ͻ���
} ALGraph;

// ��������ͼ��
int LocateVex(ALGraph *G, VerTexType v) // G��������ͼ��vҪ��ͼ�ж�λ�Ķ���
{
	int i;
	for (i = 0; i < (G->vexnum); i++)
	{
		if (v == G->vertices[i].data)
			return i; // ��������򷵻���ͷ��������е��±ꣻ���򷵻�
	}
}

void CreateUDG(ALGraph *G)
{
	int i, j, k;
	VerTexType v1, v2;
	ArcNode *p1;
	printf("�����ܽڵ����ͻ�����\n"); // G��������ͼ��vҪ��ͼ�ж�λ�Ķ���
	scanf_s("%d %d", &G->vexnum, &G->arcnum);
	fflush(stdin); // ��������뻺������
	printf("��������ڵ��ֵ��\n");
	for (i = 0; i < G->vexnum; i++) // �ڽӱ��ʼ��

	{
		scanf_s("%c", &G->vertices[i].data);
		getchar();
		G->vertices[i].firstarc = NULL;
	}

	for (k = 0; k < G->arcnum; k++)
	{
		// fflush(stdin);   //��������뻺������
		scanf_s("%c", &v1);
		getchar();
		scanf_s("%c", &v2);
		getchar();
		i = LocateVex(G, v1); // ���������������ڶ��������е�λ��
		j = LocateVex(G, v2);
		p1 = (ArcNode *)malloc(sizeof(ArcNode)); // ���ڽӱ�ָ�����ռ�
		p1->adjvex = j;							 // ��ֵ��p->adjvexָ��Ķ�����
		p1->nextarc = G->vertices[i].firstarc;	 // nextarcָ����ָ��i����firstarcָ����
		G->vertices[i].firstarc = p1;			 // ����i�ĵ�һ��ָ��ָ��
		indegree[j]++;
	}
}

int TopoSort(ALGraph G, int *topo)
{
	StackList S; // ����һ��ջָ��
	ArcNode *p;
	int index;
	int m = 0; // �±� ���ڴ洢��������
	S = NULL;
	for (int i = 0; i < G.vexnum; i++)
	{
		if (indegree[i] == 0)
		{
			S = Push(S, i);
		}
	}

	while (S) // ջ��Ϊ�� �ͼ�����
	{
		S = Pop(S, &index);
		topo[m] = index;
		m++;
		// ɾ�� index���ڵĵ�����-1
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
	topo[m] = -1; //-1�����β
	// �ж�һ���Ƿ�ɻ�
	if (m < G.vexnum)
	{
		// �ɻ�
		return 0;
	}
	else
	{
		// ���ɻ�
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
