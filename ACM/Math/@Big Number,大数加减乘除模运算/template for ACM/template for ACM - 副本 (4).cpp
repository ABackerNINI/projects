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
#define MAXOFEACH 10000000000
#define DIGITOFEACH 10
#define OUT "%010I64d"

public:
	BigNum(){}
	BigNum(ll num){ *this = num; }
	BigNum(const BigNum &num){ *this = num; }
	BigNum(BigNum &&num){ *this = std::move(num); }

	void assign(ll num){//O(1)
		data.clear();
		if (num < 0){
			isPos = false; num = -num;
		}
		else isPos = true;
		while (num>0){
			data.push_back(num%MAXOFEACH);
			num /= MAXOFEACH;
		}
		orderd = true;
	}
	void assign(const string &num){//O(N)
		data.clear();
		int bound1, bound2, idx = num.size(); ll each;

		if (num.front() == '-'){ isPos = false; bound1 = (num.size() - 1) / DIGITOFEACH + 1; bound2 = 1; }
		else { isPos = true; bound1 = num.size() / DIGITOFEACH + 1;  bound2 = 0; }

		for (int i = 0; i < bound1; ++i){
			each = 0;
			for (int j = 0; j < DIGITOFEACH && idx > bound2; ++j){
				each += (num[--idx] - '0')*((ll)pow(10, j));
			}
			data.push_back(each);
		}
		orderd = true;
	}

	BigNum &operator=(ll num){//O(1)
		assign(num);return *this;
	}
	BigNum &operator=(const BigNum &num){//O(N)
		if (this != &num){
			data = num.data; isPos = num.isPos; orderd = num.orderd;
		}
		return *this;
	}
	BigNum &operator=(BigNum &&num){//O(1)
		if (this != &num){
			data = std::move(num.data); isPos = num.isPos; orderd = num.orderd;
		}
		return *this;
	}

	bool operator==(BigNum &num){//O(N)
		arrange(); num.arrange();
		if (isPos ^ num.isPos || data.size() != num.data.size())return false;

		for (int i = 0; i<data.size(); ++i){
			if (data[i] != num.data[i])return false;
		}return true;
	}
	bool operator>( BigNum &num){//O(N)
		arrange(); num.arrange();
		if (isPos&num.isPos){
			if (data.size() != num.data.size())
				return (data.size() > num.data.size()) & isPos;

			for (int i = 0; i < data.size(); ++i){
				if (data[i] != num.data[i])
					return (data[i] > num.data[i]) & isPos;
			}
			return false;
		}
		else return isPos;
	}
	bool operator<( BigNum &num){//O(N)
		return num>*this;
	}
	bool operator!=( BigNum &num){//O(N)
		return !(*this == num);
	}
	bool operator>=( BigNum &num){//O(N)
		return *this > num || *this == num;
	}
	bool operator<=( BigNum &num){//O(N)
		return *this < num || *this == num;
	}


	BigNum &operator<<=(int n){//O(N)
		int size = data.size();
		for (int i = n; i > 0; --i)data.push_back(size >= i ? data[size - i] : 0);

		for (int i = size - 1; i >= n; --i)data[i] = data[i - n];

		for (int i = n - 1; i >= 0; --i)data[i] = 0;

		return *this;
	}
	BigNum &operator>>=(int n){//O(N)
		for (int i = 0; i < data.size() - n; ++i)data[i] = data[i + n];

		while (n--)data.pop_back();

		return *this;
	}

	BigNum &operator*=(ll num){//O(N)
		if (num < 0){ isPos = !isPos; num = -num; }
		for (int i = 0; i < data.size(); ++i)data[i] *= num;

		arrange(); return *this;
	}
	BigNum &operator/=(ll num){//O(N)
		if (num == 0)throw 0;// arrange();
		if (num < 0){ isPos = !isPos; num = -num; }
		for (int i = data.size() - 1; i >= 0; --i){
			if (i>0)data[i - 1] += (data[i] % num) * MAXOFEACH;
			data[i] /= num;
		}
		arrange(); return *this;
	}

	BigNum &operator+=(const BigNum &num){//O(N)
		fit(num.data.size());

		int msize = min(data.size(), num.data.size());
		if (isPos&num.isPos)for (int i = 0; i < msize; ++i)data[i] += num.data[i];
		else for (int i = 0; i < msize; ++i)data[i] -= num.data[i];
		

		orderd = false; return *this;
	}
	BigNum &operator-=(const BigNum &num){//O(N)
		fit(num.data.size());

		int msize = min(data.size(), num.data.size());
		if (isPos&num.isPos)for (int i = 0; i < msize; ++i)data[i] -= num.data[i];
		else for (int i = 0; i < msize; ++i)data[i] += num.data[i];

		orderd = false; return *this;
	}
	BigNum &operator*=(BigNum &num){//O(k*N*M)
		num.arrange();
		if (!num.isPos)isPos = !isPos;

		BigNum tmp = *this;
		*this = 0;

		for (int i = 0; i < num.data.size(); ++i){
			*this += tmp*num.data[i];
			tmp <<= 1;
		}

		arrange(); return *this;
	}
	BigNum &operator/=(BigNum &num){
		num.arrange();
		if (!num.isPos)isPos = !isPos;

		BigNum tmp = num, ans = 0, _ans = 1;
		int dsize = data.size() - num.data.size();
		if (dsize > 0){ tmp <<= dsize; _ans <<= dsize; }
		dsize *= DIGITOFEACH;

		for (int i = 0; i<dsize; ++i){
			while (*this > tmp){
				*this -= tmp;
				ans += _ans;
				arrange();
				print();
			}
			tmp /= 10; _ans /= 10;
		}

		*this = std::move(ans);

		return *this;
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

	BigNum operator<<(int n){
		BigNum tmp = *this;
		return tmp <<= n;
	}
	BigNum operator>>(int n){
		BigNum tmp = *this;
		return tmp >>= n;
	}

	/*
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
	}*/

	void print(bool nextLine = true){//O(N)
		arrange();
		if (!isPos)putchar('-');
		for (int i = data.size() - 1; i >= 0; --i){
			if (data[i] != 0){
				printf("%I64d", data[i]);
				for (int j = i - 1; j >= 0; --j){
					printf(OUT, data[j]);
				}if (nextLine)putchar('\n'); return;
			}
		}
		printf("0");
		if (nextLine)putchar('\n');
	}
	void debug(int n = 10){//O(N)
		if (isPos)printf("正\n");
		else printf("负\n");

		for (int i = 0; i < n; ++i)printf("%I64d\n", data[i]);
		printf("\n");
	}

	string ToString(){}

private:
	bool isPos, orderd;
	vector<ll>data;

	void fit(int n){
		if (data.size() < n){
			int dsize = n - data.size();
			while (dsize--)data.push_back(0);
		}
	}
	void arrange(){//O(N)
		if (!orderd){
			ll carry = 0;
			for (int i = 0; i < data.size(); ++i){
				data[i] += carry;
				carry = data[i] / MAXOFEACH;
				data[i] %= MAXOFEACH;
				if (data[i] < 0){
					data[i] += MAXOFEACH;
					--carry;
				}
			}

			if (carry<0){
				isPos = !isPos; carry = -carry;
				for (int i = data.size() - 1; i >= 0; --i){
					data[i] = -data[i];
					data[i] += carry*MAXOFEACH;
					carry = data[i] % MAXOFEACH;
					data[i] /= MAXOFEACH;
				}
			}
			while (!data.empty() && data.back() == 0)data.pop_back();

			if (carry > 0)data.push_back(carry);
		}
		while (!data.empty() && data.back() == 0)data.pop_back();
	}
	template<typename T>int getDigit(T num){//O(N)
		int i = 0;
		while (num > 0){
			num /= 10; ++i;
		}
		return (i >> 2) + 2;
	}
};

int main(){
	BigNum bn1, bn2; string s1, s2;
	cin >> s1 >> s2;
	bn1.assign(s1); bn2.assign(s2); bn2.print();

	bn1 /= bn2; bn1.print();

	return 0;
}