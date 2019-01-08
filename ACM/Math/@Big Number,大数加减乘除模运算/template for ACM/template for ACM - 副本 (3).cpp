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

class BigNum{
#define MAXOFEACH 10000

public:
	//BigNum(){}
	//n为数在10进制下的位数
	BigNum(int n){ malloc(n);orderd = true; }
	BigNum(const BigNum &num){ *this = num; }
	BigNum(BigNum &&num) :data(NULL){ *this =  std::move(num); }

	void assign(ll num){//O(1)
		clear();
		if (num < 0){
			isPos = false; num = -num;
		}
		else isPos = true;

		fitting(6);

		data[0] = num; orderd = false;
	}
	void assign(const string &num){//O(N)
		clear();
		int bound1, bound2, idx = num.size(); ll each;

		if (num.front() == '-'){ isPos = false; bound1 = (num.size() - 1) / 4 + 1; bound2 = 1; }
		else { isPos = true; bound1 = num.size() / 4 + 1;  bound2 = 0; }

		fitting(bound1 + 5);

		for (int i = 0; i < bound1; ++i){
			each = 0;
			for (int j = 0; j < 4 && idx > bound2; ++j){
				each += (num[--idx] - '0')*((ll)pow(10, j));
			}
			data[i] = each;
		}
		orderd = true;
	}

	BigNum &operator=(ll num){
		assign(num);return *this;
	}
	BigNum &operator=(const BigNum &num){//O(N)
		if (this != &num){
			malloc((num.maxLen - 2) << 2); isPos = num.isPos; orderd = num.orderd;
			memcpy(data, num.data, sizeof(ll)*maxLen);
		}
		return *this;
	}
	BigNum &operator=(BigNum &&num){//O(1)
		if (this != &num){
			std::swap(data, num.data);
			maxLen = num.maxLen; isPos = num.isPos; orderd = num.orderd;
		}
		return *this;
	}

	BigNum &operator<<=(int n){
		int bound = getDigit();
		fitting(bound += n);
		for (int i = bound - 1; i >= 0; --i){
			data[i] = i < n ? 0 : data[i - n];
		}return *this;
	}
	BigNum &operator>>=(int n){
		int bound = getDigit() - n + 1;
		for (int i = 0; i < bound; ++i){
			data[i] = data[i + n];
		}return *this;
	}

	BigNum &operator++(){ 
		*this += 1;
		return *this; 
	}
	BigNum &operator--(){
		*this -= 1; 
		return *this; 
	}
	BigNum operator++(int){
		BigNum tmp = *this;
		*this += 1; 
		return tmp; 
	}
	BigNum operator--(int){
		BigNum tmp = *this;
		*this -= 1;
		return tmp;
	}

	BigNum &operator+=(ll num){//O(1)
		if ((isPos&&num >= 0) || (!isPos&&num < 0))data[0] += abs(num);
		else data[0] -= abs(num);
		orderd = false; return *this;
	}
	BigNum &operator-=(ll num){//O(1)
		if ((isPos&&num >= 0) || (!isPos&&num < 0))data[0] -= abs(num);
		else data[0] += abs(num);
		orderd = false; return *this;
	}
	BigNum &operator*=(ll num){//O(N)
		fitting(getDigit() + getDigit(num));
		if (num < 0){ isPos = !isPos; num = -num; }
		for (int i = 0; i < maxLen; ++i)data[i] *= num;

		orderd = false; return *this;
	}
	BigNum &operator/=(ll num){//O(N)
		if (num == 0)throw 0; arrange();
		if (num < 0){ isPos = !isPos; num = -num; }
		for (int i = maxLen - 1; i >= 0; --i){
			if (i>0)data[i - 1] += (data[i] % num) * 10000;
			data[i] /= num;
		}
		orderd = true; return *this;
	}
	BigNum &operator%=(ll num){}

