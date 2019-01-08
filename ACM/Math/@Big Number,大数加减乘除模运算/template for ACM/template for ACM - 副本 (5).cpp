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

#define MAXOFEACH 10
#define DIGITOFEACH 1
#define TYPEOFEACH int
#define FMTOFEACH "%d"

public:
	BigInt() {}
	template<typename IntType>BigInt(IntType num) {
		this->assign(num);
	}
	BigInt(string &num) {
		this->assign(num);
	}
	BigInt(const BigInt &num) {
		this->assign(num);
	}
	BigInt(BigInt &&num) {
		this->assign(std::move(num));
	}

	template<typename IntType>BigInt &operator=(IntType num) {
		this->assign(num);

		return *this;
	}
	BigInt &operator=(string &num) {
		this->assign(num);

		return *this;
	}
	BigInt &operator=(const BigInt &num) {
		this->assign(num);

		return *this;
	}
	BigInt &operator=(BigInt &&num) {
		this->assign(std::move(num));

		return *this;
	}

	template<typename IntType>void assign(IntType num) {
		data.clear();
		if (num == 0) { isPos = true; data.push_back(0); return; }
		if (num < 0) { isPos = false; num = -num; }
		else isPos = true;

		while (num>0) {
			data.push_back(num%MAXOFEACH);
			num /= MAXOFEACH;
		}
	}
	void assign(char *num) {
		data.clear();
		int bound1, bound2, idx = strlen(num); TYPEOFEACH each;

		if (*num == '-') { isPos = false; bound1 = (idx - 1 + (DIGITOFEACH - 1)) / DIGITOFEACH; bound2 = 1; }
		else { isPos = true; bound1 = (idx + (DIGITOFEACH - 1)) / DIGITOFEACH;  bound2 = 0; }

		for (int i = 0; i < bound1; ++i) {
			each = 0;
			for (int j = 0; j < DIGITOFEACH && idx > bound2; ++j) {
				each += (num[--idx] - '0')*((TYPEOFEACH)pow(10, j));
			}
			data.push_back(each);
		}
	}
	void assign(string &num) {
		data.clear();
		int bound1, bound2, idx = num.size(); TYPEOFEACH each;

		if (num.front() == '-') { isPos = false; bound1 = (num.size() - 1 + (DIGITOFEACH - 1)) / DIGITOFEACH; bound2 = 1; }
		else { isPos = true; bound1 = (num.size() + (DIGITOFEACH - 1)) / DIGITOFEACH;  bound2 = 0; }

		for (int i = 0; i < bound1; ++i) {
			each = 0;
			for (int j = 0; j < DIGITOFEACH && idx > bound2; ++j) {
				each += (num[--idx] - '0')*((TYPEOFEACH)pow(10, j));
			}
			data.push_back(each);
		}
	}
	void assign(const BigInt &num) {
		this->data = num.data;
		this->isPos = num.isPos;
	}
	void assign(BigInt &&num) {
		this->Swap(num);
	}

	bool operator==(BigInt &num)const {
		return (isPos == num.isPos) && (this->abs_equal(num) == 0);
	}
	bool operator<(BigInt &num)const {
		if (isPos != num.isPos)return !isPos;
		else return (this->abs_equal(num) < 0) == isPos;
	}

	BigInt &operator<<=(unsigned int n) {
		while (n--)data.push_front(0);

		return *this;
	}
	BigInt &operator>>=(unsigned int n) {
		if (data.size()>n) {
			while (n--) data.pop_front();
		}
		else *this = 0;

		return *this;
	}

	BigInt &operator+=(BigInt &num) {
		if (isPos == num.isPos)this->abs_add(num);
		else this->abs_sub(num);

		return *this;
	}
	BigInt &operator-=(BigInt &num) {
		if (isPos == num.isPos) this->abs_sub(num);
		else this->abs_add(num);

		return *this;
	}
	BigInt &operator*=(BigInt &num) {
		if (!num.isPos)isPos = !isPos;

		this->abs_mul(num);

		return *this;
	}
	BigInt &operator/=(BigInt &num) {
		if (!num.isPos)isPos = !isPos;

		this->abs_div(num);

		return *this;
	}
	BigInt &div(BigInt &divisor, BigInt *remainder) {
		if (!divisor.isPos)isPos = !isPos;

		this->abs_div(divisor, remainder);

		return *this;
	}

	BigInt operator+(BigInt &num) {
		BigInt tmp = *this;
		tmp += num;

		return tmp;
	}
	BigInt operator-(BigInt &num) {
		BigInt tmp = *this;
		tmp -= num;

		return tmp;
	}
	BigInt operator*(BigInt &num) {
		BigInt tmp = *this;
		tmp *= num;

		return tmp;
	}
	BigInt operator/(BigInt &num) {
		BigInt tmp = *this;
		tmp /= num;

		return tmp;
	}

	void Swap(BigInt &num) {
		data.swap(num.data);
		std::swap(isPos, num.isPos);
	}
	void Print(bool newLine = false) {
		if (!isPos)printf("-");
		for (int i = data.size() - 1; i > -1; --i) {
			printf(FMTOFEACH, data[i]);
		}
		if (newLine)printf("\n");
	}

	//~BigInt() {}

