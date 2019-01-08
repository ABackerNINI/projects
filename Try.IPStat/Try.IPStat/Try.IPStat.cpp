// Try.IPStat.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "string.h"
#include "conio.h"
#include "windows.h"
#include "IPStat.h"

#define debug 0

using namespace std;

int main()
{
#if debug
	DWORD START = GetTickCount();
	string ipTxt = "D:\\MyCodes\\C++\\2015\\C++��ҵ\\IP��ַ�б���ٷ���ͳ��\\template for ACM\\ip.txt";
	string subnetTxt = "D:\\MyCodes\\C++\\2015\\C++��ҵ\\IP��ַ�б���ٷ���ͳ��\\template for ACM\\subnet.txt";
	string resultTxt = "D:\\MyCodes\\C++\\2015\\C++��ҵ\\IP��ַ�б���ٷ���ͳ��\\template for ACM\\result.txt";
#else
	string ipTxt = "ip.txt";
	string subnetTxt = "subnet.txt";
	string resultTxt = "result.txt";
#endif

	IPStat ipstat = IPStat();
	if (!ipstat.calc(ipTxt, subnetTxt, resultTxt))
		printf("ERROR ON READING OR WRITING FILE(S)!\n");
	else
	{
		resultTxt = (string)"type " + resultTxt;
		system(resultTxt.data());
		printf("\nOK!\n");
	}

#if debug
	printf("\ndone in %dms~\n", GetTickCount() - START);
#endif
	getch();

	return 0;
}

