/*
	多项式计算
	
	By 陈文杰 9/18/2015
*/

#include <string>
#include <cstring>
#include <iostream>

#include "Calc.h"

using namespace std;

#define debug 0x0

bool SpecialCMD(string &s){
	if (s == "cls"){
		system("cls");return true;
	}
	else if (s == "data"){
		cache.PrintData(); return true;
	}
	else if (s[0] >= 'A'&&s[0] <= 'Z'&&s[1] == '-'&&s[2] == '>'){
		cache.Set(s[0], Calc(s.substr(3, s.size() - 3), false)); return true;
	}

	return false;
}

#if (debug&0x1)
inline void test(const string &s){
	cout << ">" << s << endl; cout << "\t" << Calc(s) << endl;
}
#endif;

int main(){
	string s; 

#if (debug&0x1)
	s = "1-(1+2)*3"; test(s);
	s = "(1+2)*3="; test(s);
	s = "2/(1-(1+2))*3="; test(s);
#endif;

	while (printf(">"), cin >> s){
		try{
			if (!SpecialCMD(s))Calc(s),cache.PrintCur();
		}
		catch (exception &e){
			cout << "\t" << e.what() << endl;
		}
	}

	return 0;
}

#undef debug