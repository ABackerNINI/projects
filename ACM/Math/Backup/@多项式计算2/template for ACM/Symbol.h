#pragma once

#ifndef _CALC_SYMBOL_ABACKER_
#define _CALC_SYMBOL_ABACKER_

#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>

#include "Commen.h"

using namespace std;

#pragma warning(disable:4996)

#define DEBUG 0x0
#define DEBUG_OPERATOR_MAP 0x1
#define DEBUG_VARIABALE_MAP 0x1

//1,2,3,4, 5, 6, 7, 8,  9,  10, 11, 12, 13,    14,    15,    16, 17, 18,19, 20,21,22,23,24,25,26,  27, 28, 29,       30,          31, 32.33,
//+,-,*,/,++,--,**,//,pow,sqrt,sin,cos,tan,arcsin,arccos,arctan,gcd,lcm,ln,log, ^, |, &, !, ~, ',arc',cls,var,debug off,setprecision,hex, #,

#define OPERATORN 33//������ĸ���
#define DEVIATION -100//�����ӳ��ƫ����,��Ϊ'a'���Ը���debug������滻,������Ӱ�������ӳ��

//�����ӳ��,ע�ⲻ�ܾ���ǰ������,��"++"������"+",����"++"���ں�;"#"�������
static const string Operators[OPERATORN] = { "+", "-", "*", "/", "++", "--", "**", "//", "pow", "sqrt", "sin", "cos",
"tan", "arcsin", "arccos", "arctan", "gcd", "lcm", "ln", "log", "^", "|", "&", "!", "~", "'", "arc'", "cls", "var", "debug off", "setprecision", "hex", "#" };
static const int OptrCpd[OPERATORN] = { 2, 2, 2, 2, 1, 1, 2, 2/*//*/, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2/*lcm*/, 1, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 2, 1, 0 };//�����Ŀ��
static const int OptrPrio[OPERATORN] = { 2, 2, 3, 3, 4, 4, 5, 5/*//*/, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6/*lcm*/, 6, 6, 1, 1, 1, 4, 1, 7, 6, 0, 0, 0, 0, 0, -1 };//��������ȼ�

#define VARIABLEN 2//�����ĸ���

//����ӳ��,ͬ��ע�ⲻ�ܾ���ǰ������,�Ҳ��ܰ��������,��:"cospi"������"cos",���Բ���ʹ��"cospi"
static const string Variables[] = { "PI", "e" };
static const string VarRpcmet[] = { " 3.14159265358979323846264", "2.718281828459" };

//������#
inline int endSym(){
	return OPERATORN - 1 + DEVIATION;
}

//Ԥ��������,�����ź������ӳ��
void precondition(string &s){

	//�����滻
	int size = s.size();
	for (int i = 0; i < size; ++i){
		if (s[i] == '{' || s[i] == '[')s[i] = '(';
		else if (s[i] == '}' || s[i] == ']')s[i] = ')';
	}

	//�ж�������:+-�ڵ�һλ������'('��','���Ϊ������
	for (int i = 0; i < size; ++i){
		if (s[i] == '-' || s[i] == '+'){
			if (i == 0 || s[i - 1] == '(' || s[i - 1] == ','){
				if (s[i] == '-')s.replace(i, 1, "--");
				else s.replace(i, 1, "++");
			}
		}
	}

	//�����滻
	int at; string rpc = " ";
	for (int i = OPERATORN - 1; i > -1; --i){
		rpc[0] = i + DEVIATION;
		while (at = s.find(Operators[i]), ~at){
			s.replace(at, Operators[i].size(), rpc);
#if (DEBUG&DEBUG_OPERATOR_MAP)
			cout << "\t" << Operators[i] << "->" << rpc << endl;
#endif;
		}
	}

	//�����滻
	for (int i = 0; i<VARIABLEN; ++i){
		while (at = s.find(Variables[i]), ~at){
			s.replace(at, Variables[i].size(), VarRpcmet[i]);
#if (DEBUG&DEBUG_VARIABALE_MAP)
			cout << "\t" << Variables[i] << "->" << VarRpcmet[i] << endl;
#endif;
		}
	}

#if (DEBUG&DEBUG_OPERATOR_MAP)
	cout << "\t" << s << endl;
#endif;
}

//1,2,3,4, 5, 6, 7, 8,  9,  10, 11, 12, 13,    14,    15,    16, 17, 18,19, 20,21,22,23,24,25,26,  27, 28, 29,       30,          31, 32,33,
//+,-,*,/,++,--,**,//,pow,sqrt,sin,cos,tan,arcsin,arccos,arctan,gcd,lcm,ln,log, ^, |, &, !, ~, ',arc',cls,var,debug off,setprecision,hex, #,

//����OPTRջ�׶��������
void Calc(stack<char>&OPTR, stack<double>&OPND){
	char sym = GetTop(OPTR);
	double ans = 0, b = 0, a = 0;
	if (OptrCpd[sym - DEVIATION] >0)b = GetTop(OPND);
	if (OptrCpd[sym - DEVIATION] == 2)a = GetTop(OPND);//˫Ŀ����

	switch (sym - DEVIATION + 1){
	case 1:ans = a + b; break;
	case 2:ans = a - b; break;
	case 3:ans = a*b; break;
	case 4:ans = divCheck(a, b); break;
	case 5:ans = b; break;
	case 6:ans = -b; break;
	case 7:ans = pow(a, b); break;
	case 8:ans = pow(a, divCheck(1, b)); break;
	case 9:ans = pow(a, b); break;
	case 10:ans = sqrt(b); break;
	case 11:ans = sin(b); break;
	case 12:ans = cos(b); break;
	case 13:ans = tan(b); break;
	case 14:ans = asin(b); break;
	case 15:ans = acos(b); break;
	case 16:ans = atan(b); break;
	case 17:ans = (double)gcd((LL)min(a, b), (LL)max(a, b)); break;
	case 18:ans = (double)lcm((LL)a, (LL)b); break;
	case 19:ans = log(b); break;
	case 20:ans = log(b) / log(a); break;
	case 21:ans = (double)((LL)a ^ (LL)b); break;
	case 22:ans = (double)((LL)a | (LL)b); break;
	case 23:ans = (double)((LL)a & (LL)b); break;
	case 24:ans = (double)factorial((LL)b); break;
	case 25:ans = (double)(~(LL)b); break;
	case 26:ans = b / 180 * acos(-1.0); break;
	case 27:ans = b * 180 / acos(-1.0); break;
	case 28:system("cls"); CACHE = false; OPND.push(0); return;
	case 29:cac.PrintAll(); CACHE = false; OPND.push(0); return;
	case 30:SYMBOLDEBUG = false; CACHE = false; OPND.push(0); return;
	case 31:char format[10];sprintf(format, "\t%%.%df\n", (int)a);printf(format, b); CACHE = false; OPND.push(b); return;
	case 32:cout << "\t" << hex << (LL)b << endl; CACHE = false; OPND.push(b); return;
	default:throw exception("Error:Wrong Expression!"); break;
	}

	OPND.push(ans);

	if (SYMBOLDEBUG){ cout << "\t" << a << " " << Operators[sym - DEVIATION] << " " << b << " = " << ans;  doubleToFraction(ans); cout << endl; }
}

//������������ȼ�
inline int Prio(char c){
	if (c == '(')return -1;
	return OptrPrio[c - DEVIATION];
}

#undef DEBUG
#undef DEVIATION
#undef OPERATORN

#endif