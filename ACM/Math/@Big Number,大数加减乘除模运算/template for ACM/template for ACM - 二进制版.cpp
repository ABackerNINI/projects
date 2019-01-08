//Template for ACM

#define LL long long
#define INF 0x7FFFFFFF7FFFFFFF

#include <stack>
#include <cmath>
#include <deque>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class BigInt {
#define DATATYPEOFEACH		int			//每个数据的类型
#define MAXDIGITOFEACH		28			//每个数据的位数,留一位作进位,至少留4位!,应大于等于4
#define MAXNUMOFEACH		0xfffffff	//每个数据能表示的最大数,至少为10	15
	
#define	DEBUG 0x0
#define	DEBUG_PRINT 0x1					//输出每个数据
#define DEBUG_THROW 0x10				//抛出错误

public:
	BigInt() {}

	//用于assign(const string &num);
	BigInt(const unsigned short &num) {
		assign(num);
	}
	BigInt(const string &num) {
		assign(num);
	}

	void assign(const string &num) {
		data.clear(); data.push_back(0); isPos = true;

		unsigned int s = 0;
		if (num[0] == '-')++s;
		for (; s < num.size(); ++s) {
			this->ASSIGN_MUL10();
			this->ADD(BigInt((unsigned short)(num[s] - '0')));
		}

		if (num[0] == '-') this->NEG();
	}
	void assign(const unsigned short &num) {
		data.clear(); data.push_back((DATATYPEOFEACH)num); isPos = true;
	}

	bool operator<(const BigInt &_Left) {
		if (isPos == _Left.isPos)return (abs_Equ(_Left) < 0) == isPos;
		else return !isPos;
	}

	BigInt &operator<<=(unsigned int _Left) {
		if (_Left == 0)return *this;

		unsigned int d = _Left / MAXDIGITOFEACH;
		while (d--) {
			data.push_front(0);
		}

		_Left %= MAXDIGITOFEACH;

		data.push_back(0);

		for (unsigned int i = data.size() - 1; i > 0; --i) {
			data[i] <<= _Left; data[i] |= (data[i - 1] >> (MAXDIGITOFEACH - _Left));
		}
		data[0] <<= _Left;

		if (data.back() == 0)data.pop_back();

		clear_carry();

		return *this;
	}

	BigInt &operator+=(const BigInt &_Left) {
		this->ADD(_Left);

		return *this;
	}
	BigInt &operator-=(const BigInt &_Left) {
		BigInt tmp = _Left; 
		
		tmp.isPos ? tmp.NEG() : tmp.POS();

		this->ADD(tmp);

		return *this;
	}
	BigInt &operator*=(const BigInt &_Left) {
		bool res = _Left.isPos ? isPos : !isPos;

		if (!isPos) this->POS();
		if (_Left.isPos)MUL(_Left);
		else MUL(_Left.abs());

		if (!res)this->NEG();

		return *this;
	}
	BigInt &operator/=(const BigInt &_Left) {

	}

	BigInt operator+(const BigInt &_Left) {
		BigInt tmp = *this;
		tmp += _Left;

		return tmp;
	}
	BigInt operator-(const BigInt &_Left) {
		BigInt tmp = *this;
		tmp -= _Left;

		return tmp;
	}
	BigInt operator*(const BigInt &_Left) {
		BigInt tmp = *this;
		tmp *= _Left;

		return tmp;
	}

	void Print(bool isNewLine = false) {
		BigInt tmp = *this;
		stack<short>stack;

		if (!isPos) {
			printf("-");
			tmp.POS();
		}

		short remain;
		while (remain = tmp.PRINT_DIV10(), remain > -1) {
			stack.push(remain);//printf("%d", remain);
		}

		if (stack.empty())printf("0");
		else {
			while (!stack.empty()) {
				printf("%d", stack.top());
				stack.pop();
			}
		}

#if(DEBUG&DEBUG_PRINT)
		int val = 0; printf("(");
		for (int k = data.size() - 1; k > -1; --k) {
			printf("[%d]", data[k]);
			for (int i = 3; i > -1; --i) {
				printf(data[k] & (1 << i) ? "1" : "0");
				if (data[k] & (1 << i))val |= (1 << ((k << 2) + i));
			}
		}
		if (!isPos) {
			for (int i = 4 * data.size(); i < 32; ++i) {
				val |= (1 << i);
			}
		}
		printf(")%d", val);

#endif;

		if (isNewLine)printf("\n");
	}

	BigInt abs() const {
		BigInt tmp = *this;
		if (!isPos)tmp.POS();

		return tmp;
	}

