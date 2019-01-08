//Template for ACM

#define LL long long
#define INF 0x7FFFFFFF7FFFFFFF

#include <cmath>
#include <deque>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class BigInt {
#define DATATYPEOFEACH int
#define MAXDIGITOFEACH 30
#define MAXNUMOFEACH 0x3fffffff

public:
	BigInt() {}
	BigInt(const string &num) {
		
	}

	void assign(const string &num) {
		
	}

	bool operator<(const BigInt &_Left) {
		if (isPos == _Left.isPos)return (abs_Equ(_Left) < 0) == isPos;
		else return !isPos;
	}

	BigInt &operator<<=(unsigned int _Left) {
		unsigned int d = _Left / MAXDIGITOFEACH;
		while (d--) {
			data.push_back(0);
		}

		_Left %= MAXDIGITOFEACH;

		data.push_front(0);

		for (unsigned int i = 0; i < data.size() - 1; ++i) {
			data[i] >>= _Left; data[i] <<= (_Left << 1); data[i] |= data[i + 1] >> (MAXDIGITOFEACH - _Left);
		}

		if (data.front() == 0)data.pop_front();

		return *this;
	}

	BigInt &operator+=(const BigInt &_Left) {
		
	}

	BigInt &operator*=(int _Left) {
		
	}

	void Print(bool isNewLine = true) {
		
	}

private:
	deque<DATATYPEOFEACH>data; bool isPos;

	//要求:正数
	void abs_MUL10() {
		BigInt tmp = *this;
		*this <<= 3;
		*this += (tmp <<= 1);
	}
	void abs_ADD(const BigInt &_Left) {
		BigInt *a, tmp;
		const BigInt *b;

		if (*this<_Left) {
			tmp = _Left;
			a = &tmp; b = this;
		}
		else {
			a = this; b = &_Left;
		}

		a->data[b->data.size() - 1] += b->data[b->data.size() - 1];

		for (unsigned int i = b->data.size() - 2; i>-1; --i) {
			tmp.data[i] += data[i] + data[i - 1] >> MAXDIGITOFEACH;
			data[i - 1] &= MAXNUMOFEACH;
		}
	}

	void abs_ADD1() {
		unsigned int i;
		for (i = data.size() - 1; i > -1 && data[i] == MAXNUMOFEACH; --i) {
			data[i] = 0;
		}
		if (i > -1)data[i] += 1;
		else data.push_front(1);
	}
	void abs_SUB1() {
		unsigned int i;
		for (i = data.size() - 1; i > -1 && data[i] == 0; --i) {
			data[i] = MAXNUMOFEACH;
		}
		if (i > -1)data[i] -= 1;
	}
	int  abs_Equ(const BigInt &_Left) {
		if (data.size() != _Left.data.size())return data.size() - _Left.data.size();
		else {
			for (unsigned int i = 0; i < data.size(); ++i) {
				if (data[i] != _Left.data[i])return data[i] - _Left.data[i];
			}
			return 0;
		}
	}

	void NEG() {
		for (unsigned int i = 0; i < data.size(); ++i) {
			data[i] = ~data[i];
		}
		if (isPos) {
			this->abs_ADD1();
			isPos = false;
		}
		else {
			this->abs_SUB1();
			isPos = true;
		}
	}

	void pop_front_zero() {
		while (data.front() == 0)data.pop_front();
	}
};

//初始化测试
void test_1() {
	string num;//int,LL
	BigInt bi;
	while (cin >> num) {
		bi.assign(num);
		bi.Print(true);
	}
}

/*
//+ - * /运算符测试
void test_2() {
	string num1, num2;
	BigInt a, b, c;
	while (cin >> num1 >> num2) {
		a.assign(num1); b.assign(num2);
		a.Print(); printf(" + ");  b.Print(); printf(" = "); c = a + b; c.Print(true);
		a.Print(); printf(" - ");  b.Print(); printf(" = "); c = a - b; c.Print(true);
		a.Print(); printf(" * ");  b.Print(); printf(" = "); c = a * b; c.Print(true);
		a.Print(); printf(" / ");  b.Print(); printf(" = "); if (b == (BigInt)0)printf("INF\n"); else { c = a / b; c.Print(true); }
	}
}

char n1[100000 + 5], n2[100000 + 5];

void test_3() {
	BigInt a, b, c;
	while (cin >> n1 >> n2) {
		a.assign(n1); b.assign(n2);
		a.div(b, &c); a.Print(true); c.Print(true);
	}
}*/

int main(){
	test_1();

	return 0;
}