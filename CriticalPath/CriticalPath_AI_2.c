#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ���ã����Ǳ�Ӧ���ҿ��԰����������Ϊ�����������ݣ�ֱ�ӽ�����д�ڴ������档���������������ݣ������������´��룺

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
    // ֱ�ӽ�����д�ڴ�������
    G->vexnum = 9;                                                                                                                                                                                                  // ������
    G->arcnum = 11;                                                                                                                                                                                                 // ����
    char vexs[9] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };                                                                                                                                                   // ������Ϣ
    char arcs[11][3] = { {'A', 'B', '6'}, {'A', 'C', '4'}, {'A', 'D', '5'}, {'B', 'E', '1'}, {'C', 'E', '1'}, {'D', 'F', '2'}, {'E', 'G', '9'}, {'E', 'H', '7'}, {'F', 'H', '4'}, {'G', 'I', '2'}, {'H', 'I', '4'} }; // ����Ϣ
    for (int i = 0; i < G->vexnum; i++)                                                                                                                                                                             // ��ʼ����������
    {
        G->vertices[i].data = vexs[i];
        G->vertices[i].firstarc = NULL;
    }
    for (int i = 0; i < G->arcnum; i++) // ��ʼ��������
    {
        char v1 = arcs[i][0];
        char v2 = arcs[i][1];
        int w = arcs[i][2] - '0'; // ���ַ�ת��Ϊ����
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
// (1) github.com. https://github.com/ourzizz/learnc/tree/98fa94b9e4cdcdc97c3e1098b1caced867948e97/datastruct%2Fgraph%2FAOE.cpp.