#pragma once

#ifndef _CALC_CALC_ABACKER_
#define _CALC_CALC_ABACKER_

#include <stack>
#include <cstring>
#include <iostream>

#include "Symbol.h"
#include "Commen.h"

using namespace std;

stack<char>OPTR;
stack<double>OPND;

double Calc(string s,bool isCache = true){
	CACHE = isCache;
	precondition(s);

	while (!OPTR.empty())OPTR.pop();
	while (!OPND.empty())OPND.pop();

	OPTR.push(endSym());//#

	int size = s.size();
	if (s.back() == '=')--size;

	for (int i = 0; i < size; ++i){
		if (s[i] == ' ')continue;
		else if (isCap(s[i]))OPND.push(cac.Get(s[i]));//±äÁ¿
		else if (isNum(s[i]))OPND.push(getFigure(s, i));//Êý×Ö
		else if (s[i] == ',')while (GetTop(OPTR, false) != '(')Calc(OPTR, OPND);
		else if (s[i] == '(')OPTR.push('(');
		else if (s[i] == ')'){
			while (GetTop(OPTR, false) != '('){
				Calc(OPTR, OPND);
			}GetTop(OPTR);
		}
		else{//·ûºÅ
			while (Prio(s[i]) <= Prio(GetTop(OPTR, false))){
				Calc(OPTR, OPND);
			}OPTR.push(s[i]);
		}
	}
	while (GetTop(OPTR, false) != endSym()){//#
		Calc(OPTR, OPND);
	}

	if (OPTR.size() > 1 || OPND.size() > 1)throw exception("Error:Wrong Expression!");

	if (CACHE){ cac.Push(GetTop(OPND, false)); cac.PrintLastPush(); }

	return GetTop(OPND, false);
}

#endif;