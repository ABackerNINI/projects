#pragma once

#ifndef _CALC_COMMEN_ABACKER_
#define _CALC_COMMEN_ABACKER_

#include <time.h>
#include <iostream>

using namespace std;

bool SYMBOLDEBUG = true;

const static char *helpInf = "Calc V2.0    2015    @ABacker\n"
"\n"
"##��������ȼ�:\n"
"0	#\n"
"1	^(���)		|(��)		&(��)		~(ȡ��)\n"
"2	+		-		++(��)		--(��)\n"
"3	*		/		%%(ȡģ)\n"
"4	**(�˷�)	//(����)\n"
"5	math_func\n"
"6	!(�׳�)		'(�Ƕ�ת����)\n"
"����math_func����:\n"
"pow(�˷�),sqrt(����),sin,cos,tan,arcsin,arccos,arctan,arc'(����ת�Ƕ�),gcd(���Լ��),lcm(��С������),log,ln\n"
"\n"
"##��������:\n"
"cls: ����\n"
"debug on/debug off: ��/�رյ�����Ϣ��ʾ\n"
"\n"
"����\"demo\"��ȡʾ��...\n";


//�ж��Ƿ�Ϊ����
inline bool isNum(char c){
	return c >= '0'&&c <= '9';
}

//�ж��Ƿ�Ϊ��ĸ
inline bool isLtr(char c) {
	return c >= 'A'&&c <= 'Z' || c >= 'a'&&c <= 'z';
}

//�ж��Ƿ�Ϊ��д��ĸ
inline bool isCap(char c){
	return c >= 'A'&&c <= 'Z';
}

//��ȡstring s��λ��pos��������,���ƽ�pos���������һλ
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

//��ȡstring s��λ��pos���ı�����,���ƽ�pos�����������һλ
string getVar(const string &s, int &pos) {
	string str = "";
	while (s[pos] == ' ')++pos;
	while (isLtr(s[pos])) {
		str += s[pos++];
	}--pos;

	return str;
}

//��ȡstring s��λ��pos���ı�����
string getVar(const string &s, int &&pos) {
	string str = "";
	while (s[pos] == ' ')++pos;
	while (isLtr(s[pos])) {
		str += s[pos++];
	}--pos;

	return str;
}

//��ȡstring s��λ��pos���ķ���,���ƽ�pos
/*string getSym(const string &s, int &pos){
	string tmp;tmp += s[pos];
}*/

//�ж�ջ���Ƿ�Ϊ��
template<typename T>inline T GetTop(stack<T>&st, bool rid = true){
	if (st.empty())throw exception("Error:Wrong Expression!");

	if (rid){ T ret = st.top(); st.pop(); return ret; }
	else return st.top();
}

#endif;