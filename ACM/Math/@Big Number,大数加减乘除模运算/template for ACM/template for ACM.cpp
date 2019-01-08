#pragma once

#include <list>
#include <cmath>
#include <deque>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class BigInt {
#define BASE			1000000000			//RADIX
#define BASELEN					 9
#define DATATYPE			   int
#define OUTFORMAT_0			  "%d"
#define OUTFORMAT_1			"%09d"

public:
	BigInt() {}
	BigInt(const long long &num) {
		assign(num);
	}
	explicit BigInt(const string &num) {
		assign(num.c_str());
	}
	explicit BigInt(const char *num) {
		assign(num);
	}
	BigInt(BigInt &&num) {
		assign(std::move(num));
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
		int firstGroupLen = len%BASELEN;
		if (firstGroupLen == 0) { firstGroupLen = BASELEN; size = len / BASELEN; }
		else size = len / BASELEN + 1;

		data.push_back(parseNum(num, firstGroupLen));
		num += firstGroupLen;

		for (int i = size - 2; i > -1; --i) {
			data.push_front(parseNum(num, BASELEN));
			num += BASELEN;
		}
	}
	void assign(BigInt &&num) {
		sign = num.sign;
		data.swap(num.data);
	}

	BigInt &operator=(const char *num) {
		assign(num);

		return *this;
	}
	BigInt &operator=(const string &num) {
		assign(num);

		return *this;
	}
	BigInt &operator=(const long long &num) {
		assign(num);

		return *this;
	}
	BigInt &operator=(BigInt &&num) {
		assign(std::move(num));

		return *this;
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
		*this = (*this*_Right);

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
	string toString() const {
		string buf;
		if (sign == 0)buf.append("0");
		else {
			if (sign == -1)buf.append("-");
			deque<DATATYPE>::const_reverse_iterator it = data.rbegin();

			buf.append(to_string(*it));
			for (++it; it != data.rend(); ++it)buf.append(toString(*it));
		}

		return buf;
	}
	void swap(BigInt &_Right) {
		std::swap(sign, _Right.sign);
		data.swap(_Right.data);
	}

	//the same with *this*=(BASE*n),but faster
	BigInt &_leftShift(unsigned int n) {
		for (unsigned int i = 0; i < n; ++i)data.push_front(0);

		return *this;
	}
	//the same with *this/=(BASE*n),but faster
	BigInt &_rightShift(unsigned int n) {
		if (data.size() <= n) {
			data.clear(); sign = 0;
		}
		else for (unsigned int i = 0; i < n; ++i)data.pop_front();

		return *this;
	}
	//remainder's sign will be the same with the sign of the dividend
	BigInt &_divRem(const BigInt &Divisor, BigInt *Remainder) {
		abs_div(Divisor, Remainder);

		return *this;
	}

	~BigInt() {

	}
private:
	int sign; deque<DATATYPE>data;
	friend class BigDec;

	int  abs_equ(const BigInt &_Right) const {
		if (data.size() != _Right.data.size())return data.size() < _Right.data.size() ? -1 : 1;

		for (int i = data.size() - 1; i>-1; --i) {
			if (data[i] != _Right.data[i])return data[i] < _Right.data[i] ? -1 : 1;
		}
		return 0;
	}
	void abs_add(const BigInt &_Right) {
		for (unsigned int i = 0; i < _Right.data.size(); ++i) {
			data[i] += _Right.data[i];
			carry_up(i);
		}
	}
	void abs_sub(const BigInt &_Right) {
		for (unsigned int i = 0; i < _Right.data.size(); ++i) {
			data[i] -= _Right.data[i];
			carry_down(i);
		}
		shrink();
	}
	void abs_div(const BigInt &_Right, BigInt *_Remainder = NULL) {
		if (_Right.sign == 0)throw exception("Error:divison by zero!");
		if (abs_equ(_Right) < 0) {
			if (_Remainder != NULL)  *_Remainder = *this;
			*this = 0LL;
			return;
		}
		
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

	DATATYPE parseNum(const char *num, int n) {
		DATATYPE ret = 0;
		while (n--) {
			ret *= 10;
			ret += *(num++) - '0';
		}

		return ret;
	}
	string toString(DATATYPE num) const {
		char buf[10];
		sprintf(buf, OUTFORMAT_1, num);

		return (string)buf;
	}
};

class BigDec {
public:
	BigDec() {}
	BigDec(const char *num) {}
	BigDec(const string &num) {
		assign(num);
	}
	BigDec(const BigInt &num,unsigned int point) {
		assign(num, point);
	}

	void assign(const char *num) {
		
	}
	void assign(const string &num) {}
	void assign(const BigDec &num) {}
	void assign(BigDec &&num) {
		swap(num);
	}
	void assign(const BigInt &num, unsigned int point = 0) {
		data = num; this->point = point;
	}
	void assign(BigInt &&num, unsigned int point = 0) {
		data.swap(num); this->point = point;
	}

	void print(bool isNewLine = false) const {
		string s = data.toString();

		printf("%s.%s", s.substr(0, s.size() - point).c_str(), s.substr(s.size() - point, s.size()).c_str());

		if (isNewLine)printf("\n");
	}
	void toString() const {
		
	}
	void swap(BigDec &num) {
		std::swap(point, num.point);
		data.swap(num.data);
	}

private:
	BigInt data; unsigned int point;
};

//BigInt≥ı ºªØ≤‚ ‘
void test_1() {
	string s; BigInt num;
	while (1) {
		cin >> s;
		num.assign(s);
		num.print(true);
	}
}

//BigInt+ - * / ≤‚ ‘
void test_2() {
	string s1, s2; BigInt a, b, c;
	while (1) {
		cin >> s1 >> s2;
		a.assign(s1); b.assign(s2);
		c = a + b; c.print(true);
		c = a - b; c.print(true);
		c = a*b;   c.print(true);
	}
}

//BigDec≥ı ºªØ≤‚ ‘
void test_3() {
	BigInt bigint("1234567890");
	BigDec num(bigint, 5);
	num.print();
}

int main() {
	//test_3();

	return 0;
}

/*
22222222222222211111111 1222222222222222222
*/