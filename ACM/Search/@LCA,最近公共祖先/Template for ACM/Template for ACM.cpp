//Template for ACM

#define LL long long
#define INF 0x7FFFFFFF
#define LINF 0x7FFFFFFF7FFFFFFF

#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN ()

template<typename T>class RMQ_MIN_VAL {
public:
	RMQ_MIN_VAL(T *arr, int n) :arr(arr), n(n) {
		bd = log2(n) + 1;
		_F = new T[n*bd];

		for (int i = 0; i < n; ++i)F(i, 0) = arr[i];

		for (int k = 1, j = 1; j < bd; k <<= 1, ++j) {
			for (int i = 0; i < n; ++i) {
				F(i, j) = min(F(i, j - 1), i + k < n ? F(i + k, j - 1) : (T)LINF);
			}
		}

		//debug
		/*for (int i = 0; i < n; ++i){
		for (int j = 0; j < bd; ++j)printf("%d ", F(i, j));
		printf("\n");
		}*/
	}

	//返回arr[l,r]中的最小值
	T Query(int l, int r) {
		int k = log2(r - l + 1);
		return min(F(l, k), F(r - (1 << k) + 1, k));
	}

	~RMQ_MIN_VAL() { if (_F)delete[]_F; }

private:
	T *arr; int n, bd; T *_F;
	T &F(int i, int j) { return _F[bd*i + j]; }
};

template<typename DataType>class LCA {
public:
	struct Data{
		DataType &data; int idx;
	};

public:

	LCA(vector<Data>*root) :root(root) {}
	DataType &Query() {}

private:
	vector<DataType>*root;
};

int main() {


	return 0;
}