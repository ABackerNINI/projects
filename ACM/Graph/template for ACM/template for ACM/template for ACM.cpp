#include <stdio.h>
#include <string.h>

#define INF (1<<30)
#define MAXN 1000

int map[MAXN][MAXN], dis[MAXN];
bool vis[MAXN];

void dijkstra(int n){
	memset(vis, false, sizeof(vis));

	for (int i = 1; i <= n; ++i)dis[i] = INF;
	dis[0] = 0;

	int k;
	for (int i = 1; i <= n; ++i){
		k = -1;
		for (int j = 1; j <= n; ++j){
			if (!vis[j] && (k == -1 || dis[k] > dis[j]))
				k = j;
		}

		vis[k] = true;
		for (int j = 1; j <= n; ++j){
			if (!vis[j] && map[k][j] && (dis[k] + map[k][j] < dis[j]))
				dis[j] = dis[k] + map[k][j];
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d ",dis[i]);
}
int main() {
	int n, m;//n¸öµã,mÌõ±ß
	scanf("%d%d", &n, &m);

	memset(map, 0, sizeof(map));

	int u, v, w;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		map[u][v] = w;
	}
	dijkstra(n);

	return 0;
}