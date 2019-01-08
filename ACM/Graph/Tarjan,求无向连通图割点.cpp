#define MAX 5000+5
//include...

vector<int>G[MAX];
int cnt;//访问次序
int dfn[MAX];//i点的访问次序
int low[MAX];//i点能到达的最小访问次序
int ans[MAX];//ans[i]保存的是在这个图中删除i点所增加的连通分量数,若ans[i]>0,则点i为割点
int pre[MAX];
bool vis[MAX];

void init()
{
	cnt = 0;
	memset(ans, 0, sizeof(ans));
	memset(vis, 1, sizeof(vis));
}

void Tarjan(int at)
{
	vis[at] = 0;
	int child = 0;
	dfn[at] = low[at] = cnt++;

	for (int i = 0; i < G[at].size(); i++)//对新加入树的点at,遍历其所有的邻接点
	{
		if (vis[G[at][i]])//如果邻接点未被访问,访问它
		{
			child++;
			pre[G[at][i]] = at;

			Tarjan(G[at][i]);
			low[at] = min(low[at], low[G[at][i]]);//因为该点可能通过其他路径访问到序号更小的点,所以更新一下low值

			if (pre[at] == at)//如果at点是起始点,如果有超过1个的邻接点未被访问,则该点为割点,如果选择的是非割点,那么其邻接点都会在DFS中从其他路径访问到
			{
				if (child > 1)
					ans[at]++;
			}
			else if (low[G[at][i]] >= dfn[at])//如果该点的能访问的最小序号大于等于at点的序号,则说明删除at点该点脱离at点所在的连通分量
					ans[at]++;
		}//已经访问过了,那么at点就能访问到它
		else if (G[at][i] != pre[at])
			low[at] = min(low[at], dfn[G[at][i]]);
	}
}

int mian()
{
	//建图
	/*sample:
	int N, M;
	scanf("%d%d", &N, &M);

	int u, v;
	for (int i = 0; i < M; i++)
	{
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}*/

	init();
	pre[0]=0;
	DFS(0);//任意点开始

	return 0;
}