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

const int MAXBAG = 10000+5;//bag��������ֵ
int dp[MAXBAG][2];

//V[i]Ϊʯͷ�����
//����Ϊbag�ı��������װ���������ʯͷ,ʯͷ���ظ�ʹ��
//ע��:�������Ϊ��
int bag_01(int bag, const int *V, int n){
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i < n; ++i){
		for (int j = 1; j <= bag; ++j){
			dp[j][i & 1] = max(dp[j][(i + 1) & 1], j >= V[i] ? dp[j - V[i]][(i + 1) & 1] + V[i] : 0);
		}
	}
	return dp[bag][(n + 1) & 1];
}

//V[i]Ϊʯͷ�����,W[i]Ϊʯͷ�ļ�ֵ
//����Ϊbag�ı��������װ���ټ�ֵ��ʯͷ,ʯͷ���ظ�ʹ��
//ע��:���,��ֵ����Ϊ��
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