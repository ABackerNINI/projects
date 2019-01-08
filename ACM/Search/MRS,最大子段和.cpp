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

#define MAXN (50000+5)

ll arr[MAXN];
ll dp[MAXN];

ll maxSubSequence(int n){
	dp[0] = 0; ll ret = 0;
	for (int i = 1; i <= n; ++i){
		dp[i] = max(dp[i - 1] + arr[i], arr[i]);
		if (ret < dp[i])ret = dp[i];
	}return ret;
}

int main(){
	int n; cin >> n;
	for (int i = 1; i <= n; ++i){
		scanf("%lld", &arr[i]);
	}
	printf("%lld", maxSubSequence(n));

	return 0;
}