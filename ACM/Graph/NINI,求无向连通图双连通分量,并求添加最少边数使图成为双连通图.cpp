//#include...

#define MAX 100000+5

vector<int>G[MAX];
int cnt;
int pre[MAX];
int cmt[MAX];//保存点的集合,如果cmt[i]==cmt[j],那么点i和点j处于同一双连通分量
int in[MAX + 3000],out[MAX + 3000];//点的出入度
bool change[MAX];

void init(int n)
{
	memset(cmt, -1, sizeof(int)*(n + 2));
	cnt = 1;
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	memset(change, 1, sizeof(change));
}

void DFS(int at)
{
	cmt[at] = cnt++;//属于自己的集合
	int v;
	for (int i = 0; i < G[at].size(); i++)//枚举邻接点
	{
		v = G[at][i];
		if (v == pre[at])//跳过父亲节点
			continue;
		if (cmt[v] == -1)//如果该点还未分配集合,DFS该点
		{
			pre[v] = at;
			DFS(v);
		}
		else if (cmt[v] != cmt[at])//如果该点已经分配了集合,说明at点与该点形成了环,即pre[v->at]上所有点属于同一个双连通分量,沿pre数组修改为相同的集合
		{
			for (int j = at; j != v; j = pre[j])
			{
				if (change[j])//如果该点已经处于一个双连通分量,那么将pre路径上的其余点添加入该双连通分量
				{
					cmt[j] = cmt[v];
					change[j] = 0;
				}
				else
					break;
			}
		}
	}
}

int getMinEages()
{
	//缩点:理清各个双连通分量的连接关系
	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j < G[i].size(); j++)
		{
			if (cmt[i] != cmt[G[i][j]])
			{
				out[cmt[i]]++;
				in[cmt[G[i][j]]]++;
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= N; i++)
	{
		if (in[cmt[i]] == 1 && out[cmt[i]] == 1)//如果该点的出入度都为1,那么就是缩点后的叶节点
		{
			ans++;
			in[cmt[i]] = 0;
		}
	}
	return (ans + 1) / 2;//将所有叶节点的出入度补齐至少为2,所需的添加的边数
}

int main()
{
	//建图
	/*sample:
	int N, M;
	scanf("%d%d", &N, &M)

		init(N);

	int u, v;
	for (int i = 0; i < M; i++)
	{
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}*/

	DFS(1);//从任意点开始DFS求双连通分量

	printf("%d\n", getMinEages());
	return 0;
}

