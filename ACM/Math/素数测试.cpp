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

//产生一个属于区间[s,t]的整数
inline int random(int s, int t){
	return s + rand() % (t - s + 1);
}

//测试val是否为素数
//true,素数		false,合数
bool FermatTest(ll val){
	int seed;srand(unsigned(time(0)));//time()包含于<ctime>
	for (int j = 0; j < 1000; ++j){//产生1000个随机数进行测试
		seed = random(2, 100000);
		if ((seed % val>0) && fastPow(seed, val - 1, val) != 1){
			return false;
		}
	}return true;
}

int main(){

	return 0;
}