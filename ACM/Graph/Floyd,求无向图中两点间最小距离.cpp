#include "stdio.h"
#include "string.h"
#include "math.h"

#define INF (1<<30)//Ҫ�㹻��
#define MAX (100)

int dis[MAX][MAX];//dis[i][j]����i,j֮�����̾���

void Floyd(int n){
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j)dis[i][j] = 0;
			else dis[i][j] = INF;
		}
	}
	for (int v = 1; d <= n; v++){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++)
				dis[i][j] = min(dis[i][j], dis[i][v] + dis[v][j]);
		}
	}
}

int main()
{
 	/*//��ͼ,���ڽӾ���
	int n,m;//n:����;m:����
	scanf("%d%d",&n,&m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &u, &v,&d);
        dis[u][v] = d;dis[v][u] = d;
	}
	Floyd(n);*/

	return 0;
}