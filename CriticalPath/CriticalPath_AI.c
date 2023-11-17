#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 您好，这是必应。我可以帮您补全求关键路径的函数。根据您给出的函数，我生成了以下代码：

// 定义栈结构
typedef struct Stack
{
    int data[99];
    int top;
} Stack;

// 初始化栈
void InitStack(Stack* S)
{
    S->top = -1;
}

// 判断栈是否为空
bool IsEmpty(Stack* S)
{
    return S->top == -1;
}

// 入栈
void Push(Stack* S, int x)
{
    S->top++;
    S->data[S->top] = x;
}

// 出栈
int Pop(Stack* S)
{
    int x = S->data[S->top];
    S->top--;
    return x;
}

// 定义邻接表结点
typedef struct ArcNode
{
    int adjvex;              // 邻接点域
    int info;                // 权值
    struct ArcNode* nextarc; // 指向下一个邻接点的指针
} ArcNode;

// 定义邻接表头结点
typedef struct VNode
{
    char data;         // 顶点信息
    ArcNode* firstarc; // 指向第一个邻接点的指针
} VNode;

// 定义邻接表图
typedef struct ALGraph
{
    VNode vertices[99]; // 顶点数组
    int vexnum;         // 顶点数
    int arcnum;         // 边数
} ALGraph;

// 根据顶点信息查找顶点下标
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

// 创建邻接表图
void CreateGraph(ALGraph* G)
{
    printf("请输入顶点数和边数：\n");
    scanf_s("%d%d", &G->vexnum, &G->arcnum);

    printf("请输入顶点信息：\n");
    for (int i = 0; i < G->vexnum; i++)
    {
        scanf_s(" %c", &G->vertices[i].data); // 注意空格
        G->vertices[i].firstarc = NULL;
    }
    printf("请输入边信息：\n");
    for (int i = 0; i < G->arcnum; i++)
    {
        char v1, v2;
        int w;
        scanf_s(" %c %c %d", &v1, &v2, &w); // 注意空格
        int m = LocateVex(*G, v1);
        int n = LocateVex(*G, v2);
        ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = n;
        p->info = w;
        p->nextarc = G->vertices[m].firstarc;
        G->vertices[m].firstarc = p;
    }
}

// 拓扑排序
bool TopoSort(ALGraph G, int* etv, int* topo)
{
    Stack S;
    InitStack(&S);
    int indegree[99] = { 0 };            // 入度数组
    for (int i = 0; i < G.vexnum; i++) // 初始化入度数组
    {
        ArcNode* p = G.vertices[i].firstarc;
        while (p)
        {
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
    for (int i = 0; i < G.vexnum; i++) // 将入度为0的顶点入栈
    {
        if (indegree[i] == 0)
        {
            Push(&S, i);
        }
    }
    int count = 0;       // 记录拓扑序列的长度
    while (!IsEmpty(&S)) // 栈不为空时循环
    {
        int j = Pop(&S); // 出栈
        topo[count] = j; // 将出栈的顶点放入拓扑序列
        count++;
        ArcNode* p = G.vertices[j].firstarc; // 遍历出栈顶点的邻接点
        while (p)
        {
            int k = p->adjvex;
            indegree[k]--;        // 将邻接点的入度减一
            if (indegree[k] == 0) // 如果入度为0，则入栈
            {
                Push(&S, k);
            }
            if (etv[j] + p->info > etv[k]) // 更新事件最早发生时间
            {
                etv[k] = etv[j] + p->info;
            }
            p = p->nextarc;
        }
    }
    if (count < G.vexnum) // 如果拓扑序列的长度小于顶点数，说明有环
    {
        return false;
    }
    else
    {
        return true;
    }
}

// 求关键路径的函数
void CriticalPath(ALGraph G, int* etv, int* ltv)
{
    int topo[99] = { 0 };
    ArcNode* p;
    int ete, lte; // 此处其实没必要用数组
    if (TopoSort(G, etv, topo))
    {
        // 初始化事件最晚发生时间
        int x = topo[G.vexnum - 1]; // x是拓扑序列的终点，也是图汇点
        for (int i = 0; i < G.vexnum; i++)
        {
            ltv[i] = etv[x];
        }
        // 逆拓扑 求事件最晚发生时间
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
        // 求活动的最早和最晚,顺便输出关键路径，通过点遍历所有的边，时间复杂度O（E）
        printf("以下是关键路径：\n");
        for (int i = 0; i < G.vexnum; i++)
        {
            for (p = G.vertices[i].firstarc; p; p = p->nextarc)
            {
                int k = p->adjvex;
                ete = etv[i];
                lte = ltv[k] - p->info;
                if (ete == lte) // 输出关键路径的边
                {
                    printf("%c %c : %d\n", G.vertices[i].data, G.vertices[k].data, p->info);
                }
            }
        }
    }
}

// 主函数
int main()
{
    ALGraph G;
    CreateGraph(&G);           // 创建邻接表图
    int etv[99] = { 0 };         // 事件最早发生时间
    int ltv[99] = { 0 };         // 事件最晚发生时间
    CriticalPath(G, etv, ltv); // 求关键路径
    return 0;
}

// 源: 与必应的对话， 2023/11/6
// (1) Software Engineering | Critical Path Method - GeeksforGeeks. https://www.geeksforgeeks.org/software-engineering-critical-path-method/.
// (2) Calculating critical path of a DAG in C++ - Stack Overflow. https://stackoverflow.com/questions/6080542/calculating-critical-path-of-a-dag-in-c.
// (3) Critical Path Method Implementation in C# - CodeProject. https://www.codeproject.com/articles/25312/critical-path-method-implementation-in-c.
// (4) algorithm - How to compute the critical path of a directional acyclic .... https://stackoverflow.com/questions/107660/how-to-compute-the-critical-path-of-a-directional-acyclic-graph.
// (5) GitHub - suman95/Critical-path-management: A complete C++ code for .... https://github.com/suman95/Critical-path-management.