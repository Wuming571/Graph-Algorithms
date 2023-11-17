#include <stdio.h>
#include <stdbool.h>
#define INF 65535

//g��ά�������ڽӾ������洢ͼ
int g[105][105];
int nv, ne;
//dist��������δ��ӵ���С�������е���B�����е� A���ϵľ���
int dist[105];
//0����û����ӵ���������
bool vi[105];

void prim() {
	//�õ�һ����㵽A���ϣ���Ϊ��С�������ĸ��ڵ�
	dist[0] = 0;
	vi[0] = 1;
	for (int i = 1; i < nv; i++)
		dist[i] = g[0][i];
	//��ʼ˳����ʼ��Ѱ��Ȩֵ��С�ĵ�
	int minn;
	int tmpd;

	for (int i = 1; i < nv; i++) {
		//�����д����Ǳ����еģ���ÿ�ҵ�һ������ʱ����Ҫ���£�
		// ���ݴ�ı�ź�Ȩֵ���г�ʼ��
		minn = -1;//�����ҵ���p�ı�ţ��ڽӵ�int minn;	
		tmpd = INF;//����dist��ֵ,��СȨֵ
		for (int j=0; j < nv; j++) {
			//ȷ������B�����У�����ȨֵҪ��С
			if (vi[j] == false && dist[j] < tmpd) {
				minn = j;
				tmpd = dist[j];	
			}

		}
		//���δ�ҵ�˵������ͨͼ������
	if (minn == -1)
		return;
	printf("%d %d\n", minn, tmpd);
	vi[minn] = true;
	for (int j = 1; j < nv; j++) {
		if (dist[j] > g[minn][j])
			dist[j] = g[minn][j];
	}
		//��B���Ͻ��и��£������ٽ����Ȩֵ
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
	for (int i = 0; i < nv; i++) {
		dist[i] = INF;
	}
	prim();

	return 0;
}