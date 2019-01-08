//Template for ACM

#define ll long long
#define INF 0x7FFFFFFF
#define ABS(val) ((val)>0)?(val):(-(val))
#define MAX(a,b) (b)<(a)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
#define FOR(i,l,r) for(int i=(l);i<=(r);++i)
#define VIT(type) vector<type>::iterator
#define REP(n) int _rep=n;while(_rep--)

#include <map>
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <algorithm>
#include <cmath>
#include <stack>
#include <string>
#include <queue>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

#define MAXN 1000000+5

struct Node{
	int sum;
	int lazy;
};

class segTree{

public:
	//维护区间[L,R]上的和
	segTree(int L, int R){
		int bound = (R << 2) + 5;
		data = new Node[bound];

		for (int i = 0; i < bound; ++i){
			data[i].sum = 0;
			data[i].lazy = 0;
		}
	}

	void Build(int *Array, int L, int R, int at = 1){

	}

	//更新区间[l,r]
	void Modify(int l, int r, int add, int L, int R, int at = 1){
		if (l <= L&& R <= r){ data[at].sum += (R - L + 1)*add; data[at].lazy += add; return; }

		int mid = (L + R) >> 1;
		LazyDown(at, mid - L + 1, R - mid);//下放lazy标记

		if (l <= mid)Modify(l, r, add, L, mid, at << 1);
		if (r > mid)Modify(l, r, add, mid + 1, R, (at << 1) + 1);

		int lc = at << 1;
		data[at].sum = data[lc].sum + data[lc | 1].sum;
	}

	//询问区间[l,r]最大值
	int Query(int l, int r, int L, int R, int at = 1){
		if (l <= L&& R <= r)return data[at].sum;

		int mid = (L + R) >> 1;
		LazyDown(at, mid - L + 1, R - mid);//下放lazy标记

		int lc = at << 1;
		if (l <= mid&&mid < r)return Query(l, r, L, mid, lc) + Query(l, r, mid + 1, R, lc | 1);
		else if (l <= mid)return Query(l, r, L, mid, lc);
		else return Query(l, r, mid + 1, R, lc | 1);
	}

	//debug
	void print(int R){
		for (int i = 0; i < 4 * R; ++i)
			printf("%d: %d,%d\n", i, data[i].sum, data[i].lazy);
	}

	~segTree(){ if (data)delete[] data; }

	void clear(){ if (data)delete[] data; }

private:
	Node *data;

	inline void LazyDown(int at, int nl, int nr){
		if (data[at].lazy){
			int lc = at << 1;
			data[lc].sum += nl*data[at].lazy;
			data[lc].lazy += data[at].lazy;
			data[lc | 1].sum += nr*data[at].lazy;
			data[lc | 1].lazy += data[at].lazy;
			data[at].lazy = 0;
		}
	}
};

int main()
{
	int L, R;
	segTree tree(L, R);

	tree.Modify(0, 100, 1, L, R);
	tree.Query(0, 100, L, R);

	return 0;
}