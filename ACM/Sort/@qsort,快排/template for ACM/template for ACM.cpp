//Template for ACM

#define ll long long
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

#include <ctime>

using namespace std;

#define MAXN ()

inline int random(int s, int t){
	return s + rand() % (t - s + 1);
}

template<typename T>void qsort(T *begin,T *end){
	int L = 0, R = end - begin;
	int k = random(L, R); printf("%d\n", k);

	T mid = begin[k]; T *b = begin, *e = end;
	for (int i = 0; i < R; ++i){
		if (begin[i] < mid)swap(*(b++), begin[i]);
		else swap(*(--e), begin[i]);
	}
}

int arr[] = { 1, 3, 2, 0, 9, 4, 6, 3, 0 };

int main(){
	srand(unsigned(time(0))); 
	qsort(arr, arr + 9);

	return 0;
}