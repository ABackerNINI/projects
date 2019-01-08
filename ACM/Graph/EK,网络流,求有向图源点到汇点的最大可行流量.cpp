//include...

#define MAX 100

vector<int>G[MAX];
int C[MAX][MAX];//最大容量
bool vis[MAX];
int pre[MAX];


bool BFS(int s, int t)
{
	memset(vis, 1, sizeof(vis));
	memset(pre, 0, sizeof(pre));

	queue<int>open;
	open.push(s);
	vis[s] = 0;
	pre[s] = s;

	int tmp;
	while (!open.empty())
	{
		tmp = open.front();
		open.pop();
		for (int i = 0; i < G[tmp].size(); i++)
		{
			if (vis[G[tmp][i]] && C[tmp][G[tmp][i]]>0)
			{
				pre[G[tmp][i]] = tmp;
				if (G[tmp][i] == t)
					return true;

				open.push(G[tmp][i]);
				vis[G[tmp][i]] = 0;
			}
		}
	}

	return false;
}

ll EK(int s,int t)//返回最大流量
{
	ll maxFlow = 0;
	while (BFS(s, t))
	{
		int delta = 100000000;
		for (int v = t; v != s; v = pre[v])
		{
			if (delta > C[pre[v]][v])
				delta = C[pre[v]][v];
		}

		for (int v = t; v != s; v = pre[v])
		{
			C[pre[v]][v] -= delta;
			C[v][pre[v]] += delta;
		}

		maxFlow += delta;
	}

	return maxFlow;
}

int main()
{
	memset(C,0,sizeof(C));

	int s,t;//源点,汇点
	//建图,需要建立无向图!
	/*sample:
	int N,M;
	scanf("%d%d", &N, &M);

	int u, v, c;
	for (int i = 0; i < N; i++)
	{
		scanf("%d%d%d", &u, &v, &c);
		G[u].push_back(v);
		G[v].push_back(u);
		C[u][v] += c;
	}*/
	//C[i][j] += c;

	printf("%lld\n",EK(s,t));
	return 0;
}