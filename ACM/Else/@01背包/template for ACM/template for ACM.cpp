//Template for ACM

#define ll long long
#define INF 0x7FFFFFFF7FFFFFFF

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include <map>
#include <list>
#include <cmath>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXBAG = 10000+5;//bag的最大可能值
int dp[MAXBAG][2];

//V[i]为石头的体积
//容量为bag的背包最多能装多少体积的石头,石头不重复使用
//注意:体积不能为负
int bag_01(int bag, const int *V, int n){
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < n; ++i){
		for (int j = 1; j <= bag; ++j){
			dp[j][i & 1] = max(dp[j][(i + 1) & 1], j >= V[i] ? dp[j - V[i]][(i + 1) & 1] + V[i] : 0);
		}
	}
	return dp[bag][(n + 1) & 1];
}

//V[i]为石头的体积,W[i]为石头的价值
//容量为bag的背包最多能装多少价值的石头,石头不重复使用
//注意:体积,价值不能为负
int bag_01(int bag, const int *V, const int *W, int n){
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < n; ++i){
		for (int j = 1; j <= bag; ++j){
			dp[j][i & 1] = max(dp[j][(i + 1) & 1], j >= V[i] ? dp[j - arr[i]][(i + 1) & 1] + W[i] : 0);
		}
	}
	return dp[bag][(n + 1) & 1];
}

int main(){

	return 0;
}