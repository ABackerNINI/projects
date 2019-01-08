#define MAX 5000+5
//include...

vector<int>G[MAX];
int cnt;//���ʴ���
int dfn[MAX];//i��ķ��ʴ���
int low[MAX];//i���ܵ������С���ʴ���
int ans[MAX];//ans[i]������������ͼ��ɾ��i�������ӵ���ͨ������,��ans[i]>0,���iΪ���
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

	for (int i = 0; i < G[at].size(); i++)//���¼������ĵ�at,���������е��ڽӵ�
	{
		if (vis[G[at][i]])//����ڽӵ�δ������,������
		{
			child++;
			pre[G[at][i]] = at;

			Tarjan(G[at][i]);
			low[at] = min(low[at], low[G[at][i]]);//��Ϊ�õ����ͨ������·�����ʵ���Ÿ�С�ĵ�,���Ը���һ��lowֵ

			if (pre[at] == at)//���at������ʼ��,����г���1�����ڽӵ�δ������,��õ�Ϊ���,���ѡ����ǷǸ��,��ô���ڽӵ㶼����DFS�д�����·�����ʵ�
			{
				if (child > 1)
					ans[at]++;
			}
			else if (low[G[at][i]] >= dfn[at])//����õ���ܷ��ʵ���С��Ŵ��ڵ���at������,��˵��ɾ��at��õ�����at�����ڵ���ͨ����
					ans[at]++;
		}//�Ѿ����ʹ���,��ôat����ܷ��ʵ���
		else if (G[at][i] != pre[at])
			low[at] = min(low[at], dfn[G[at][i]]);
	}
}

int mian()
{
	//��ͼ
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
	DFS(0);//����㿪ʼ

	return 0;
}