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

//ͨ������hash�ķ������ַ���ӳ��Ϊtrue��false
class HashString {
public:
	//maxnΪ������push�����ַ�������
	HashString(int maxn) :data(NULL), maxn(maxn << 1), size(0) {
		data = new vector<LL>[this->maxn];
	}

	void Insert(const char *string) {
		++size;
		data[Hash(string)].push_back(Key(string));
	}

	//����Ѿ�push��,����true,���򷵻�false
	bool IsExist(const char *string)const {
		unsigned int hash = Hash(string);
		int len = data[hash].size();
		if (len > 0) {
			LL key = Key(string);
			for (int i = 0; i < len; ++i) {
				if (data[hash][i] == key)return true;
			}
		}
		return false;
	}

	int Size() {
		return size;
	}
	double Alpha()const {
		return (double)size / maxn;
	}

	bool operator[](const char *string)const {
		return IsExist(string);
	}

	~HashString() {
		if (data)delete[]data;
	}

	//debug ���size�ֱ�Ϊ0,1,2,3������������
	void print_1() {
		int n[4] = { 0 };
		for (int i = 0; i < maxn; ++i) {
			++n[data[i].size()];
		}
		printf("%d %d %d %d\n", n[0], n[1], n[2], n[3]);
	}
private:
	vector<LL>*data; int maxn, size;
	const static unsigned int seed1 = 131; LL seed2 = 1000000007;

	unsigned int Hash(const char *string)const {
		unsigned int hash = 0;
		while (*string) {
			hash = hash*seed1 + *string++;
		}
		return hash%maxn;
	}
	LL Key(const char *string)const {
		LL hash = 0;
		while (*string) {
			hash = hash*seed2 + *string++;
		}
		return hash;
	}
};

//����[0,9999999]��Χ��������Ϊ����,��HashString���в���
void test_1() {
	DWORD begin = GetTickCount();
	HashString h(10000000); char s[10];

	for (int i = 0; i < 10000000; ++i) {
		sprintf(s, "%06d", i); h.Insert(s);
	}
	h.print_1();
	printf("%dms\n", GetTickCount() - begin);
}

int main() {
	test_1();

	return 0;
}