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

	iterator &operator++(){ ++p; UPCHECK(p); return *this; }
	iterator &operator--(){ --p; DWCHECK(p); return *this; }

	iterator operator++(int){ iterator _it = *this; ++p; UPCHECK(p); return _it; }
	iterator operator--(int){ iterator _it = *this; --p; DWCHECK(p); return _it; }

	iterator operator+(int n)const{ iterator _it = *this; return _it += n; }
	iterator operator-(int n)const{ iterator _it = *this; return _it -= n; }

	int operator-(iterator &it){ return p - it.p; }//use only if push back only

	iterator &operator+=(int n){ UP(p, n); return *this; }
	iterator &operator-=(int n){ DW(p, n); return *this; }

	T &operator*()const{ return *p; }
	T *operator->()const{ return p; }
	T &operator[](int n)const{ T *_p = p; _p += n; UPCHECK(_p); return *_p; }

	bool operator<(const iterator &it)const{ return p < it.p; }//use only if push back only
	bool operator>(const iterator &it)const{ return p > it.p; }//use only if push back only
	bool operator>=(const iterator &it)const{ return p >= it.p; }//use only if push back only
	bool operator<=(const iterator &it)const{ return p <= it.p; }//use only if push back only
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

	//maxLen为允许push进的最大个数,超过一个则长度变为0,超过两个长度变为1,以此类推;不提供溢出检查...
	Queue(const int maxLen = 1000000) :maxLen(maxLen + 1){ data = (T *)malloc(sizeof(T)*(maxLen + 1)); }

	void push_back(const T &value){ data[_back] = value;  ++_back; UPCHECK(_back); }
	void push_front(const T &value){ --_front; DWCHECK(_front);  data[_front] = value; }

	void pop_front(){ ++_front; UPCHECK(_front); }
	void pop_back(){ --_back; DWCHECK(_back); }

	T front(){ return data[_front]; }
	T back(){ return data[_back == 0 ? maxLen - 1 : _back - 1]; }

	bool empty(){ return _front == _back; }
	void clear(){ _front = 0; _back = 0; }
	int size(){ int len = _back - _front; return len >= 0 ? len : len + maxLen; }
	void resize(const int maxLen){ if (data)delete[]data; clear(); this->maxLen = maxLen; }

	iterator begin(){ return iterator(&data[_front], data - 1, &data[maxLen]); }
	iterator end(){ return iterator(&data[_back], data - 1, &data[maxLen]); }

	T &operator[](int idx){ idx += _front; UPCHECK(idx); return data[idx]; }
	//Queue operator=(const Queue &q){}
	//Queue operator=(const Queue &&q){}

	~Queue(){ if (data)delete[] data; }

private:
	T *data;
	int _front = 0, _back = 0;
	int maxLen;//总长度

#undef UPCHECK
#undef DWCHECK
};

class BigNumber{
public:
	BigNumber(int maxLen){ q = new Queue<int>(maxLen); }
	BigNumber(string num){ q = new Queue<int>(num.size() + 10); assign(num); }

	void assign(string num){
		int h = num.size() / 4 + 1; int e; int idx = num.size();
		while (h--){
			e = 0;
			for (int i = 0; i < 4 && idx > 0; ++i){
				e += (num[--idx] - '0')*(pow(10, i));
			}
			q->push_back(e);
		}
	}

	BigNumber operator+(const ll num){}
	BigNumber operator-(const ll num){}
	BigNumber operator+(const BigNumber &num){}
	BigNumber operator-(const BigNumber &num){}


	BigNumber &operator+=(const ll num){
	}
	BigNumber &operator-=(const ll num){}
	BigNumber &operator+=(const BigNumber &num){
		int carry = 0; Queue<int>::iterator it1, it2, end1, end2;

		for (int i = num.q->size() - q->size() + 1; i > 0; --i){ q->push_back(0); }

		it1 = q->begin(); it2 = num.q->begin();
		end1 = q->end(); end2 = num.q->end();
		for (; it1 != end1; ++it1, ++it2){
			*it1 += it2 < end2 ? *it2 : 0 + carry;
			carry = *it1 / 10000;
			*it1 %= 10000;
		}
		if (q->back() == 0)q->pop_back();


		return *this;
	}
	BigNumber &operator-=(const BigNumber &num){}

	string ToString(){
		Queue<int>::iterator it, begin; begin = q->begin(); char *ret = new char[q->size() * 4 + 1]; int idx = 0;
		for (it = q->end() - 1; it != begin - 1; --it){
			sprintf(ret + (idx++) * 4, "%04d", *it);
		}
		int zeron = 0, len = strlen(ret); for (int i = 0; i < len - 2; ++i){ if (ret[i] == '0')++zeron; else break; }
		string _ret; _ret.assign(ret + zeron, ret + q->size() * 4 + 1); delete[] ret;
		return _ret;
	}

	~BigNumber(){ if (q)delete q; }

private:
	Queue<int>*q;
};


int main(){
	BigNumber bn(1000);
	bn.assign("10382");
	bn += (string)"123456700054616565";

	cout << bn.ToString() << endl;

	return 0;
}