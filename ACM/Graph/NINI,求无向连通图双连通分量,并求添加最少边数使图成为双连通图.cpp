//#include...

#define MAX 100000+5

vector<int>G[MAX];
int cnt;
int pre[MAX];
int cmt[MAX];//�����ļ���,���cmt[i]==cmt[j],��ô��i�͵�j����ͬһ˫��ͨ����
int in[MAX + 3000],out[MAX + 3000];//��ĳ����
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
	cmt[at] = cnt++;//�����Լ��ļ���
	int v;
	for (int i = 0; i < G[at].size(); i++)//ö���ڽӵ�
	{
		v = G[at][i];
		if (v == pre[at])//�������׽ڵ�
			continue;
		if (cmt[v] == -1)//����õ㻹δ���伯��,DFS�õ�
		{
			pre[v] = at;
			DFS(v);
		}
		else if (cmt[v] != cmt[at])//����õ��Ѿ������˼���,˵��at����õ��γ��˻�,��pre[v->at]�����е�����ͬһ��˫��ͨ����,��pre�����޸�Ϊ��ͬ�ļ���
		{
			for (int j = at; j != v; j = pre[j])
			{
				if (change[j])//����õ��Ѿ�����һ��˫��ͨ����,��ô��pre·���ϵ������������˫��ͨ����
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
	//����:�������˫��ͨ���������ӹ�ϵ
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
		if (in[cmt[i]] == 1 && out[cmt[i]] == 1)//����õ�ĳ���ȶ�Ϊ1,��ô����������Ҷ�ڵ�
		{
			ans++;
			in[cmt[i]] = 0;
		}
	}
	return (ans + 1) / 2;//������Ҷ�ڵ�ĳ���Ȳ�������Ϊ2,�������ӵı���
}

int main()
{
	//��ͼ
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

	DFS(1);//������㿪ʼDFS��˫��ͨ����

	printf("%d\n", getMinEages());
	return 0;
}

