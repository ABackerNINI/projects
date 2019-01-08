
#define ll long long
#define INF 0x7FFFFFFF

#include "stdio.h"
#include <iostream>

using namespace std;

const int MAXN = 100;

ll fact[MAXN];//Ô¤´¦ÀíµÄ½×³Ë(mod p)

//(a^b)%p
ll fastPow(ll a, ll b, ll p){
	ll res = 1;
	while (b != 0) {
		if (b & 1) res = (res * a) % p;
		a = (a*a) % p;
		b >>= 1;
	}
	return res;
}

//C(n,m)%p
ll C(int n, int m, int p){
	if (m > n - m)m = n - m;
	if (m == 0)return 1;

	ll ret = (fact[n] * fastPow(fact[m] * fact[n - m], p - 2, p)) % p;

	return ret;
}

//p must be prime
ll Lucas(int n, int m, int p){
	if (p == 1)return 0;

	fact[0] = 1;
	for (int i = 1; i <= n; ++i)fact[i] = (i*fact[i - 1]) % p;

	ll ans = 1; int _n, _m;
	while (n&&m&&ans){
		_n = n%p; _m = m%p;
		if (_n < _m)return 0;

		ans = (ans*C(_n, _m, p)) % p;
		n /= p; m /= p;
	}

	return ans;
}


int main()
{
	//printf("%lld\n", Lucas(9, 2, 13));

	return 0;
}