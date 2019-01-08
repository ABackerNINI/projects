#pragma once

#ifndef _CALC_CALC_ABACKER_
#define _CALC_CALC_ABACKER_

#include <stack>
#include <cstring>
#include <iostream>

#include "Cache.h"
#include "Symbol.h"
#include "Commen.h"

using namespace std;

Cache cache;
stack<char>OPTR;
stack<double>OPND;

double Calc(string expr, bool isCache = true) {
	precondition(expr);

	while (!OPTR.empty())OPTR.pop();
	while (!OPND.empty())OPND.pop();

	OPTR.push(endSym());//#

	int size = (int)expr.size();
	//if (s.back() == '=')--size;

	for (int i = 0; i < size; ++i) {
		if (expr[i] == ' ' || expr[i] == '=')continue;
		else if (isLtr(expr[i])) {//±äÁ¿
			try {
				OPND.push(cache.get(getVar(expr, i)));
			}
			catch (...) {
				throw exception("Error:Wrong Expression!");
			}
		}
		else if (isNum(expr[i]))OPND.push(getFigure(expr, i));//Êý×Ö
		else if (expr[i] == ',')while (GetTop(OPTR, false) != '(')Calc(OPTR, OPND);
		else if (expr[i] == '(')OPTR.push('(');
		else if (expr[i] == ')') {
			while (GetTop(OPTR, false) != '(') {
				Calc(OPTR, OPND);
			}GetTop(OPTR);
		}
		else {//·ûºÅ
			while (Prio(expr[i]) <= Prio(GetTop(OPTR, false))) {
				Calc(OPTR, OPND);
			}OPTR.push(expr[i]);
		}
	}

	while (GetTop(OPTR, false) != endSym()) {//#
		Calc(OPTR, OPND);
	}

	if (OPTR.size() > 1 || OPND.size() > 1)throw exception("Error:Wrong Expression!");
	if (isCache) { cache.push(GetTop(OPND, false)); cache.printLastPush(); }

	return GetTop(OPND, false);
}

#endif;