//#include...

#define MAX 10000+5

int C[MAX];//�����Ӧ�����յ���ɫ
vector<int>Ga[MAX];//A��ϵͼ,������㲻��ͬɫ
vector<int>Gb[MAX];//B��ϵͼ,�������ֻ��ͬɫ


//�����Ƿ��ͻ
bool DFS(int at)
{
	int c = (C[at] == 'B' ? 'W' : 'B');
	while (!Ga[at].empty())//����A��ϵ
	{
		if (C[Ga[at].back()] != 0)
		{
			if (C[Ga[at].back()] != c)
				return false;
		}
		else
		{
			C[Ga[at].back()] = c;

			if (!DFS(Ga[at].back()))
				return false;
		}
		Ga[at].pop_back();
	}

	while (!Gb[at].empty())//����B��ϵ
	{
		if (C[Gb[at].back()] != 0)
		{
			if (C[Gb[at].back()] != C[at])
				return false;
		}
		else
		{
			C[Gb[at].back()] = C[at];
			if (!DFS(Gb[at].back()))
				return false;
		}
		Gb[at].pop_back();
	}

	return true;
}

int main()
{
	memset(C, 0, sizeof(C));
	
	//��ͼ
	/*sample:
	int n, p, m;//����,a��ϵ��,b��ϵ��
	scanf("%d%d%d", &n, &p, &m);

	int x, y;
	for (int i = 0; i<p; i++)
	{
		scanf("%d%d", &x, &y);
		Ga[x].push_back(y);
		Ga[y].push_back(x);
	}//����A��ϵ

	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &x, &y);
		Gb[x].push_back(y);
		Gb[y].push_back(x);
	}//����B��ϵ*/


	C[0] = 'B';//������㸳ɫ����ʼDFS
	if (!DFS(0))//������ֳ�ͻ,˵�����ɶ���ɫ
	{
		//printf("No\n");
	}

	return 0;
}

