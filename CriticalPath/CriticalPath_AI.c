#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ���ã����Ǳ�Ӧ���ҿ��԰�����ȫ��ؼ�·���ĺ����������������ĺ����������������´��룺

// ����ջ�ṹ
typedef struct Stack
{
    int data[99];
    int top;
} Stack;

// ��ʼ��ջ
void InitStack(Stack* S)
{
    S->top = -1;
}

// �ж�ջ�Ƿ�Ϊ��
bool IsEmpty(Stack* S)
{
    return S->top == -1;
}

// ��ջ
void Push(Stack* S, int x)
{
    S->top++;
    S->data[S->top] = x;
}

// ��ջ
int Pop(Stack* S)
{
    int x = S->data[S->top];
    S->top--;
    return x;
}

// �����ڽӱ���
typedef struct ArcNode
{
    int adjvex;              // �ڽӵ���
    int info;                // Ȩֵ
    struct ArcNode* nextarc; // ָ����һ���ڽӵ��ָ��
} ArcNode;

// �����ڽӱ�ͷ���
typedef struct VNode
{
    char data;         // ������Ϣ
    ArcNode* firstarc; // ָ���һ���ڽӵ��ָ��
} VNode;

// �����ڽӱ�ͼ
typedef struct ALGraph
{
    VNode vertices[99]; // ��������
    int vexnum;         // ������
    int arcnum;         // ����
} ALGraph;

// ���ݶ�����Ϣ���Ҷ����±�
int LocateVex(ALGraph G, char v)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data == v)
        {
            return i;
        }
    }
    return -1;
}

// �����ڽӱ�ͼ
void CreateGraph(ALGraph* G)
{
    printf("�����붥�����ͱ�����\n");
    scanf_s("%d%d", &G->vexnum, &G->arcnum);

    printf("�����붥����Ϣ��\n");
    for (int i = 0; i < G->vexnum; i++)
    {
        scanf_s(" %c", &G->vertices[i].data); // ע��ո�
        G->vertices[i].firstarc = NULL;
    }
    printf("���������Ϣ��\n");
    for (int i = 0; i < G->arcnum; i++)
    {
        char v1, v2;
        int w;
        scanf_s(" %c %c %d", &v1, &v2, &w); // ע��ո�
        int m = LocateVex(*G, v1);
        int n = LocateVex(*G, v2);
        ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = n;
        p->info = w;
        p->nextarc = G->vertices[m].firstarc;
        G->vertices[m].firstarc = p;
    }
}

// ��������
bool TopoSort(ALGraph G, int* etv, int* topo)
{
    Stack S;
    InitStack(&S);
    int indegree[99] = { 0 };            // �������
    for (int i = 0; i < G.vexnum; i++) // ��ʼ���������
    {
        ArcNode* p = G.vertices[i].firstarc;
        while (p)
        {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
    for (int i = 0; i < G.vexnum; i++) // �����Ϊ0�Ķ�����ջ
    {
        if (indegree[i] == 0)
        {
            Push(&S, i);
        }
    }
    int count = 0;       // ��¼�������еĳ���
    while (!IsEmpty(&S)) // ջ��Ϊ��ʱѭ��
    {
        int j = Pop(&S); // ��ջ
        topo[count] = j; // ����ջ�Ķ��������������
        count++;
        ArcNode* p = G.vertices[j].firstarc; // ������ջ������ڽӵ�
        while (p)
        {
            int k = p->adjvex;
            indegree[k]--;        // ���ڽӵ����ȼ�һ
            if (indegree[k] == 0) // ������Ϊ0������ջ
            {
                Push(&S, k);
            }
            if (etv[j] + p->info > etv[k]) // �����¼����緢��ʱ��
            {
                etv[k] = etv[j] + p->info;
            }
            p = p->nextarc;
        }
    }
    if (count < G.vexnum) // ����������еĳ���С�ڶ�������˵���л�
    {
        return false;
    }
    else
    {
        return true;
    }
}

// ��ؼ�·���ĺ���
void CriticalPath(ALGraph G, int* etv, int* ltv)
{
    int topo[99] = { 0 };
    ArcNode* p;
    int ete, lte; // �˴���ʵû��Ҫ������
    if (TopoSort(G, etv, topo))
    {
        // ��ʼ���¼�������ʱ��
        int x = topo[G.vexnum - 1]; // x���������е��յ㣬Ҳ��ͼ���
        for (int i = 0; i < G.vexnum; i++)
        {
            ltv[i] = etv[x];
        }
        // ������ ���¼�������ʱ��
        for (int i = G.vexnum - 2; i >= 0; i--)
        {
            int gettop = topo[i];
            for (p = G.vertices[gettop].firstarc; p; p = p->nextarc)
            {
                int k = p->adjvex;
                if (ltv[k] - p->info < ltv[gettop])
                {
                    ltv[gettop] = ltv[k] - p->info;
                }
            }
        }
        // �������������,˳������ؼ�·����ͨ����������еıߣ�ʱ�临�Ӷ�O��E��
        printf("�����ǹؼ�·����\n");
        for (int i = 0; i < G.vexnum; i++)
        {
            for (p = G.vertices[i].firstarc; p; p = p->nextarc)
            {
                int k = p->adjvex;
                ete = etv[i];
                lte = ltv[k] - p->info;
                if (ete == lte) // ����ؼ�·���ı�
                {
                    printf("%c %c : %d\n", G.vertices[i].data, G.vertices[k].data, p->info);
                }
            }
        }
    }
}

// ������
int main()
{
    ALGraph G;
    CreateGraph(&G);           // �����ڽӱ�ͼ
    int etv[99] = { 0 };         // �¼����緢��ʱ��
    int ltv[99] = { 0 };         // �¼�������ʱ��
    CriticalPath(G, etv, ltv); // ��ؼ�·��
    return 0;
}

// Դ: ���Ӧ�ĶԻ��� 2023/11/6
// (1) Software Engineering | Critical Path Method - GeeksforGeeks. https://www.geeksforgeeks.org/software-engineering-critical-path-method/.
// (2) Calculating critical path of a DAG in C++ - Stack Overflow. https://stackoverflow.com/questions/6080542/calculating-critical-path-of-a-dag-in-c.
// (3) Critical Path Method Implementation in C# - CodeProject. https://www.codeproject.com/articles/25312/critical-path-method-implementation-in-c.
// (4) algorithm - How to compute the critical path of a directional acyclic .... https://stackoverflow.com/questions/107660/how-to-compute-the-critical-path-of-a-directional-acyclic-graph.
// (5) GitHub - suman95/Critical-path-management: A complete C++ code for .... https://github.com/suman95/Critical-path-management.