//include...

#define MAX 100
#define INF 10000000000//足够大

int dis[MAX][MAX];//图中两点间距离(权值)
vector<int>G[MAX];//保存最小生成树
int mindis;//保存最小生成树的总距离

bool vis[MAX];
int low[MAX];

void init(int n)
{
	memset(vis, 1, sizeof(vis));

	for (int i = 0; i < n; i++)
		low[i] = INF;
}

void prim(int s,int n)
{
	vis[s] = 0; 
	int pos = s; 

	int _pos;
	for (int i = 0; i < n - 1; i++)
	{
		low[pos] = INF; _pos = pos;
		for (int j = 0; j < n; j++)
		{
			if (vis[j])
			{
				;
				if (low[j]>dis[_pos, j])
					low[j] = dis[_pos, j];

				if (low[pos]>low[j])
					pos = j;
			}
		}
		vis[pos] = 0;
		mindis += low[pos];
		G[_pos].push_back(pos);
	}
}

int main()
{
	memset(dis,0,sizeof(dis));//初始化为0

	//建图,用邻接矩阵
	/*sample:
	int n,m;//点数,边数
	scanf("%d%d", &n,&m);

	int u,v,d;
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d%d", &u, &v, &d);
		dis[u][v]=d;
		dis[v][u]=d;
	}*/

	init(n);
	prim(0,n);//从0点开始

	return 0;
}