	BigNum &operator+=(const BigNum &num){//O(N)
		fitting(num.maxLen);
		if (isPos^num.isPos)
			for (int i = 0; i < num.maxLen; ++i)
				data[i] -= num.data[i];
		else 
			for (int i = 0; i < num.maxLen; ++i)data[i] += num.data[i];
		orderd = false; return *this;
	}
	BigNum &operator-=(const BigNum &num){//O(N)
		fitting(num.maxLen);
		if (isPos^num.isPos)for (int i = 0; i < num.maxLen; ++i)data[i] += num.data[i];
		else for (int i = 0; i < num.maxLen; ++i)data[i] -= num.data[i];
		orderd = false; return *this;
	}
	BigNum &operator*=(BigNum &num){//O(k*N*M)
		int bound = num.getDigit();
		fitting(getDigit() + bound);
		if (!num.isPos)isPos = !isPos;

		BigNum tmp = *this;
		clear();

		for (int i = 0; i < bound; ++i){
			*this += tmp*num.data[i];
			tmp *= 10000;
		}

		arrange(); return *this;
	}
	BigNum &operator/=(BigNum &num){
		int bound1 = getDigit(), bound2 = num.getDigit();
		if (bound2 == 1 && num.data[0] == 0)throw 0;
		if (bound1 < bound2)*this = 0;
		
		BigNum ans((maxLen - 2) << 2);
		BigNum tmp = num, _ans(bound1 - bound2 + 5);
		_ans = 1; int i = 0;
		for (; i < bound1 - bound2 + 2; ++i){
			tmp <<= 1; _ans <<= 1;
		}

		ans = 0; bool p = isPos;
		for (; i >= 0; --i){
			while (1){
				*this -= tmp; //print();
				if (arrange(), isPos == p){
					ans += _ans;
				}
				else {
					*this += tmp;
					tmp >>= 1;
					_ans >>= 1;
					break;
				}
			}
		}

		if (p ^ num.isPos)ans.isPos = false;
		else ans.isPos = true;

		*this = std::move(ans);
		return *this;
	}
	BigNum &operator%=(BigNum &num){}

	BigNum getLastReminder(){}

	//尽量少使用以下5个函数
	template<typename T>BigNum operator+(T &num)const{
		BigNum tmp = *this;
		tmp += num;
		return tmp;
	}
	template<typename T>BigNum operator-(T &num)const{
		BigNum tmp = *this;
		tmp -= num;
		return tmp;
	}
	template<typename T>BigNum operator*(T &num)const{
		BigNum tmp = *this;
		tmp *= num;
		return tmp;
	}
	template<typename T>BigNum operator/(T &num)const{
		BigNum tmp = *this;
		tmp /= num;
		return tmp;
	}
	template<typename T>BigNum operator%(T &num)const{
		BigNum tmp = *this;
		tmp %= num;
		return tmp;
	}

	void print(bool nextLine = true){//O(N)
		arrange();
		if (!isPos)putchar('-');
		for (int i = maxLen - 1; i >= 0; --i){
			if (data[i] != 0){
				printf("%d", data[i]);
				for (int j = i - 1; j >= 0; --j){
					printf("%04I64d", data[j]);
				}if (nextLine)putchar('\n'); return;
			}
		}
		printf("0");
		if (nextLine)putchar('\n');
	}
	void debug(int n = 10){//O(N)
		for (int i = 0; i < n; ++i)printf("%I64d\n", data[i]);
		printf("\n");
	}

	string ToString(){}

	~BigNum(){ if (data)delete[]data; }
private:
	ll *data;//data为数据数组
	int maxLen;//maxLen=n/4+2,即10000进制下的位数
	bool isPos, orderd;	//isPos在orderd=true的情况下表示该数是否为正数		orderd表示该数是否整理为标准10000进制

	void arrange(){//O(N)
		if (orderd)return;
		ll carry = 0;

		for (int k = maxLen - 1; k >= 0; --k){
			if (data[k] != 0){
				bool flag;
				for (int i = 0; i <= k || flag; ++i){
					flag = false;
					data[i] += carry;
					carry = data[i] / 10000;
					if (carry != 0)flag = true;

					data[i] %= 10000;
					if (data[i] < 0 && (i<k||flag)){
						data[i] += 10000;
						--carry;
					}
				}
			}
		}

		for (int k = maxLen - 1; k >= 0; --k){
			if (data[k] != 0){
				if (data[k] < 0){//变号
					isPos = !isPos; 
					for (int j = 0; j < maxLen; ++j)data[j] = -data[j]; 
					
					arrange();
				}
				orderd = true; return;
			}
		}
		isPos = true; orderd = true;
	}
	void clear(){
		for (int i = 0; i < maxLen; ++i)data[i] = 0;
	}
	int getDigit(){//O(N)
		int i; arrange();
		for (i = maxLen - 1; i >= 0; --i){
			if (data[i] != 0)break;
		}
		return i + 1;
	}
	template<typename T>int getDigit(T num){//O(N)
		int i = 0;
		while (num > 0){
			num /= 10; ++i;
		}
		return (i >> 2) + 2;
	}
	void fitting(int maxLen){//O(N)
		if (maxLen > this->maxLen){
			ll *_data = new ll[maxLen]; 
			for (int i = 0; i < maxLen; ++i)_data[i] = 0;
			memcpy(_data, data, sizeof(ll)*this->maxLen);
			delete[]data; data = _data;
			this->maxLen = maxLen;
		}
	}
	void malloc(int n){//O(N)
		maxLen = (n >> 2) + 2;
		data = new ll[maxLen];
	}
};

int main(){
	BigNum bn(100+5), bn1(100+5),bn2(1); string s, s1; cin >> s >> s1;
	bn.assign(s); bn1.assign(s1); bn2 = bn;

	bn /= bn1; bn.print();
	bn2 -= bn*bn1; bn2.print();

	return 0;
}