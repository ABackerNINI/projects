//Template for ACM

#define ll long long
#define INF 0x7FFFFFFF
#define LINF 0x7FFFFFFFFFFFFFFF

#include "stdio.h"
#include "stdlib.h"

#include <map>
#include <queue>
#include <stack>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN (1000+5)

//(a^b)%mod
ll fastPow(ll a, ll b, ll mod){
	ll ret = 1; a %= mod;
	while (b){
		if (b & 1){ ret *= a; ret %= mod; }
		a *= a; a %= mod;
		b >>= 1;
	}
	return ret;
}

//����һ����������[s,t]������
inline int random(int s, int t){
	return s + rand() % (t - s + 1);
}

//����val�Ƿ�Ϊ����
//true,����		false,����
bool FermatTest(ll val){
	int seed;srand(unsigned(time(0)));//time()������<ctime>
	for (int j = 0; j < 1000; ++j){//����1000����������в���
		seed = random(2, 100000);
		if ((seed % val>0) && fastPow(seed, val - 1, val) != 1){
			return false;
		}
	}return true;
}

int main(){

	return 0;
}