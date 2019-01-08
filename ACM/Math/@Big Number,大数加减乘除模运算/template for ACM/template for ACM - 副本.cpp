//Template for ACM

#define ll long long
#define INF 0x7FFFFFFF
#define LINF 0x7FFFFFFFFFFFFFFF

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

class BigNumber{
public:
	BigNumber(int len = 1000):len(len){
		data = new ll[len];
	}
	BigNumber(string num){
		len = num.size() + 100;
		data = new ll[len];
	}
	void assign(string num){
		string::iterator it = num.begin();
		for (; it != num.end(); ++it){
			
		}
	}

private:
	ll *data;
	int len;
};

class BigNum{
public:
	string num;
	BigNum(string num){
		this->num.resize(num.size() + 100);
		this->num.assign(num.begin(), num.end());
	}
	BigNum operator+(BigNum &num){
	
	}
};

int main(){
	if (true)printf("false");

	return 0;
}