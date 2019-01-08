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

#include "windows.h"

using namespace std;

const int MAXN = 0;

template<typename T>class Queue_iterator{
#define UPCHECK(p) if(p==end)p=cbegin+1
#define DWCHECK(p) if(p==cbegin)p=end-1
#define UP(p,n) p+=n;if(p >= end)p = cbegin + 1 + (p - end)
#define DW(p,n) p-=n;if(p <= cbegin)p = end - 1 + (p - cbegin)

	typedef Queue_iterator iterator;

public:
	Queue_iterator(){}
	Queue_iterator(T *p, T *cbegin, T *end) :p(p), cbegin(cbegin), end(end){}

	iterator &operator++(){ ++p; UPCHECK(p); return *this; }//前++
	iterator &operator--(){ --p; DWCHECK(p); return *this; }//前--

	iterator operator++(int){ iterator _it = *this; ++p; UPCHECK(p); return _it; }//后++
	iterator operator--(int){ iterator _it = *this; --p; DWCHECK(p); return _it; }//后--

	iterator operator+(int n)const{ iterator _it = *this; return _it += n; }
	iterator operator-(int n)const{ iterator _it = *this; return _it -= n; }

	//int operator-(iterator &it){ return p - it.p; }//在使用了push_front()之后返回会出错

	iterator &operator+=(int n){ UP(p, n); return *this; }
	iterator &operator-=(int n){ DW(p, n); return *this; }

	T &operator*()const{ return *p; }
	T *operator->()const{ return p; }
	T &operator[](int n)const{ T *_p = p; _p += n; UPCHECK(_p); return *_p; }

	//bool operator<(const iterator &it)const{ return p < it.p; }  //在使用了push_front()之后返回会出错
	//bool operator>(const iterator &it)const{ return p > it.p; }  //在使用了push_front()之后返回会出错
	//bool operator>=(const iterator &it)const{ return p >= it.p; }//在使用了push_front()之后返回会出错
	//bool operator<=(const iterator &it)const{ return p <= it.p; }//在使用了push_front()之后返回会出错
	bool operator==(const iterator &it)const{ return p == it.p; }
	bool operator!=(const iterator &it)const{ return p != it.p; }
private:
	T *p, *cbegin, *end;

#undef UPCHECK
#undef DWCHECK
#undef UP
#undef DW
};

template<typename T>class Queue{
#define UPCHECK(var) if(var==maxLen)var=0
#define DWCHECK(var) if(var==-1)var=maxLen-1

public:
	typedef Queue_iterator<T> iterator;

	//Queue(){}

	//maxLen为允许push进元素的最大个数,超过一个则长度变为0,超过两个长度变为1,以此类推;不提供溢出检查...
	Queue(const int maxLen = 1000000) :maxLen(maxLen + 1){ data = (T *)malloc(sizeof(T)*(maxLen + 1)); }

	void push_back(const T &value){ data[Back] = value;  ++Back; UPCHECK(Back); }
	void push_front(const T &value){ --Front; DWCHECK(Front);  data[Front] = value; }

	void pop_front(){ ++Front; UPCHECK(Front); }
	void pop_back(){ --Back; DWCHECK(Back); }

	T &front(){ return data[Front]; }
	T &back(){ return data[Back == 0 ? maxLen - 1 : Back - 1]; }

	void clear(){ Front = 0; Back = 0; }
	bool empty(){ return Front == Back; }
	int size(){ int len = Back - Front; return len >= 0 ? len : len + maxLen; }
	//void resize(const int maxLen){ if (data)delete[]data; clear(); this->maxLen = maxLen; }

	iterator begin(){ return iterator(&data[Front], data - 1, &data[maxLen]); }//返回指向队首的迭代器
	iterator end(){ return iterator(&data[Back], data - 1, &data[maxLen]); }//返回指向队尾下一个位置的迭代器

	T &operator[](int idx){ idx += Front; UPCHECK(idx); return data[idx]; }

	~Queue(){ if (data)delete[] data; }

private:
	T *data;
	int Front = 0, Back = 0;//Front指向刚push_front()写入的位置,Back指向将要push_back()写入的位置
	int maxLen;//允许push进元素的最大个数+1

#undef UPCHECK
#undef DWCHECK
};

int main(){
	Queue<int>q;
	for (int i = 0; i < 5; ++i)q.push_back(i);
	for (int i = 0; i < 7; ++i)q.push_front(i);
	Queue<int>::iterator it, end;
	it = q.begin(); end = q.end();
	for (; it != end; ++it){ printf("%d\n", *it); }

	return 0;
}