private:
	deque<DATATYPEOFEACH>data; bool isPos;

	//要求:正数
	void ASSIGN_MUL10() {
		BigInt tmp = *this;
		*this <<= 3;
		this->ADD(tmp <<= 1);
	}

	//要求:正数
	//除以10并返回余数
	//返回负数表示商已为0，其中负数的绝对值为余数
	short PRINT_DIV10() {
		if (data.size() == 1 && data[0] == 0)return -1;

		DATATYPEOFEACH remain = 0;

		for (int i = data.size() - 1; i > -1; --i) {
			data[i] += (remain << MAXDIGITOFEACH);//留4位的原因
			remain = data[i] % 10;
			data[i] /= 10;
		}

		pop_back_zero();

		return (short)remain;
	}
	void ADD(const BigInt &_Left) {
		//补短,将被加数补到与加数位数一致
		if (this->data.size() < _Left.data.size()) {
			unsigned int delta = _Left.data.size() - data.size();
			DATATYPEOFEACH e = isPos ? 0 : MAXNUMOFEACH;

			while (delta--)data.push_back(e);
		}

		//加加数
		data[0] += _Left.data[0];
		for (unsigned int i = 1; i < _Left.data.size(); ++i) {
			data[i] += data[i - 1] >> MAXDIGITOFEACH;//进位
			data[i] += _Left.data[i];
		}

		//加被加数比加数长的部分,因为负数前要补MAXNUMOFEACH
		if (!_Left.isPos) {
			for (unsigned int i = _Left.data.size(); i < data.size(); ++i) {
				data[i] += data[i - 1] >> MAXDIGITOFEACH;//进位
				data[i] += MAXNUMOFEACH;
			}
		}

		if (isPos == _Left.isPos) {//进最高位
			if (data.size() == _Left.data.size()) {
				if (data.back() >> MAXDIGITOFEACH) {
					if (isPos) data.push_back((DATATYPEOFEACH)1);
				}
			}
			else /*if(data.size() > _Left.data.size())*/ {
				data[_Left.data.size()] += data[_Left.data.size() - 1] >> MAXDIGITOFEACH ? 1 : 0;
			}
		}
		else {//变号
			if (isPos) {
				if (data.back() >> MAXDIGITOFEACH == 0)isPos = false;
			}
			else {
				if (data.back() >> MAXDIGITOFEACH) isPos = true;
			}
		}

		clear_carry();

		if (isPos)pop_back_zero();
		else pop_back_max();
	}

	//要求:都为正数
	void MUL(const BigInt &_Left) {
		BigInt tmp, _tmp = *this;
		this->assign((unsigned short)0);
		for (unsigned int i = 0; i < _Left.data.size(); ++i) {
			tmp = _tmp;

			tmp.MUL(_Left.data[i]);
			this->ADD(tmp);

			_tmp <<= MAXDIGITOFEACH;
		}
	}
	void MUL(const DATATYPEOFEACH &_Left) {
		unsigned int k = 0; BigInt tmp = *this;
		this->assign((unsigned short)0);
		for (unsigned int i = 0; i < MAXDIGITOFEACH; ++i) {
			if (_Left&(1 << i)) {
				*this += (tmp <<= (i - k));
				k = i;
			}
		}
	}

	//要求:正数
	int  abs_Equ(const BigInt &_Left) {
		if (data.size() != _Left.data.size())return data.size() - _Left.data.size();
		else {
			for (unsigned int i = data.size() - 1; i >-1; --i) {
				if (data[i] != _Left.data[i])return data[i] - _Left.data[i];
			}
			return 0;
		}
	}

	void NEG_ADD1() {
		unsigned int i;
		for (i = 0; i < data.size() && data[i] == MAXNUMOFEACH; ++i) {
			data[i] = 0;
		}
		if (i < data.size())data[i] += 1;
	}
	void POS_SUB1() {
		unsigned int i;
		for (i = 0; i < data.size() && data[i] == 0; ++i) {
			data[i] = MAXNUMOFEACH;
		}
		if (i < data.size())data[i] -= 1;
	}

	void NEG() {
#if(DEBUG&DEBUG_THROW)
		if (!isPos)throw exception("ERROR:void NEG()");
#endif;

		for (unsigned int i = 0; i < data.size(); ++i) {
			data[i] = ~data[i]; data[i] &= MAXNUMOFEACH;
		}
		NEG_ADD1();

		isPos = false;
	}
	void POS() {
#if(DEBUG&DEBUG_THROW)
		if (isPos)throw exception("ERROR:void POS()");
#endif;

		POS_SUB1();
		for (unsigned int i = 0; i < data.size(); ++i) {
			data[i] = ~data[i]; data[i] &= MAXNUMOFEACH;
		}

		isPos = true;
	}

	//要求:正数
	void pop_back_zero() {
#if(DEBUG&DEBUG_THROW)
		if (!isPos)throw exception("ERROR:void pop_back_zero()");
#endif;

		while (data.size()>1 && data.back() == 0)data.pop_back();
	}
	//要求:负数
	void pop_back_max() {
#if(DEBUG&DEBUG_THROW)
		if (isPos)throw exception("ERROR:void pop_back_max()");
#endif;

		while (data.size() > 1 && data.back() == MAXNUMOFEACH)data.pop_back();
	}
	void clear_carry() {
		for (unsigned int i = 0; i < data.size(); ++i) {
			data[i] &= MAXNUMOFEACH;
		}
	}
};

//初始化测试
void test_1() {
	string num;//int,LL
	BigInt bi;
	while (cin >> num) {
		bi.assign(num);
		//bi.Print(true);
	}
}

//+ - * /运算符测试
void test_2() {
	string num1, num2;
	BigInt a, b, c;
	while (cin >> num1 >> num2) {
		a.assign(num1); b.assign(num2);
		a += b; a.Print();
		//a.Print(); printf(" + ");  b.Print(); printf(" = "); c = a + b; c.Print(true);
		//a.Print(); printf(" - ");  b.Print(); printf(" = "); c = a - b; c.Print(true);
		//a.Print(); printf(" * ");  b.Print(); printf(" = "); c = a * b; c.Print(true);
		//a.Print(); printf(" / ");  b.Print(); printf(" = "); if (b == (BigInt)0)printf("INF\n"); else { c = a / b; c.Print(true); }
	}
}

/*
char n1[100000 + 5], n2[100000 + 5];

void test_3() {
	BigInt a, b, c;
	while (cin >> n1 >> n2) {
		a.assign(n1); b.assign(n2);
		a.div(b, &c); a.Print(true); c.Print(true);
	}
}*/

int main(){
	test_2();

	return 0;
}

/*
17 -16
-16 17
-17 16
16 -17

40 45
50 70
160 170
-3892 2121
567 9932
*/