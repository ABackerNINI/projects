//Template for ACM

#define ll long long
#define INF 0x7FFFFFFF
#define LINF 0x7FFFFFFFFFFFFFFF

#include "stdio.h"
#include "stdlib.h"

#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN ()

//求数组arr[]的最长上升子序列
int LIS(int *arr, int n){//longest increasing subsequence
	int *dp = new int[n + 5];//dp[i]表示长度为i+1的上升子序列的最小结尾
	int where, idx = 0;

	dp[idx++] = arr[0];
	for (int i = 1; i < n; ++i){
		if (arr[i]>dp[idx - 1]){
			dp[idx++] = arr[i];
		}
		else{
			where = lower_bound(dp, dp + idx, arr[i]) - dp;
			dp[where] = min(dp[where], arr[i]);
		}
	}

	delete[]dp;//dp[0->(idx-1)]保存着其中一组最长上升子序列

	return idx;
}

int arr[50000 + 5];

int main(){
	int n; cin >> n;
	for (int i = 0; i < n; ++i)scanf("%d", &arr[i]);

	printf("%d\n", LIS(arr, n));

	return 0;
}