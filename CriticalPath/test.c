#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    // 直接将数据写在代码里面
    G->vexnum = 9;                                                                                                                                                                                                  // 顶点数
    G->arcnum = 11;                                                                                                                                                                                                 // 边数
    char vexs[9] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I' };                                                                                                                                                   // 顶点信息
    char arcs[11][3] = { {'A', 'B', '6'}, {'A', 'C', '4'}, {'A', 'D', '5'}, {'B', 'E', '1'}, {'C', 'E', '1'}, {'D', 'F', '2'}, {'E', 'G', '9'}, {'E', 'H', '7'}, {'F', 'H', '4'}, {'G', 'I', '2'}, {'H', 'I', '4'} }; // 边信息
    for (int i = 0; i < G->vexnum; i++)                                                                                                                                                                             // 初始化顶点数组
    {
        G->vertices[i].data = vexs[i];
        G->vertices[i].firstarc = NULL;
    }
    for (int i = 0; i < G->arcnum; i++) // 初始化边链表
    {
        char v1 = arcs[i][0];
        char v2 = arcs[i][1];
        int w = arcs[i][2] - '0'; // 将字符转换为数字
        int m = LocateVex(*G, v1);
        int n = LocateVex(*G, v2);
        ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = n;
        p->info = w;
        p->nextarc = G->vertices[m].firstarc;
        G->vertices[m].firstarc = p;
    }
}

//拓扑排序
bool TopoSort(ALGraph G, int* etv, int* topo) {
    Stack S;
    InitStack(&S);
    //统计各个结点的入度
    int indegree[99] = { 0 };
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode* p = G.vertices[i].firstarc;
        while(p){
            indegree[p->adjvex]++;
            p = p->nextarc;
        }
    }
    //将入度为0的结点入栈
    for (int i = 0; i < G.vexnum; i++) {
        if (indegree[i] == 0)
            Push(&S, i);
    }
    //记录拓扑序列长度
    int count = 0;
    //栈不为空循环不结束
    while (!IsEmpty(&S)) {
        //j来存放出栈顶点的值
        int j = Pop(&S);
        //出栈的顶点放入拓扑序列
        topo[count] = j;
        count++;
        //遍历出栈结点邻接点，让它们入度--
        ArcNode* p = G.vertices[j].firstarc;
        while(p){
            //k来存放邻接点的值
            int k = p->adjvex;
            indegree[k]--;
            if (indegree[k] == 0)
                Push(&S, k);
            //更新事件最早发生时间
            if (etv[j] + p->info > etv[k])
                etv[k] = etv[j] + p->info;
            p = p->nextarc;
        }
    }
    if (count < G.vexnum)
        return false;
    else
        return true;
}

//求关键路径的函数
void CriticalPath(ALGraph G, int* etv, int* ltv) {
    int topo[99] = { 0 };
    ArcNode* p;
    int ete, lte;
    if (TopoSort(G, etv, topo)) {
        //初始时间最晚发生时间
        int x = topo[G.vexnum - 1];//x结点的最晚发生时间
        //x为拓扑序列的终点，图的汇点
        for (int i = 0; i < G.vexnum; i++)
            ltv[i] = etv[x];
        //进行逆拓扑序列推ltv，事件的最晚发生时间
        for (int i = G.vexnum - 2; i; i--) {
            int gettop = topo[i];
            for (p = G.vertices[gettop].firstarc; p; p = p->nextarc) {
                int k = p->adjvex;
                if (ltv[k] - p->info < ltv[gettop])
                    ltv[gettop] = ltv[k] - p->info;
            }
        }
        printf("以下时关键路径:\n");
        for (int i = 0; i < G.vexnum; i++) {
            for (p = G.vertices[i].firstarc; p; p = p->nextarc) {
                //k为该节点的邻接点
                int k = p->adjvex;
                ete = etv[i];
                //活动的最晚发生时间等于邻接点最晚发生时间减去边权值
                lte = ltv[k] - p->info;
                if (ete == lte)
                    printf("%c %c :%d\n", G.vertices[i].data, G.vertices[k].data, p->info);
            }
        }
    }
}

int main() {
    ALGraph G;
    CreateGraph(&G);
    int etv[99] = { 0 };         // 事件最早发生时间
    int ltv[99] = { 0 };         // 事件最晚发生时间
    CriticalPath(G, etv, ltv);

}