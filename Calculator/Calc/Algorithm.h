#pragma once

#ifndef _CALC_ALGORITHM_ABACKER_
#define _CALC_ALGORITHM_ABACKER_

#include <cmath>
#include <time.h>
#include <iostream>
#include <algorithm>

using namespace std;

#pragma warning(disable:4996)

#define LL long long
#define EPS 1e-10
#define MAXOFDENOMINATOR 100000LL

//���Լ��
LL gcd(LL a, LL b){
	return a == 0 ? b : gcd(b%a, a);
}

//��С������
inline LL lcm(LL a, LL b){
	return a / gcd(min(a, b), max(a, b))*b;
}

//�׳�
LL factorial(LL x){
	if (x == 0)return 1;
	bool negative = false;

	if (x < 0){ negative = true; x = -x; }

	LL ret = 1;
	for (int i = 1; i <= x; ++i)ret *= i;

	return negative ? -ret : ret;
}

//����a/b,������b�Ƿ�Ϊ0
inline double divCheck(double a, double b){
	if (b == 0)throw exception("Error:Bad Number For Divison!");

	return a / b;
}

//�ж�val�Ƿ�Ϊ����,����(1e-10)
inline bool isInt(double val){
	double d = val - round(val);
	return d > -(1e-10) && d < 1e-10;
}

//��double����ת��Ϊ�����������,�о��ȶ�ʧ
//���������ĸ��󲻳���MAXOFDENOMINATOR
bool doubleToFraction(double val){
	if (!isInt(val)){
		for (LL i = 2; i < MAXOFDENOMINATOR; ++i){
			if (isInt(i*val)){
				printf("%I64d/%I64d", (LL)round(i*val), i);
				//cout << "\t" << round(i*val) << "/" << i; 
				return true;
			}
		}
	}return false;
}

/*void doubleToFraction(double val){
	if (!isInt(val)){
		double m = 1; 
		bool negative = val < 0 ? true : false;
		val = abs(val);

		LL _fenzhi, _fenmu = 100000, fenzhi, fenmu;
		_fenzhi = val*_fenmu;
		for (LL i = -1000; i < 1000; ++i){
			if (i + _fenzhi>0){
				for (LL j = -1000; j < 1000; ++j){
					if (j + _fenmu>0){
						if (m>abs(val - (i + _fenzhi) / (j + _fenmu))){
							m = abs(val - (i + _fenzhi) / (j + _fenmu));
							fenzhi = i + _fenzhi; fenmu = j + _fenmu;
						}
					}
				}
			}
		}
		if (negative)fenzhi = -fenzhi;

		cout << "\t" << fenzhi << "/" << fenmu;
	}
}*/

//(a^b)%mod
LL fastPow(LL a, LL b, LL mod){
	LL ret = 1; a %= mod;
	while (b){
		if (b & 1){ ret *= a; ret %= mod; }
		a *= a; a %= mod;
		b >>= 1;
	}
	return ret;
}

//����һ����������[s,t]������
inline int random(int s, int t){
	return s + rand() % (t - s + 1);
}

//�������test��������val�Ƿ�Ϊ����
bool FermatTest(LL val, int test = 10000){
	int seed; srand(unsigned(time(0)));
	for (int j = 0; j < test; ++j){
		seed = random(2, 1000000);
		if ((seed % val>0) && fastPow(seed, val - 1, val) != 1){
			return false;
		}
	}return true;
}

//�ж�val�Ƿ�Ϊ����,��������1e+9ʱ���÷������,��һ�����!
bool isPrime(double val){
	LL num = LL(val + EPS);
	if (num < 10 * 10000 * 10000){
		if ((num & 1) == 0)return false;
		int _num = (int)num; int bd = (int)sqrt(_num) + 1;
		for (int i = 3; i < bd; i += 2)if (_num%i == 0)return false;
		return true;
	}
	else return FermatTest(num);
}

//��num��nλС�����
inline void printRadix(double num, unsigned int n) {
	char format[10];
	sprintf(format, "\t%%.%uf\n", n);
	printf(format, num);
}

//��num��ʮ���������
inline void printHex(double num) {
	cout << "\t" << hex << (LL)num << endl;
}

#endif;