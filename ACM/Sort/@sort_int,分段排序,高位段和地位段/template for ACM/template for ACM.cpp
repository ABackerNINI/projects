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

void sort_unsigned_int(unsigned int *begin, unsigned int *end){
	int n = end - begin;
	vector<unsigned int>*vec = new vector<unsigned int>[1 << 16];

	unsigned int *b = begin;
	while (b != end){
		vec[*b >> 16].push_back(*(b++));
	}

	vector<unsigned int>::iterator it;
	for (int i = 0; i < (1 << 16); ++i){
		if (vec[i].size()>0){
			if (vec[i].size() > 1)sort(vec[i].begin(), vec[i].end());
			it = vec[i].begin();
			for (; it != vec[i].end(); ++it){
				*(begin++) = *it;
			}
		}
	}

	delete[]vec;
}

unsigned int arr[] = { 95, 5564, 5555665, 45455, 55779442 };

int main(){
	sort_unsigned_int(arr, arr + 5);

	return 0;
}