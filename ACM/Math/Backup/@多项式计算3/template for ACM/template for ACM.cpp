/*
	多项式计算
	
	By ABacker 9/18/2015
*/

#include <string>
#include <cstring>
#include <iostream>

#include "Calc.h"
#include "Commen.h"
#include "fractional.h"

using namespace std;

#define DEBUG 0x0
#define DEBUG_TEST 0x1

bool SpecialCMD(const string &s){
	if (s.size() > 2 && isCap(s[0]) && s[1] == '='){
		cac.Set(s[0], Calc(s.substr(2, s.size() - 2), false)); return true;
	}
	if (s.size() > 3 && isCap(s[0]) && s[1] == '-'&&s[2] == '>'){
		cac.Set(s[0], Calc(s.substr(3, s.size() - 3), false)); return true;
	}
	return false;
}

#if (DEBUG&DEBUG_TEST)
inline void test(const string &s){
	if (s == "")return;
	cout << ">" << s << endl;
	try{
		if (!SpecialCMD(s)){
			Calc(s);
		}
	}
	catch (exception &e){
		cout << "\t" << e.what() << endl;
	}
}
#endif;

int main(){
	string s; 

#if (DEBUG&DEBUG_TEST)
	s = "3/2 + 1/3 + 1/(-3)"; test(s);//1.5 3/2
	s = "3/(-2)"; test(s);//-1.5 -3/2
	s = "1-(1+2)*3"; test(s);//-8
	s = "(1+2)*3="; test(s);//9
	s = "2/{[1-(1+2)]*3}="; test(s);//-0.333 -1/3
	s = "10-3*(2/1-(6*2+(21+3/5)*8/3)*(-2))+8*2"; test(s);//-397.6
	s = "sin(30')"; test(s);//0.5
	s = "cos(60')"; test(s);//0.5
	s = "C->1+2+3"; test(s);
	s = "C/2"; test(s);//3
	s = "hex(D*3)"; test(s);//1b
	s = "var"; test(s);
#endif;

	while (printf(">"), getline(cin, s),s!=""){
		try{
			if (!SpecialCMD(s))Calc(s);
		}
		catch (exception &e){
			cout << "\t" << e.what() << endl;
		}
	}

	return 0;
}

#undef DEBUG
#undef DEBUG_TEST