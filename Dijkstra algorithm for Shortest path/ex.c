#include <stdio.h>
#include <stdbool.h>
#define INF 65535

// �ڽӾ���������ͼ
int g[105][105];
// ���� ���� Դ��
int nv, ne, v;
// dist�㵽Դ�����̾���
int dist[105];
// path�����ת���
int path[105];
// ch�Ƿ������·����
bool ch[105];

void dijkstra()
{
    // ��Դ���ڽӵ���г�ʼ��
    for (int i = 0; i < ne; i++) {
        dist[i] = g[v][i];
        if (g[v][i] != INF) {
            path[i] = v;
        }
    }
    // �洢distֵ��С����Ϣ
    int minn;// minn
    int k;// k
    // ��ʼ���в���
    for (int i = 1; i < nv; i++) {
        minn = INF;
        // �ҵ���С��dist
        for (int j = 0; j < nv; j++) {
            if (ch[j] == false && dist[j] < minn) {
                minn = dist[j];
                k = j;
            }
        }
        ch[k] = true;
        // �µ�k����Ϊ��ת�� k�ٽ�����и���
        for (int j = 0; j < nv; j++) {
            if (ch[j] == false && dist[k] + g[k][j] < dist[j]) {
                dist[j] = dist[k] + g[k][j];
                path[j] = k;

            }
        }
    }
}

int main()
{
    int x, y, w;
    scanf_s("%d%d", &nv, &ne);
    for (int i = 0; i < nv; i++)
    {
        for (int j = 0; j < nv; j++)
        {
            if (i == j)
                g[i][j] = g[j][i] = 0;
            else
                g[i][j] = g[j][i] = INF;
        }
    }
    for (int i = 0; i < ne; i++)
    {
        scanf_s("%d%d%d", &x, &y, &w);
        g[x][y] = g[y][x] = w;
    }
    // ����Դ�㣬����Դ����г�ʼ��
    scanf_s("%d", &v);
    for (int i = 0; i < nv; i++) {
        dist[i] = INF;
    }
    dist[v] = 0;
    ch[v] = true;
    path[v] = v;

    dijkstra();

    // ������������·��
    for (int i = 0; i < nv; i++)
    {
        printf("%d %d %d  ", v, i, dist[i]);
        int j = i;
        printf("%d->", i);
        while (path[j] != j)
        {
            printf("%d->", path[j]);
            j = path[j];
        }
        printf("\n");
    }

    return 0;
}