//#include...

#define MAX 10000+5

int C[MAX];//保存对应点最终的颜色
vector<int>Ga[MAX];//A关系图,即点与点不能同色
vector<int>Gb[MAX];//B关系图,即点与点只能同色


//返回是否冲突
bool DFS(int at)
{
	int c = (C[at] == 'B' ? 'W' : 'B');
	while (!Ga[at].empty())//处理A关系
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

	while (!Gb[at].empty())//处理B关系
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
	
	//建图
	/*sample:
	int n, p, m;//点数,a关系数,b关系数
	scanf("%d%d%d", &n, &p, &m);

	int x, y;
	for (int i = 0; i<p; i++)
	{
		scanf("%d%d", &x, &y);
		Ga[x].push_back(y);
		Ga[y].push_back(x);
	}//创建A关系

	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &x, &y);
		Gb[x].push_back(y);
		Gb[y].push_back(x);
	}//创建B关系*/


	C[0] = 'B';//将任意点赋色并开始DFS
	if (!DFS(0))//如果发现冲突,说明不可二着色
	{
		//printf("No\n");
	}

	return 0;
}

