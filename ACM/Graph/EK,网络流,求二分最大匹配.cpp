#define MAX 400+5

vector<int>G[MAX];
int C[MAX][MAX];
bool vis[MAX];
int pre[MAX];

bool BFS(int s, int t)
{
	memset(vis, 1, sizeof(vis));
	memset(pre, -1, sizeof(pre));

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

int EK(int s, int t)
{
	int maxFlow = 0;
	while (BFS(s, t))
	{//不需返回寻找增广路最大可行流量
		for (int v = t; v != s; v = pre[v])
		{
			C[pre[v]][v] -= 1;
			C[v][pre[v]] += 1;
		}

		maxFlow += 1;
	}

	return maxFlow;
}

int main()
{
	//建图,注意建立无向图!选择两个不用的点作为源点和汇点,这里选择0点和MAX-1点
	/*sample:

	int N, M;
	scanf("%d%d", &N, &M);

	for (int i = 1; i <= 200; i++)
	{
		G[0].push_back(i);
		G[i].push_back(0);//连接源点和所有二分匹配的一边
		C[0][i] = 1;
		G[i + 200].push_back(MAX - 1);
		G[MAX - 1].push_back(i + 200);//连接汇点和所有二分匹配的另一边
		C[i + 200][MAX - 1] = 1;
	}

	int S,s;
	for(int i=0;i<N;i++)
	{
		scanf("%d", &S);
		for (int j = 1; j <= S; j++)
		{
			scanf("%d", &s);
			G[i].push_back(s + 200);
			G[s + 200].push_back(i);
			C[i][s + 200] = 1;
		}
	}*/

	printf("%d\n", EK(0, MAX - 1));

	return 0;
}