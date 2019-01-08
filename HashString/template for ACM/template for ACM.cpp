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

#include <ctime>
#include <windows.h>

using namespace std;

#define MAXN ()

//通过两次hash的方法将字符串是否存在的信息存储起来,IsExist(string)如果存在返回true,不存在返回false;重载了[]运算
class HashString{
public:
	HashString(int maxn) :data(NULL), maxn(maxn << 1), size(0){
		data = new vector<LL>[this->maxn];
	}

	void Insert(const char *string){
		++size;
		data[Hash(string)].push_back(Key(string));
	}

	bool IsExist(const char *string)const{
		unsigned int hash = Hash(string);
		int len = data[hash].size();
		if (len > 0){
			LL key = Key(string);
			for (int i = 0; i < len; ++i){
				if (data[hash][i] == key)return true;
			}
		}
		return false;
	}
	bool operator[](const char *string)const{
		return IsExist(string);
	}
	double Alpha()const{
		return (double)size / maxn;
	}
	~HashString(){
		if (data)delete[]data;
	}

	//debug
	void print(){
		/*int n = 0;
		for (int i = 0; i < maxn; ++i)if (n < data[i].size())n = data[i].size();
		printf("%d\n", n);*/
		int n[4] = { 0 };
		for (int i = 0; i < maxn; ++i){
			++n[data[i].size()];
		}
		printf("%d %d %d %d\n", n[0], n[1], n[2], n[3]);
	}
private:
	vector<LL>*data; int maxn, size;
	const static unsigned int seed1 = 131; LL seed2 = 1000000007;

	unsigned int Hash(const char *string)const{
		unsigned int hash = 0;
		while (*string){
			hash = hash*seed1 + *string++;
		}
		return hash%maxn;
	}
	LL Key(const char *string)const{
		LL hash = 0;
		while (*string){
			hash = hash*seed2 + *string++;
		}
		return hash;
	}
};

void test(){
	DWORD begin = GetTickCount();
	HashString h(10000000); char s[10];

	for (int i = 0; i < 10000000; ++i){
		sprintf(s, "%06d", i); h.Insert(s);
	}
	h.print();
	printf("t:%d\n", GetTickCount() - begin);
}

int main(){
	test(); 

	return 0;
}