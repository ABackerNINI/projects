//Template for ACM

#define LL long long
#define INF 0x7FFFFFFF7FFFFFFF

#include <list>
#include <cmath>
#include <deque>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class BigInt {
#define RADIX			10
#define DIGITOFGROUP	9
#define BASE			1000000000
#define DATATYPE		int
#define OUTFORMAT_0		"%d"
#define OUTFORMAT_1		"%09d"

public:
	BigInt() {}
	BigInt(const int &num) {
		assign(num);
	}
	BigInt(const string &num) {
		assign(num.c_str());
	}
	BigInt(const char *num) {
		assign(num);
	}

	void assign(long long num) {
		data.clear();
		sign = (num < 0 ? -1 : num == 0 ? 0 : 1);

		for (num = abs(num); num>0; num /= BASE)data.push_back((DATATYPE)(num%BASE));
	}
	void assign(const string &num) {
		assign(num.c_str());
	}
	void assign(const char *num) {
		data.clear();

		if (*num == '-') {
			sign = -1;
			++num;
		}
		else sign = 1;

		int len = strlen(num), size;
		int firstGroupLen = len%DIGITOFGROUP;
		if (firstGroupLen == 0) { firstGroupLen = DIGITOFGROUP; size = len / DIGITOFGROUP; }
		else size = len / DIGITOFGROUP + 1;

		data.push_back(parseInt(num, firstGroupLen));
		num += firstGroupLen;

		for (int i = size - 2; i > -1; --i) {
			data.push_front(parseInt(num, DIGITOFGROUP));
			num += DIGITOFGROUP;
		}
	}

	BigInt &operator+=(const BigInt &_Right) {
		if (this->abs_equ(_Right) == -1) {
			BigInt tmp = _Right;
			if (sign*tmp.sign == -1)tmp.abs_sub(*this);
			else tmp.abs_add(*this);

			*this = ::move(tmp);
		}
		else {
			if (sign*_Right.sign == -1)this->abs_sub(_Right);
			else this->abs_add(_Right);
		}

		return *this;
	}
	BigInt &operator-=(const BigInt &_Right) {
		if (this->abs_equ(_Right) == -1) {
			BigInt tmp = _Right;
			if (sign*tmp.sign == -1)tmp.abs_add(*this);
			else tmp.abs_sub(*this);

			*this = ::move(tmp);
		}
		else {
			if (sign*_Right.sign == -1)this->abs_add(_Right);
			else this->abs_sub(_Right);
		}

		return *this;
	}
	BigInt &operator*=(const BigInt &_Right) {
		*this = *this*_Right;

		return *this;
	}

	BigInt operator+(const BigInt &_Right) {
		BigInt tmp = *this;
		tmp += _Right;

		return tmp;
	}
	BigInt operator-(const BigInt &_Right) {
		BigInt tmp = *this;
		tmp -= _Right;

		return tmp;
	}
	BigInt operator*(const BigInt &_Right) {
		BigInt result = 0;
		result.sign = sign*_Right.sign;
		result.data.resize(data.size() + _Right.data.size());

		long long product;
		for (int i = data.size() - 1; i > -1; --i) {
			for (int j = _Right.data.size() - 1; j > -1; --j) {
				product = (long long)data[i] * _Right.data[j];
				result.data[i + j] += (DATATYPE)(product%BASE);
				result.carry_up(i + j);
				result.data[i + j + 1] += (DATATYPE)(product / BASE);
				result.carry_up(i + j + 1);
			}
		}

		result.shrink();
		return result;
	}

	void print(bool isNewLine = false) const {
		if (sign == 0)  printf("0");
		else {
			if (sign == -1)printf("-");
			deque<DATATYPE>::const_reverse_iterator it = data.rbegin();

			printf(OUTFORMAT_0, *it);
			for (++it; it != data.rend(); ++it)printf(OUTFORMAT_1, *it);
		}
		if (isNewLine)printf("\n");
	}

	~BigInt() {

	}

private:
	int sign; deque<DATATYPE>data;

	void abs_add(const BigInt &_Right) {
		for (int i = 0; i < _Right.data.size(); ++i) {
			data[i] += _Right.data[i];
			carry_up(i);
		}
	}
	void abs_sub(const BigInt &_Right) {
		for (int i = 0; i < _Right.data.size(); ++i) {
			data[i] -= _Right.data[i];
			carry_down(i);
		}
		shrink();
	}

	//void abs_div(const BigInt &_Right) {

	//}
	int  abs_equ(const BigInt &_Right) const {
		if (data.size() != _Right.data.size())return data.size() < _Right.data.size() ? -1 : 1;

		for (int i = data.size() - 1; i>-1; --i) {
			if (data[i] != _Right.data[i])return data[i] < _Right.data[i] ? -1 : 1;
		}
		return 0;
	}

	void carry_up(int n) {
		for (; data[n] >= BASE; ++n) {
			if (n == data.size() - 1) data.push_back(data[n] / BASE);
			else data[n + 1] += data[n] / BASE;
			data[n] %= BASE;
		}
	}
	void carry_down(int n) {
		for (; data[n] < 0; ++n) {
			data[n + 1]--;
			data[n] += BASE;
		}
		shrink();
	}
	void shrink() {
		for (int i = data.size() - 1; i > -1 && data[i] == 0; --i)data.pop_back();
		if (data.size() == 0)sign = 0;
	}

	int parseInt(const char *num, int n) {
		int ret = 0;
		while (n--) {
			ret *= 10;
			ret += *(num++) - '0';
		}

		return ret;
	}
};

//³õÊ¼»¯²âÊÔ
void test_1() {
	string s;BigInt num;
	while (1) {
		cin >> s;
		num.assign(s);
		num.print(true);
	}
}

//+ - * / ²âÊÔ
void test_2() {
	string s1, s2; BigInt a, b, c;
	while (1) {
		cin >> s1 >> s2;
		a.assign(s1); b.assign(s2);
		c = a + b; c.print(true);
		c = a - b; c.print(true);
		c = a*b; c.print(true);
	}
}

int main(){
	test_2();

	return 0;
}//22222222222222211111111 1222222222222222222