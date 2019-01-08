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

#define MAXN (1000+5)

int lcs[MAXN][MAXN];//lcs的右下端保存的是最大公共子序列的长度

//返回其中一个最大公共子序列
string LCS(const string &s1,const string &s2){
	for (int i = 0; i < MAXN; ++i){ lcs[0][i] = 0; lcs[i][0] = 0; }

	for (int i = 1; i <= s1.size(); ++i){
		for (int j = 1; j <= s2.size(); ++j){
			if (s1[i - 1] == s2[j - 1])
				lcs[i][j] = lcs[i - 1][j - 1] + 1;
			else lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
		}
	}
	string ret = "";
	for (int i = s1.size() - 1, j = s2.size() - 1; i >= 0 && j >= 0;){
		if (s1[i] == s2[j]){ ret += s1[i]; --i; --j; }
		else{
			if (lcs[i + 1][j + 1] == lcs[i][j]){ --i; --j; }
			else{
				if (lcs[i][j + 1] >= lcs[i + 1][j])--i;
				else --j;
			}
		}
	}

	reverse(ret.begin(), ret.end());
	return ret;
}

int main(){
	string a, b; cin >> a >> b;
	cout << LCS(a, b) << endl;

	return 0;
}