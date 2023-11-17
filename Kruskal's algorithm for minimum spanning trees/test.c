#include <stdio.h>
#include <stdlib.h>
#define INF 65535
/*����С������---->ѡ��n-1���ߣ�

1.ѡ��n-1��Ȩֵ����С�ıߣ� ÿ�ζ�ѡ�µ���С�ı�E---����̰��
2. ���в��ܳ��ֻ� �����ò��鼯���ж�һ�� E�������˵��ǲ�������ͬһ����ͨ���ϣ�
(1)yes,˵��E����ѡ  (2)no, ˵��ҪѡE

Kruskal��˼· ---̰�ģ�̰����˼�� �������ܺ�   Ŀ���ǳ

ʱ�临�Ӷȣ��ڲ��鼯����·��ѹ���Ļ����� O(eloge) ----�ʺ� ϡ��ͼ
*/

//�ڽӾ����ͼ������Ȩ����ͼ
int g[105][105];//�������100����
int nv, ne;

//�߼��������洢�������еı߱�ṹ��
typedef struct {
	int u, v;//�˵�
	int w;//Ȩֵ
}Edge;

Edge e[5005];

void sorte(int l, int r) {
	//ѡ��
	int minn;
	Edge tmp;
	for (int i = l; i < r; i++) {
		minn = i;
		for (int j = i + 1; j < r; j++) {
			if (e[minn].w > e[j].w)
				minn = j;
		}
		tmp = e[i];
		e[i] = e[minn];
		e[minn] = tmp;
	}
	//�������֮��Ľ��
	printf("��Ȩֵ�������У�\n");
	for (int i = 0; i < r; i++)
		printf("(%d %d) %d\n", e[i].v, e[i].u, e[i].w);
}
//���鼯��
int find(int* f, int z) {
	while (z != f[z])
		z = f[z];
	return z;
}

void Kruskal() {
	int f[105];
	for (int i = 0; i < nv; i++) {
		f[i] = i;
	}
	printf("��������С�������ıߣ�\n");
	//���ݲ��鼯�ж��Ƿ��γɻ�
	for (int i = 0; i < ne; i++) {
		int fu = find(f, e[i].u);
		int fv = find(f, e[i].v);
		//������������Ƿ���ͬһ��������
		if (fu != fv) {
			f[fv] = fu;
			printf("(%d %d) %d\n", e[i].v, e[i].u, e[i].w);
		}
	}
}

int main() {
	//���ڽӾ��󴴽�ͼ
	scanf_s("%d%d", &nv, &ne);
	//�Զ�ά�߱�������г�ʼ��
	for (int i = 0; i < nv; i++) {
		for (int j = 0; j < nv; j++) {
			if (i == j) {
				g[i][j] = g[j][i] = 0;
			}
			else {
				g[i][j] = g[j][i] = INF;
			}
		}
	}
	//��ͷ����β��Ȩֵ
	int x, y, wi;
	int k = 0;//��������±�
	//���д���
	for (int i = 0; i < ne; i++) {
		scanf_s("%d%d%d", &x, &y, &wi);
		g[x][y] = g[y][x] = wi;
		//�Ȱ�������������߼�������
		e[k].v = x;
		e[k].u = y;
		e[k].w = wi;
		k++;
	}
	sorte(0, k);
	Kruskal();

	return 0;
}