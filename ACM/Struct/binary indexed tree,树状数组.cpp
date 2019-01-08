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

const int MAXN = 0;

template<typename T>class BinaryIndexedTree{
public:
	BinaryIndexedTree(int maxLen) :maxLen(maxLen + 5){ data = new T[maxLen + 5]; for (int i = 0; i < maxLen + 5; ++i)data[i] = 0; }

	ll sum(int n){
		ll ret = 0;
		while (n > 0){
			ret += data[n];
			n -= lowbit(n);
		}return ret;
	}

	void modify(int pos, int add){
		while (pos <= maxLen){
			data[pos] += add;
			pos += lowbit(pos);
		}
	}

	~BinaryIndexedTree(){ if (data)delete[]data; }
private:
	T *data;
	int maxLen;

private:
	inline int lowbit(int x){ return x&(-x); }
};



//ÇóÄæÐò¶Ô
void test_1() {
	struct P {
		int val, idx;
		bool operator<(const P &p) { return val < p.val; }
	}p[50000 + 5];

	int n; cin >> n;
	BinaryIndexedTree<int>t(n);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &p[i].val); p[i].idx = i + 1;
	}
	sort(p, p + n);

	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		t.modify(p[i].idx, 1);
		ans += t.sum(n) - t.sum(p[i].idx);
	}

	printf("%lld\n", ans);
}

int main(){
	test_1();

	return 0;
}