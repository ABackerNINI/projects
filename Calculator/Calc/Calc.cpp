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
	s = "3/2 + 1/3 + 1/(-3)"; demo(s, "����ʽ�п����пո�");//1.5 3/2
	s = "3/(-2)"; demo(s, "������Ҫ������������");//-1.5 -3/2
	s = "1-(1+2)*3"; demo(s, "ĩβ���Բ���\"=\"����");//-8
	s = "(1+2)*3="; demo(s, "ĩβ���Լ�\"=\"����");//9
	s = "2/{[1-(1+2)]*3}="; demo(s, "����ʹ��Բ����,�����źͻ�����");//-0.333 -1/3
	s = "10-3*(2/1-(6*2+(21+3/5)*8/3)*(-2))+8*2"; demo(s, "����Ƕ��");//-397.6
	printf("\n");

	printf("##��ѧ����ʾ��:\n");
	s = "pow(2,3)"; demo(s, "�˷�����ʾ��,2��3�η�");//8
	s = "log(2,8)"; demo(s, "��������ʾ��,��2Ϊ��ȡ8�Ķ���");//3
	s = "ln(4)"; demo(s, "����Ȼ����e=2.7182..Ϊ�׵Ķ�������ʾ��");//1.38629
	s = "sqrt(36)"; demo(s, "ƽ��������ʾ��,36��ƽ����");//6
	s = "lcm(9,12)"; demo(s, "���Լ������ʾ��");//3
	s = "gcd(9,12)"; demo(s, "��С����������ʾ��");//36
	printf("\n");

	printf("##���Ǻ���ʾ��:\n");
	s = "sin(30')"; demo(s, "ʹ��sin,cos��tan������������Ϊ����,ע���'(�Ƕ�ת����)��ʶ��");//0.5
	s = "cos(60')"; demo(s);//0.5
	s = "arc'(arccos(0.5))"; demo(s, "ʹ��arcsin,arccos��arctan����������Ϊ����,ע���arc'(����ת�Ƕ�)����");//60
	printf("\n");

	printf("##���⺯��ʾ��:\n");
	s = "hex(9*3)"; demo(s, "ʮ�������������ʾ��");//27 1b
	s = "radix(20,cos(45'))"; demo(s, "�������20λС�����,�˳������Ǻ���,���������Ͷ��������ľ������Ϊ1e-12");
	s = "isprime(30+1)"; demo(s, "�ж����Ƿ�Ϊ����,�Դ��ڵ���1e9��������10000�η�����Է���");//true
	printf("\n");

	printf("##�Զ������ʾ��:(ע:��������������������ѭ������A-Z����,����ʱ����ʹ����Щ����)\n");
	s = "pi=3.14159"; demo(s, "�������pi");
	s = "r=50.2"; demo(s, "�������r");
	s = "2*pi*r"; demo(s, "ʹ�ñ���pi��r");
	s = "var"; demo(s, "�鿴�Ѷ������");
	printf("\n");

	SYMBOLDEBUG = true;
}

bool SpecialCMD(string &s) {
	//ȥ�����пո�
	char *tmp = new char[s.size()]; unsigned int i = 0, j = 0;
	for (; i < s.size(); ++i)if (s[i] != ' ')tmp[j++] = s[i];
	tmp[j] = '\0';
	s = (string)tmp;

	if (s == "")return true;
	if (s == "cls") {//����
		system("cls"); return true;
	}
	if (s == "calc") {//����ϵͳ������
		system("calc"); return true;
	}
	if (isLtr(s[0])) {//������ֵ
		int pos = 0;
		string var = getVar(s, pos);
		if (pos != -1 && (s[pos + 1] == '=')) {
			cache.set(var, Calc(s.substr(pos + 2, s.size() - pos - 2), false));

			return true;
		}
	}
	if (getVar(s, 0) == "hex") {//ʮ���������
		printHex(Calc(s.substr(4, s.size() - 5), false)); return true;
	}
	if (getVar(s, 0) == "radix") {//��nλС����ʽ���
		int pos = 6; unsigned int n = (unsigned int)getFigure(s, pos);
		printRadix(Calc(s.substr(pos + 2, s.size() - pos - 3), false), n);

		return true;
	}
	if (getVar(s, 0) == "isprime") {//�ж������Ƿ�Ϊ����
		double ans = Calc(s.substr(7), false);
		printf(isPrime(ans) ? "\t%I64d true\n" : "\t%I64d false\n", (long long)ans);

		return true;
	}
	if (s == "debugon") {//��dubug
		SYMBOLDEBUG = true; return true;
	}
	if (s == "debugoff") {//�ر�debug
		SYMBOLDEBUG = false; return true;
	}
	if (s == "help") {//�򿪰�����Ϣ
		printf(helpInf); return true;
	}
	if (s == "var") {//��ӡȫ���Զ������
		cache.printAll(); return true;
	}
	if (s == "demo") {//��ʾʾ��
		demo(); return true;
	}

	return false;
}

int main() {
	printf("����\"help\"��ȡ������Ϣ...\n");

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