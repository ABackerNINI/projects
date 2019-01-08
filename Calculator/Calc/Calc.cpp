/*
Calc V2

By ABacker 9/18/2015
*/

#include <string>
#include <cstring>
#include <iostream>

#include "Calc.h"
#include "Commen.h"
#include "Algorithm.h"
#include <windows.h>

using namespace std;

void demo(const string &s, const char *ps = NULL) {
	bool SpecialCMD(const string &s);

	if (s == "")return;
	cout << ">" << s;
	if (ps != NULL) {
		int nSpace = 40 - (int)s.size();
		while (--nSpace&&nSpace > 0)printf(" ");
		cout << "[" << ps << "]";
	}
	cout << endl;
}

void demo() {
	string s; SYMBOLDEBUG = false;
	s = "3/2 + 1/3 + 1/(-3)"; demo(s, "运算式中可以有空格");//1.5 3/2
	s = "3/(-2)"; demo(s, "负号需要用括号括起来");//-1.5 -3/2
	s = "1-(1+2)*3"; demo(s, "末尾可以不加\"=\"符号");//-8
	s = "(1+2)*3="; demo(s, "末尾可以加\"=\"符号");//9
	s = "2/{[1-(1+2)]*3}="; demo(s, "可以使用圆括号,方括号和花括号");//-0.333 -1/3
	s = "10-3*(2/1-(6*2+(21+3/5)*8/3)*(-2))+8*2"; demo(s, "括号嵌套");//-397.6
	printf("\n");

	printf("##数学函数示例:\n");
	s = "pow(2,3)"; demo(s, "乘方函数示例,2的3次方");//8
	s = "log(2,8)"; demo(s, "对数函数示例,以2为底取8的对数");//3
	s = "ln(4)"; demo(s, "以自然对数e=2.7182..为底的对数函数示例");//1.38629
	s = "sqrt(36)"; demo(s, "平方根函数示例,36的平方根");//6
	s = "lcm(9,12)"; demo(s, "最大公约数函数示例");//3
	s = "gcd(9,12)"; demo(s, "最小公倍数函数示例");//36
	printf("\n");

	printf("##三角函数示例:\n");
	s = "sin(30')"; demo(s, "使用sin,cos和tan函数参数类型为弧度,注意加'(角度转弧度)标识符");//0.5
	s = "cos(60')"; demo(s);//0.5
	s = "arc'(arccos(0.5))"; demo(s, "使用arcsin,arccos和arctan函数运算结果为弧度,注意加arc'(弧度转角度)函数");//60
	printf("\n");

	printf("##特殊函数示例:\n");
	s = "hex(9*3)"; demo(s, "十六进制输出函数示例");//27 1b
	s = "radix(20,cos(45'))"; demo(s, "结果保留20位小数输出,此程序三角函数,开方函数和对数函数的精度最低为1e-12");
	s = "isprime(30+1)"; demo(s, "判断数是否为质数,对大于等于1e9的数采用10000次费马测试方法");//true
	printf("\n");

	printf("##自定义变量示例:(注:程序会在运算过程中依次循环产生A-Z变量,计算时可以使用这些变量)\n");
	s = "pi=3.14159"; demo(s, "定义变量pi");
	s = "r=50.2"; demo(s, "定义变量r");
	s = "2*pi*r"; demo(s, "使用变量pi和r");
	s = "var"; demo(s, "查看已定义变量");
	printf("\n");

	SYMBOLDEBUG = true;
}

bool SpecialCMD(string &s) {
	//去除所有空格
	char *tmp = new char[s.size()]; unsigned int i = 0, j = 0;
	for (; i < s.size(); ++i)if (s[i] != ' ')tmp[j++] = s[i];
	tmp[j] = '\0';
	s = (string)tmp;

	if (s == "")return true;
	if (s == "cls") {//清屏
		system("cls"); return true;
	}
	if (s == "calc") {//调用系统计算器
		system("calc"); return true;
	}
	if (isLtr(s[0])) {//变量赋值
		int pos = 0;
		string var = getVar(s, pos);
		if (pos != -1 && (s[pos + 1] == '=')) {
			cache.set(var, Calc(s.substr(pos + 2, s.size() - pos - 2), false));

			return true;
		}
	}
	if (getVar(s, 0) == "hex") {//十六进制输出
		printHex(Calc(s.substr(4, s.size() - 5), false)); return true;
	}
	if (getVar(s, 0) == "radix") {//以n位小数形式输出
		int pos = 6; unsigned int n = (unsigned int)getFigure(s, pos);
		printRadix(Calc(s.substr(pos + 2, s.size() - pos - 3), false), n);

		return true;
	}
	if (getVar(s, 0) == "isprime") {//判断数字是否为质数
		double ans = Calc(s.substr(7), false);
		printf(isPrime(ans) ? "\t%I64d true\n" : "\t%I64d false\n", (long long)ans);

		return true;
	}
	if (s == "debugon") {//打开dubug
		SYMBOLDEBUG = true; return true;
	}
	if (s == "debugoff") {//关闭debug
		SYMBOLDEBUG = false; return true;
	}
	if (s == "help") {//打开帮助信息
		printf(helpInf); return true;
	}
	if (s == "var") {//打印全部自定义变量
		cache.printAll(); return true;
	}
	if (s == "demo") {//显示示例
		demo(); return true;
	}

	return false;
}

int main() {
	printf("输入\"help\"获取帮助信息...\n");

	string s;
	while (printf(">"), getline(cin, s)) {
		try {
			if (!SpecialCMD(s)) Calc(s);
		}
		catch (exception &e) {
			cout << "\t" << e.what() << endl;
		}
	}

	return 0;
}