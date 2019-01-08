// template for ACM.cpp
//

#include "stdio.h"
#include <iostream>
#include <algorithm>

using namespace std;

#define MIN(a,b) (a)<(b)?(a):(b)

struct Node{
	int min;
	int lazy;
};

class segTree{
public:
	//维护区间[L,R]上的最小值
	segTree(int L,int R){
		data = new Node[4 * R + 5];

		int bound = (R << 2) + 5;
		for (int i = 0; i < bound; ++i){
			data[i].min = 0;
			data[i].lazy = 0;
		}
	}

	void Build(int *Array, int L, int R, int at = 1){

	}

	//更新区间[l,r]
	void Modify(int l, int r, int add, int L, int R, int at = 1){
		if (l <= L&& R <= r){ data[at].min += add; data[at].lazy += add; return; }

		LazyDown(at);//下放lazy标记

		int mid = (L + R) >> 1;
		if (l <= mid)Modify(l, r, add, L, mid, at << 1);
		if (r > mid)Modify(l, r, add, mid + 1, R, (at << 1) + 1);

		int lc = at << 1;
		data[at].min = MIN(data[lc].min, data[lc | 1].min);
	}

	//询问区间[l,r]最大值
	int Query(int l, int r, int L, int R, int at = 1){
		if (l <= L&& R <= r)return data[at].min;

		LazyDown(at);//下放lazy标记

		int mid = (L + R) >> 1; int lc = at << 1;
		if (l <= mid&&mid < r)return MIN(Query(l, r, L, mid, lc), Query(l, r, mid + 1, R, lc | 1));
		else if (l <= mid)return Query(l, r, L, mid, lc);
		else return Query(l, r, mid + 1, R, lc | 1);
	}

	//debug
	void print(int R){
		for (int i = 0; i < 4 * R; ++i)
			printf("%d: %d,%d\n", i, data[i].min, data[i].lazy);
	}

	~segTree(){ if (data)delete[] data; }

private:
	Node *data;

	inline void LazyDown(int at){
		if (data[at].lazy){
			int lc = at << 1;
			data[lc].min += data[at].lazy;
			data[lc].lazy += data[at].lazy;
			data[lc | 1].min += data[at].lazy;
			data[lc | 1].lazy += data[at].lazy;
			data[at].lazy = 0;
		}
	}
};

int main(){
	int L = 1, R = 10;//维护的区间
	segTree tree(L, R);
	
	/*tree.Modify(3, 5, 3, L, R);
	printf("%d\n", tree.Query(1, 2, L, R));

	tree.Modify(1, 10, 1, L, R);
	printf("%d\n", tree.Query(1, 2, L, R));

	tree.Modify(2, 10, 1, L, R);
	printf("%d\n", tree.Query(1, 2, L, R));


	tree.Modify(1, 3, 2, L, R);
	printf("%d\n", tree.Query(1, 10, L, R));*/
	
	return 0;
}

