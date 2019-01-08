//Template for ACM

#define ll long long
#define INF 0x7FFFFFFF
#define LINF 0x7FFFFFFF7FFFFFFF

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

#define MAXN ()

template<typename T>class RMQ_MIN_VAL{
public:
	RMQ_MIN_VAL(T *arr, int n) :arr(arr), n(n){
		bd = log2(n) + 1;
		_F = new T[n*bd];

		for (int i = 0; i < n; ++i)F(i, 0) = arr[i];

		for (int k = 1, j = 1; j < bd; k <<= 1, ++j){
			for (int i = 0; i < n; ++i){
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
	T Query(int l, int r){
		int k = log2(r - l + 1);
		return min(F(l,k), F(r - (1 << k) + 1,k));
	}

	~RMQ_MIN_VAL(){ if (_F)delete[]_F; }

private:
	T *arr; int n, bd; T *_F;
	T &F(int i, int j){ return _F[bd*i + j]; }
};


template<typename T>class RMQ_MAX_VAL{
public:
	RMQ_MAX_VAL(T *arr, int n) :arr(arr), n(n){
		bd = log2(n) + 1;
		_F = new T[n*bd];

		for (int i = 0; i < n; ++i)F(i, 0) = arr[i];

		for (int k = 1, j = 1; j < bd; k <<= 1, ++j){
			for (int i = 0; i < n; ++i){
				F(i, j) = max(F(i, j - 1), i + k < n ? F(i + k, j - 1) : (T)-LINF);
			}
		}

		//debug
		/*for (int i = 0; i < n; ++i){
			for (int j = 0; j < bd; ++j)printf("%d ", F(i, j));
			printf("\n");
		}*/
	}

	//返回arr[l,r]中的最大值
	T Query(int l, int r){
		int k = log2(r - l + 1);
		return max(F(l, k), F(r - (1 << k) + 1, k));
	}

	~RMQ_MAX_VAL(){ if (_F)delete[]_F; }

private:
	T *arr; int n, bd; T *_F;
	T &F(int i, int j){ return _F[bd*i + j]; }
};


template<typename T>class RMQ_MIN_POS{
public:
	RMQ_MIN_POS(T *arr, int n) :arr(arr), n(n){
		bd = log2(n) + 1;
		_F = new P[n*bd];

		for (int i = 0; i < n; ++i){ F(i, 0).val = arr[i]; F(i, 0).pos = i; }

		for (int k = 1, j = 1; j < bd; k <<= 1, ++j){
			for (int i = 0; i < n; ++i){
				if (F(i, j - 1).val < (i + k < n ? F(i + k, j - 1).val : (T)LINF)){
					F(i, j).val = F(i, j - 1).val; F(i, j).pos = F(i, j - 1).pos;
				}
				else{
					F(i, j).val = F(i + k, j - 1).val; F(i, j).pos = F(i + k, j - 1).pos;
				}
			}
		}

		//debug
		/*for (int i = 0; i < n; ++i){
			for (int j = 0; j < bd; ++j)printf("%d,%d ", F(i, j).pos, F(i, j).val);
			printf("\n");
		}*/
	}

	//返回arr[l,r]中的最小值的下标
	T Query(int l, int r){
		int k = log2(r - l + 1);

		return F(l, k).val < F(r - (1 << k) + 1, k).val ? F(l, k).pos : F(r - (1 << k) + 1, k).pos;
	}

	~RMQ_MIN_POS(){ if (_F)delete[]_F; }

private:
	struct P{ T val; int pos; };
	T *arr; int n, bd; P *_F;
	P &F(int i, int j){ return _F[bd*i + j]; }
};


template<typename T>class RMQ_MAX_POS{
public:
	RMQ_MAX_POS(T *arr, int n) :arr(arr), n(n){
		bd = log2(n) + 1;
		_F = new P[n*bd];

		for (int i = 0; i < n; ++i){ F(i, 0).val = arr[i]; F(i, 0).pos = i; }

		for (int k = 1, j = 1; j < bd; k <<= 1, ++j){
			for (int i = 0; i < n; ++i){
				if (F(i, j - 1).val < (i + k < n ? F(i + k, j - 1).val : (T)-LINF)){
					F(i, j).val = F(i + k, j - 1).val; F(i, j).pos = F(i + k, j - 1).pos;
				}
				else{
					F(i, j).val = F(i, j - 1).val; F(i, j).pos = F(i, j - 1).pos;
				}
			}
		}

		//debug
		/*for (int i = 0; i < n; ++i){
			for (int j = 0; j < bd; ++j)printf("%d,%d ", F(i, j).pos, F(i, j).val);
			printf("\n");
		}*/
	}

	//返回arr[l,r]中的最大值的下标
	T Query(int l, int r){
		int k = log2(r - l + 1);

		return F(l, k).val < F(r - (1 << k) + 1, k).val ? F(r - (1 << k) + 1, k).pos : F(l, k).pos;
	}

	~RMQ_MAX_POS(){ if (_F)delete[]_F; }

private:
	struct P{ T val; int pos; };
	T *arr; int n, bd; P *_F;
	P &F(int i, int j){ return _F[bd*i + j]; }
};

/*int arr[] = { 1, 7, 3, 2, 4, 5, 0, 9 };*/

int main(){
	/*RMQ_MIN_POS<int>rmq(arr, 8);
	int l, r;
	while (scanf("%d%d", &l, &r) == 2){
		cout << rmq.Query(l, r) << endl;
	}*/

	return 0;
}