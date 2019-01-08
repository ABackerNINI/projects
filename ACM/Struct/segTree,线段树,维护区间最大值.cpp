// template for ACM.cpp
//

#include "stdio.h"
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX(a,b) (a)<(b)?(b):(a)

struct Node{
	int max;
	int lazy;
};

class segTree{
public:
	//ά������[L,R]�ϵ����ֵ
	segTree(int L,int R){
		data = new Node[4 * R + 5];

		int bound = (R << 2) + 5;
		for (int i = 0; i < bound; ++i){
			data[i].max = 0;
			data[i].lazy = 0;
		}
	}

	void Build(int *Array, int L, int R, int at = 1){

	}

	//��������[l,r]
	void Modify(int l, int r, int add, int L, int R, int at = 1){
		if (l <= L&& R <= r){ data[at].max += add; data[at].lazy += add; return; }

		LazyDown(at);//�·�lazy���

		int mid = (L + R) >> 1;
		if (l <= mid)Modify(l, r, add, L, mid, at << 1);
		if (r > mid)Modify(l, r, add, mid + 1, R, (at << 1) + 1);

		int lc = at << 1;
		data[at].max = MAX(data[lc].max, data[lc | 1].max);
	}

	//ѯ������[l,r]���ֵ
	int Query(int l, int r, int L, int R, int at = 1){
		if (l <= L&& R <= r)return data[at].max;

		LazyDown(at);//�·�lazy���

		int mid = (L + R) >> 1; int lc = at << 1;
		if (l <= mid&&mid < r)return MAX(Query(l, r, L, mid, lc), Query(l, r, mid + 1, R, lc | 1));
		else if (l <= mid)return Query(l, r, L, mid, lc);
		else return Query(l, r, mid + 1, R, lc | 1);
	}

	//debug
	void print(int R){
		for (int i = 0; i < 4 * R; ++i)
			printf("%d: %d,%d\n", i, data[i].max, data[i].lazy);
	}

	~segTree(){ if (data)delete[] data; }

private:
	Node *data;

	inline void LazyDown(int at){
		if (data[at].lazy){
			int lc = at << 1;
			data[lc].max += data[at].lazy;
			data[lc].lazy += data[at].lazy;
			data[lc | 1].max += data[at].lazy;
			data[lc | 1].lazy += data[at].lazy;
			data[at].lazy = 0;
		}
	}
};

int main(){
	int L = 1, R = 10;//ά��������
	segTree tree(L, R);

	/*
	tree.Modify(3, 5, 3, L, R);
	printf("%d\n", tree.Query(1, 2, L, R));

	tree.Modify(1, 10, 1, L, R);
	printf("%d\n", tree.Query(1, 2, L, R));
	*/
	return 0;
}