private:
	deque<TYPEOFEACH>data; bool isPos;

	//返回:小于,-1	等于,0	大于,1;
	int abs_equal(BigInt &num)const {
		if (data.size() < num.data.size())return -1;
		else if (data.size()>num.data.size())return 1;
		else {
			for (int i = data.size() - 1; i > -1; --i) {
				if (data[i] != num.data[i]) {
					if (data[i] < num.data[i])return -1;
					else return 1;
				}
			}
			return 0;
		}
	}

	void abs_add(BigInt &num) {
		unsigned int bd = min(data.size(), num.data.size());
		if (data.size() < num.data.size()) {
			for (unsigned int i = data.size(); i < num.data.size(); ++i)data.push_back(num.data[i]);
		}

		for (unsigned int i = 0; i < bd - 1; ++i) {
			data[i] += num.data[i];
			if (data[i] >= MAXOFEACH) {
				data[i] -= MAXOFEACH;
				++data[i + 1];
			}
		}

		data[bd - 1] += num.data[bd - 1];
		if (data[bd - 1] >= MAXOFEACH) {
			data[bd - 1] -= MAXOFEACH;
			if (bd >= data.size())data.push_back(1);
			else ++data[bd];
		}

		for (unsigned int i = bd; i < data.size() - 1; ++i) {
			if (data[i] >= MAXOFEACH) {
				data[i] -= MAXOFEACH;
				++data[i + 1];
			}
			else break;
		}
		if (data[data.size() - 1]>MAXOFEACH) {
			data[data.size() - 1] -= MAXOFEACH;
			data.push_back(1);
		}
	}
	void abs_sub(BigInt &num) {
		int equal = this->abs_equal(num);
		if (equal == 0) {
			*this = 0;
			return;
		}

		BigInt tmp;
		if (equal < 0) {
			tmp = num;

			this->Swap(num);
			isPos = !num.isPos;
		}

		for (unsigned int i = 0; i < num.data.size(); ++i) {
			data[i] -= num.data[i];
			if (data[i] < 0) {
				data[i] += MAXOFEACH;
				--data[i + 1];
			}
		}

		for (unsigned int i = num.data.size(); i < data.size() - 1; ++i) {
			if (data[i] < 0) {
				data[i] += MAXOFEACH;
				--data[i + 1];
			}
		}

		if (equal < 0)num.Swap(tmp);

		while (!data.empty() && data.back() == 0)data.pop_back();
	}
	void abs_mul(BigInt &num) {
		if (num == (BigInt)0 || *this == (BigInt)0) {
			*this = 0;
			return;
		}
		else if (num.abs_equal((BigInt)1) == 0) {
			return;
		}
		else if (this->abs_equal((BigInt)1) == 0) {
			bool pos = isPos;
			*this = num;
			isPos = pos;
			return;
		}

		BigInt tmp = *this;
		*this = 0;
		BigInt _tmp;

		for (unsigned int i = 0; i < num.data.size(); ++i) {

			//*this += tmp*num.data[i];
			if (num.data[i] == 0) {}
			else if (num.data[i] == 1) {
				*this += tmp;
			}
			else {
				TYPEOFEACH carry = 0;
				_tmp = tmp; unsigned int size = _tmp.data.size();

				for (unsigned int j = 0; j < size - 1; ++j) {
					_tmp.data[j] *= num.data[i];
					if (carry) { _tmp.data[j] += carry; carry = 0; }
					carry = _tmp.data[j] / MAXOFEACH;
					_tmp.data[j] %= MAXOFEACH;
				}
				_tmp.data[size - 1] *= num.data[i];
				_tmp.data[size - 1] += carry;
				if (_tmp.data[size - 1] >= MAXOFEACH) {
					_tmp.data.push_back(_tmp.data[size - 1] / MAXOFEACH);
					_tmp.data[size - 1] %= MAXOFEACH;
				}

				*this += _tmp;
			}

			tmp <<= 1;
		}
	}
	void abs_div(BigInt &num, BigInt *remainder = NULL) {
		if (num == (BigInt)0) throw exception("Error Divisor!");
		if (this->abs_equal(num) < 0) { *remainder = *this; *this = 0; return; }
		if (num.abs_equal((BigInt)1) == 0) { *remainder = 0; return; }

		unsigned int bd = data.size() - num.data.size();
		BigInt _num = num, ans; _num <<= bd; ans.isPos = isPos;


		//TYPEOFEACH k, down = 0;
		for (unsigned int i = 0; i < bd + 1; ++i) {
			unsigned int k = 0; printf("%u\n", data.size());
			while (this->abs_equal(_num) >= 0) {
				this->abs_sub(_num); ++k;
			}
			ans.data.push_front(k);
			_num >>= 1; 
			/*bool less = false;
			for (unsigned int j = data.size() - 2; j>-1; --j) {
				if (data[j] != _num.data[j]) { less = data[j] < _num.data[j]; break; }
			}

			k = data.back() - (less ? 1 : 0) + down*MAXOFEACH;
			down = k%_num.data.back(); k /= _num.data.back();

			ans.data.push_front(k);
			*this -= (BigInt)k*_num;
			_num >>= 1;*/
		}
		if (remainder)*remainder = std::move(*this);

		this->Swap(ans);
		while (!data.empty() && data.back() == 0)data.pop_back();
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
}

int main(){
	test_3();

	return 0;
}