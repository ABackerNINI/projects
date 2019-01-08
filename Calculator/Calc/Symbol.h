#pragma once

#ifndef _CALC_SYMBOL_ABACKER_
#define _CALC_SYMBOL_ABACKER_

#include <cstring>
#include <iostream>

#include "Commen.h"
#include "Algorithm.h"

using namespace std;

#pragma warning(disable:4996)

#define DEBUG 0x0
#define DEBUG_OPERATOR_MAP 0x1
#define DEBUG_VARIABALE_MAP 0x1
#define VARREPLACE 0

//1,2,3,4, 5, 6, 7, 8,9, 10,  11, 12, 13,    14,    15,    16, 17, 18,19, 20,21,22,23,24,25,26,  27, 28,29,
//+,-,*,/,++,--,**,//,%,pow,sqrt,sin,cos,tan,arcsin,arccos,arctan,gcd,lcm,ln,log, ^, |, &, !, ~, ',arc',var, #,

#define OPERATORN 29//运算符的个数
#define DEVIATION -100//运算符映射偏移量,改为'a'可以更好debug运算符替换,但可能影响运算符映射

//运算符映射,注意不能具有前包含性,即"++"包含了"+",所以"++"需在后;"#"需在最后
											// 1,   2,   3,   4,    5,    6,    7,    8,     9,    10,     11,    12,    13,    14,       15,       16,       17,    18    ,19,   20,    21,  22,  23,  24,  25,  26,  27,     28, 29,
static const string Operators[OPERATORN] = { "+", "-", "*", "/", "++", "--", "**", "//",   "%", "pow", "sqrt", "sin", "cos", "tan", "arcsin", "arccos", "arctan", "gcd", "lcm", "ln", "log", "^", "|", "&", "~", "!", "'", "arc'", "#" };
static const int OptrPrio[OPERATORN] = {       2,   2,   3,   3,    2,    2,    4,    4,     3,     5,      5,     5,     5,     5,        5,        5,        5,     5,     5,    5,     5,   1,   1,   1,   1,   6,   6,      5,  0  };//运算符优先级
static const int OptrCpd[OPERATORN] = {	       2,   2,   2,   2,    1,    1,    2,    2,     2,     2,      1,     1,     1,     1,        1,        1,        1,     2,     2,    1,     2,   2,   2,   2,   1,   1,   1,      1,  0 };//运算符目数
 
/**
0	#
1	^	|	&	~
2	+	-	++	--
3	*	/	%
4	**	//
5	math_func
6	!	'
*/

#if VARREPLACE
#define VARIABLEN 2//常量的个数

//常量映射,同样注意不能具有前包含性,且不能包含运算符,如:"cospi"包含了"cos",所以不能使用"cospi"
static const string Variables[] = { "PI", "e" };
static const string VarRpcmet[] = { " 3.14159265358979323846264", "2.718281828459" };
#endif;

//结束符#
inline int endSym(){
	return OPERATORN - 1 + DEVIATION;
}

//预处理括号,正负号和运算符映射
void precondition(string &expr) {

	//括号替换
	int size = (int)expr.size();
	for (int i = 0; i < size; ++i) {
		if (expr[i] == '{' || expr[i] == '[')expr[i] = '(';
		else if (expr[i] == '}' || expr[i] == ']')expr[i] = ')';
	}

	//判断正负号:+-在第一位或者在'('或','后的为正负号
	for (int i = 0; i < size; ++i) {
		if (expr[i] == '-' || expr[i] == '+') {
			if (i == 0 || expr[i - 1] == '(' || expr[i - 1] == ',') {
				if (expr[i] == '-')expr.replace(i, 1, "--");
				else expr.replace(i, 1, "++");
			}
		}
	}

	//符号替换
	size_t at; string rpc = " ";
	for (int i = OPERATORN - 1; i > -1; --i) {
		rpc[0] = i + DEVIATION;
		while (at = expr.find(Operators[i]), ~at) {
			expr.replace(at, Operators[i].size(), rpc);
#if (DEBUG&DEBUG_OPERATOR_MAP)
			cout << "\t" << Operators[i] << "->" << rpc << endl;
#endif;
		}
	}

#if(VARREPLACE)
	//变量替换
	for (int i = 0; i < VARIABLEN; ++i) {
		while (at = s.find(Variables[i]), ~at) {
			s.replace(at, Variables[i].size(), VarRpcmet[i]);
#if (DEBUG&DEBUG_VARIABALE_MAP)
			cout << "\t" << Variables[i] << "->" << VarRpcmet[i] << endl;
#endif;
		}
	}
#endif;

#if (DEBUG&DEBUG_OPERATOR_MAP)
	cout << "\t" << s << endl;
#endif;
}

//  1,   2,   3,   4,    5,    6,    7,    8,     9,    10,     11,    12,    13,    14,       15,       16,       17,    18    ,19,   20,    21,  22,  23,  24,  25,  26,  27,     28, 29,
//"+", "-", "*", "/", "++", "--", "**", "//",   "%", "pow", "sqrt", "sin", "cos", "tan", "arcsin", "arccos", "arctan", "gcd", "lcm", "ln", "log", "^", "|", "&", "~", "!", "'", "arc'", "#"

//计算OPTR栈首定义的运算
void Calc(stack<char>&OPTR, stack<double>&OPND) {
	char sym = GetTop(OPTR);
	double ans = 0, b = 0, a = 0;
	if (OptrCpd[sym - DEVIATION] > 0)b = GetTop(OPND);
	if (OptrCpd[sym - DEVIATION] == 2)a = GetTop(OPND);//双目运算

	switch (sym - DEVIATION + 1) {
	case 1:ans = a + b; break;
	case 2:ans = a - b; break;
	case 3:ans = a*b; break;
	case 4:ans = divCheck(a, b); break;
	case 5:ans = b; break;
	case 6:ans = -b; break;
	case 7:ans = pow(a, b); break;
	case 8:ans = pow(a, divCheck(1, b)); break;
	case 9:ans = (double)(((LL)a) % ((LL)b)); break;
	case 10:ans = pow(a, b); break;
	case 11:ans = sqrt(b); break;
	case 12:ans = sin(b); break;
	case 13:ans = cos(b); break;
	case 14:ans = tan(b); break;
	case 15:ans = asin(b); break;
	case 16:ans = acos(b); break;
	case 17:ans = atan(b); break;
	case 18:ans = (double)gcd((LL)min(a, b), (LL)max(a, b)); break;
	case 19:ans = (double)lcm((LL)a, (LL)b); break;
	case 20:ans = log(b); break;
	case 21:ans = log(b) / log(a); break;
	case 22:ans = (double)((LL)a ^ (LL)b); break;
	case 23:ans = (double)((LL)a | (LL)b); break;
	case 24:ans = (double)((LL)a & (LL)b); break;
	case 25:ans = (double)(~(LL)b); break;
	case 26:ans = (double)factorial((LL)b); break;
	case 27:ans = b / 180 * acos(-1.0); break;//角度转弧度
	case 28:ans = b * 180 / acos(-1.0); break;//弧度转角度
	default:throw exception("Error:Wrong Expression!"); break;
	}

	OPND.push(ans);

	if (SYMBOLDEBUG) { cout << "\t" << a << " " << Operators[sym - DEVIATION] << " " << b << " = " << ans << "\t"; doubleToFraction(ans); cout << endl; }
}

//返回运算符优先级
inline int Prio(char c) {
	if (c == '(')return -1;
	return OptrPrio[c - DEVIATION];
}

#undef DEBUG
#undef DEVIATION
#undef OPERATORN

#endif