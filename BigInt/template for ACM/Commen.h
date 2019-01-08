#pragma once

#ifndef _CALC_COMMEN_ABACKER_
#define _CALC_COMMEN_ABACKER_

#include <time.h>
#include <iostream>

using namespace std;

#include "Matrix.h"
#include "BigInt.h"

void readMarix(Matrix<BigInt>*matrix) {
	string s;
	for (int i = 0; i < matrix->n; ++i) {
		for (int j = 0; j < matrix->m; ++j) {
			cin >> s; (*matrix)[i][j] = s;
		}
	}
}

//判断是否为数字
inline bool isNum(char c){
	return c >= '0'&&c <= '9';
}

//判断是否为字母
inline bool isLtr(char c) {
	return c >= 'A'&&c <= 'Z' || c >= 'a'&&c <= 'z';
}

//判断是否为大写字母
inline bool isCap(char c){
	return c >= 'A'&&c <= 'Z';
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

	return ~point ? fig / pow((long long)10, (long long)point) : fig;
}

//获取string s在位置pos处的变量名,并推进pos
string getVar(const string &s,int &pos) {
	string str = "";
	while (isLtr(s[pos])) {
		str += s[pos++];
	}--pos;

	return str;
}

//判断栈顶是否为空
template<typename T>inline T GetTop(stack<T>&st, bool rid = true){
	if (st.empty())throw exception("Error:Wrong Expression!");

	if (rid){ T ret = st.top(); st.pop(); return ret; }
	else return st.top();
}

#endif;