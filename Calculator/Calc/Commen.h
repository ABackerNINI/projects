#pragma once

#ifndef _CALC_COMMEN_ABACKER_
#define _CALC_COMMEN_ABACKER_

#include <time.h>
#include <iostream>

using namespace std;

bool SYMBOLDEBUG = true;

const static char *helpInf = "Calc V2.0    2015    @ABacker\n"
"\n"
"##运算符优先级:\n"
"0	#\n"
"1	^(异或)		|(或)		&(与)		~(取反)\n"
"2	+		-		++(正)		--(负)\n"
"3	*		/		%%(取模)\n"
"4	**(乘方)	//(开方)\n"
"5	math_func\n"
"6	!(阶乘)		'(角度转弧度)\n"
"其中math_func包括:\n"
"pow(乘方),sqrt(方根),sin,cos,tan,arcsin,arccos,arctan,arc'(弧度转角度),gcd(最大公约数),lcm(最小公倍数),log,ln\n"
"\n"
"##特殊命令:\n"
"cls: 清屏\n"
"debug on/debug off: 打开/关闭调试消息显示\n"
"\n"
"输入\"demo\"获取示例...\n";


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

//获取string s在位置pos处的数字,并推进pos至数字最后一位
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

//获取string s在位置pos处的变量名,并推进pos至变量名最后一位
string getVar(const string &s, int &pos) {
	string str = "";
	while (s[pos] == ' ')++pos;
	while (isLtr(s[pos])) {
		str += s[pos++];
	}--pos;

	return str;
}

//获取string s在位置pos处的变量名
string getVar(const string &s, int &&pos) {
	string str = "";
	while (s[pos] == ' ')++pos;
	while (isLtr(s[pos])) {
		str += s[pos++];
	}--pos;

	return str;
}

//获取string s在位置pos处的符号,并推进pos
/*string getSym(const string &s, int &pos){
	string tmp;tmp += s[pos];
}*/

//判断栈顶是否为空
template<typename T>inline T GetTop(stack<T>&st, bool rid = true){
	if (st.empty())throw exception("Error:Wrong Expression!");

	if (rid){ T ret = st.top(); st.pop(); return ret; }
	else return st.top();
}

#endif;