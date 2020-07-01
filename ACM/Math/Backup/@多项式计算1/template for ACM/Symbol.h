#pragma once

#ifndef _CALC_SYMBOL_ABACKER_
#define _CALC_SYMBOL_ABACKER_

#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define debug 0x0
#define ll long long

//1,2,3,4, 5, 6, 7, 8,  9,  10, 11, 12, 13,    14,    15,    16, 17, 18,19,20,21,22,23,24,  25,
//+,-,*,/,++,--,**,//,pow,sqrt,sin,cos,tan,arcsin,arccos,arctan,gcd,lcm, ^, |, &, !, ~, ',arc',

#define OPERATORN 26
static string Operators[OPERATORN] = { "+", "-", "*", "/", "++", "--", "**", "//", "pow", "sqrt", "sin", "cos", "tan", "arcsin", "arccos", "arctan", "gcd", "lcm", "^", "|", "&", "!", "~", "'","arc'","#" };
static int OptrCpd[OPERATORN] = { 2, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 0 };
static int OptrRank[OPERATORN] = { 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 1, 1, 1, 4, 1, 7, 6, 0 };

int endSym(){
	return OPERATORN - 1 + 'a';
}

void precondition(string &s){

	//括号替换
	int size = s.size();
	for (int i = 0; i < size; ++i){
		if (s[i] == '{' || s[i] == '[')s[i] = '(';
		else if (s[i] == '}' || s[i] == ']')s[i] = ')';
	}

	//判断正负号
	for (int i = 0; i < size; ++i){
		if (s[i] == '-' || s[i] == '+'){
			if (i == 0 || s[i - 1] == '('){//+-在第一位或者前面的是'('为正负号
				if (s[i] == '-')s.replace(i, 1, "--");
				else s.replace(i, 1, "++");
			}
		}
	}

	//符号替换
	int at; string rpc = " ";
	for (int i = OPERATORN - 1; i > -1; --i){
		rpc[0] = i + 'a';
		while (at = s.find(Operators[i]), ~at){
			s.replace(at, Operators[i].size(), rpc);
#if (debug&0x1)
			cout << "\t" << Operators[i] << "->" << rpc << endl;
#endif;
		}
	}
#if (debug&0x1)
	cout << "\t" << s << endl;
#endif;
}

inline int Rank(char c){
	return OptrRank[c - 'a'];
}


#undef debug

#endif