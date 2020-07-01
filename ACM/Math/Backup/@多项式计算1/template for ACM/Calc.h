#pragma once

#ifndef _CALC_CALC_ABACKER_
#define _CALC_CALC_ABACKER_

#include <stack>
#include <cstring>
#include <iostream>

#include "Symbol.h"
#include "Cache.h"

using namespace std;

#define debug 0x1
#define ll long long
#define eps 0.0000000000000001

Cache cache;

ll gcd(ll a, ll b){
	return a == 0 ? b : gcd(b%a, a);
}
ll factorial(ll x){
	if (x < 0)throw exception("bad num for factorial!");

	if (x == 0)return 1;

	ll ret = 1;
	for (ll i = 1; i < x; ++i){
		ret *= i;
	}return ret;
}
inline double divCheck(double a,double b){
	if (b == 0)throw exception("Error:Bad Number For Divison!");

	return a / b;
}

template<typename T>inline T GetTop(stack<T>&st, bool rid = true){
	if (st.empty()){ throw exception("Error:Wrong Expression!"); }

	if (rid){ T ret = st.top(); st.pop(); return ret; }
	else return st.top();
}

//1,2,3,4, 5, 6, 7, 8,  9,  10, 11, 12, 13,    14,    15,    16, 17, 18,19,20,21,22,23,24,  25,
//+,-,*,/,++,--,**,//,pow,sqrt,sin,cos,tan,arcsin,arccos,arctan,gcd,lcm, ^, |, &, !, ~, ',arc',
void Calc(stack<int>&OPTR, stack<double>&OPND){
	char sym = GetTop(OPTR);
	double ans, b = GetTop(OPND), a = 0;
	if (OptrCpd[sym - 'a'] == 2)a = GetTop(OPND);

	switch (sym - 'a' + 1){
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
	case 17:ans = (double)gcd((ll)min(a, b), (ll)max(a, b)); break;
	case 18:ans = (double)((ll)a*(ll)b / gcd((ll)min(a, b), (ll)max(a, b))); break;
	case 19:ans = (double)((ll)a ^ (ll)b); break;
	case 20:ans = (double)((ll)a | (ll)b); break;
	case 21:ans = (double)((ll)a & (ll)b); break;
	case 22:ans = (double)factorial((ll)b); break;
	case 23:ans = (double)(~(ll)b); break;
	case 24:ans = b / 180 * acos(-1.0); break;
	case 25:ans = b * 180 / acos(-1.0); break;
	default:throw exception("Error:Wrong Expression!"); break;
	}

	OPND.push(ans);

#if (debug&0x1)
	cout << "\t" << a << " " << Operators[sym - 'a'] << " " << b << " = " << ans << endl;
#endif;
}

double Calc(string s, bool isCache = true){
	precondition(s);

	stack<int>OPTR;
	stack<double>OPND;
	OPTR.push(endSym());//#

	double fig; int point;

	int size = s.size();
	if (s.back() == '=')--size;

	for (int i = 0; i < size; ++i){
		if (s[i] >= '0'&&s[i] <= '9'){//Êý×Ö
			fig = s[i] - '0'; point = -1;
			while (s[++i] >= '0'&&s[i] <= '9' || s[i] == '.'){
				if (s[i] == '.')point = 0;
				else{
					if (~point)++point;
					fig = fig * 10 + s[i] - '0';
				}
			}--i;
			OPND.push(~point ? fig / pow((ll)10, (ll)point) : fig);
		}
		else if (s[i] >= 'A'&&s[i] <= 'Z')OPND.push(cache.Get(s[i]));
		else if (s[i] == ' ')continue;
		else if (s[i] == ',')while (GetTop(OPTR, false) != '(')Calc(OPTR, OPND);
		else if (s[i] == '(')OPTR.push('(');
		else if (s[i] == ')'){
			while (GetTop(OPTR, false) != '('){
				Calc(OPTR, OPND);
			}GetTop(OPTR);
		}
		else{//·ûºÅ
			while (Rank(s[i]) <= Rank(GetTop(OPTR, false))){
				Calc(OPTR, OPND);
			}OPTR.push(s[i]);
		}
	}
	while (GetTop(OPTR, false) != endSym()){//#
		Calc(OPTR, OPND);
	}

	if (isCache)cache.Push(GetTop(OPND, false));

	return GetTop(OPND, false);
}

#undef debug

#endif;