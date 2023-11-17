#include <stdio.h>
#include <stdbool.h>
#define INF 65535

int g[105][105];//g��ά�������ڽӾ������洢ͼ
int nv, ne;
int dist[105];//dist��������δ��ӵ���С�������е���B�����е� A���ϵľ���
bool vi[105];//0����û����ӵ���������

void prim() {
	//�õ�һ����㵽A���ϣ���Ϊ��С�������ĸ��ڵ�
	dist[0] = 0;
	vi[0] = 1;
	for (int i = 1; i < nv; i++)
		dist[i] = g[0][i];
	//��ʼ˳����ʼ��Ѱ��Ȩֵ��С�ĵ�
	int minn;//�����ҵ���p�ı�ţ��ڽӵ�
	int tmpd;//����dist��ֵ,��СȨֵ
	for (int i = 1; i < nv; i++) {
		minn = -1;
		tmpd = INF;
		for (int j = 0; j < nv; j++) {
			//ȷ������B�����У�����ȨֵҪ��С
			if (vi[j] == 0 && dist[j] < tmpd) {
				minn = j;
				tmpd = dist[j];
			}
		}
		if (minn == -1)
			return;
		printf("�ѵ�%d�ģ�ͨ��ȨΪ%d�ı߼��뵽��������\n", minn, tmpd);
		//��B���Ͻ��и��£������ٽ����Ȩֵ
		vi[minn] = true;
		for (int j = 1; j < nv; j++)
			dist[j] = (dist[j] < g[minn][j]) ? dist[j] : g[minn][j];
	}
}

int main() {
	//�����ڽӾ���
	scanf_s("%d%d", &nv, &ne);
	for (int i = 0; i < nv; i++) {
		for (int j = 0; j < nv; j++) {
			if (i == j)
				g[i][j] = 0;
			else
				g[i][j] = g[j][i] = INF;
		}
	}
	int x, y, wi;
	for (int i = 0; i < ne; i++) {
		scanf_s("%d%d%d", &x, &y, &wi);
		g[x][y] = g[y][x] = wi;
	}
	//B�м��ϵ�A�ľ���ȫ����ʼ��Ϊ�����
	for (int i = 0; i < nv; i++) 
		dist[i] = INF;
	prim();
	return 0;
}