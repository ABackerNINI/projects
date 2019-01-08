// template for ACM.cpp
//

#define ll long long
#define INF 0x7FFFFFFF
#define MAX(a,b) (a)<(b)?(b):(a)
#define MIN(a,b) (a)<(b)?(a):(b)

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <map>
#include <bitset>
#include <queue>
#include <string>
#include <set>
#include <stack>
#include <numeric>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 100

bool used[MAXN];
int belong[MAXN];//保存最终的连接方案,右边点对应的左边点idx
vector<int>G[MAXN];

bool find(int x){
	int v;
	for (int i = 0; i < G[x].size(); ++i){
		v = G[x][i];
		if (!used[v]){
			used[v] = 1;
			if (belong[v] == -1 || find(belong[v])){
				belong[v] = x;
				return true;
			}
		}
	}

	return false;
}

//[l,r]是左边点的范围
int match(int l,int r){
	memset(belong, -1, sizeof(belong));

	int ans = 0;
	for (int i = l; i <= r; ++i){//枚举左边的点
		if (!G[i].empty()){
			memset(used, 0, sizeof(used));
			if (find(i))++ans;
		}
	}
	return ans;
}

int main(){
	int l, r;
	//
	//建图
	//
	printf("%d\n", match(l, r));

	return 0;
}