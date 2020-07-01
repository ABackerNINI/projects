#pragma once

#ifndef _CALC_COMMEN_ABACKER_
#define _CALC_COMMEN_ABACKER_

#include <iostream>

using namespace std;

#include "Cache.h"

#define LL long long

static Cache cac;
static bool CACHE;
static bool SYMBOLDEBUG = true;

//判断是否为数字
inline bool isNum(char c){
	return c >= '0'&&c <= '9';
}

//判断是否为大写字母
inline bool isCap(char c){
	return c >= 'A'&&c <= 'Z';
}

//最大公约数
LL gcd(LL a, LL b){
	return a == 0 ? b : gcd(b%a, a);
}

//最小公倍数
inline LL lcm(LL a,LL b){
	return a / gcd(min(a, b), max(a, b))*b;
}

//阶乘
LL factorial(LL x){
	if (x == 0)return 1;
	bool negative = false;

	if (x < 0){ negative = true; x = -x; }

	LL ret = 1;
	for (int i = 1; i <= x; ++i)ret *= i;

	return negative ? -ret : ret;
}

//返回a/b,检查除数b是否为0
inline double divCheck(double a, double b){
	if (b == 0)throw exception("Error:Bad Number For Divison!");

	return a / b;
}

//获取string s在位置pos处的数字,并推进pos
double getFigure(const string &s, int &pos){
	double fig = s[pos] - '0'; int point = -1;
	while (s[++pos] >= '0'&&s[pos] <= '9' || s[pos] == '.'){
		if (s[pos] == '.')point = 0;
		else{
			if (~point)++point;
			fig = fig * 10 + s[pos] - '0';
		}
	}--pos;

	return ~point ? fig / pow((LL)10, (LL)point) : fig;
}

//判断val是否为整数,精度(1e-10)
inline bool isInt(double val){
	double d = val - round(val);
	return d > -(1e-10) && d < 1e-10;
}

//将double类型转换为分数类型输出,有精度丢失
//输出的数分母最大不超过10000
bool doubleToFraction(double val){
	if (!isInt(val)){
		for (LL i = 2; i < 10000; ++i){
			if (isInt(i*val)){
				cout << "\t" << round(i*val) << "/" << i; return true;
			}
		}
	}return false;
}

bool doubleToFraction2(double val){
	if (!isInt(val)){
		
	}return false;
}

//判断栈顶是否为空
template<typename T>inline T GetTop(stack<T>&st, bool rid = true){
	if (st.empty())throw exception("Error:Wrong Expression!");

	if (rid){ T ret = st.top(); st.pop(); return ret; }
	else return st.top();
}

#endif;