//Template for ACM


#include <stack>
#include <string>
#include <iostream>

#include "Calc.h"
#include "Commen.h"

using namespace std;


//矩阵乘法
void test_1() {
}

//矩阵连乘

Matrix<BigInt>*matrix; int n;
#define INF 0x7fffffffffffffff
stack<char>OPTR;
stack<Matrix<BigInt>>OPND;

void Calc() {
	char c = GetTop(OPTR);
	Matrix<BigInt>b = GetTop(OPND), a = GetTop(OPND);
	if (c == '+')OPND.push(a + b);
	else if (c == '-')OPND.push(a - b);
	else if (c == '*')OPND.push(a * b);
	else throw exception("Error:Wrong Expression!");
	OPND.top().print(true);
}

inline int Prio(char c) {
	if (c == '+' || c == '-')return 1;
	else if (c == '*')return 2;
	else return 0;
}

Matrix<BigInt> Calc(string s) {
	while (!OPTR.empty())OPTR.pop();
	while (!OPND.empty())OPND.pop();

	OPTR.push('#');

	for (unsigned int i = 0; i < s.size(); ++i) {
		if (s[i] == ' ')continue;
		else if (isCap(s[i])) OPND.push(matrix[s[i] - 'A']);
		else if (s[i] == '(')OPTR.push('(');
		else if (s[i] == ')') {
			while (GetTop(OPTR, false) != '(')
				Calc();
			GetTop(OPTR);
		}
		else {//符号
			while (Prio(s[i]) <= Prio(GetTop(OPTR, false))) {
				Calc();
			}OPTR.push(s[i]);
		}
	}
	while (GetTop(OPTR, false) != '#') Calc();

	if (OPTR.size() > 1 || OPND.size() > 1)throw exception("Error:Wrong Expression!");

	return GetTop(OPND, false);
}

//递归的方式来把最小乘数的表达式输出
void print_chain(int i, int j, int **s, string &str) {
	if (i == j) {
		//printf("%c", 'A' + i);
		str += 'A' + i;
	}
	else {
		//printf("(");
		str += '(';
		print_chain(i, s[i][j], s, str);
		print_chain(s[i][j] + 1, j, s, str);
		//printf(")");
		str += ')';
	}
}
void test_2(int n = -1) {
	if (n == -1) cin >> n;
	matrix = new Matrix<BigInt>[n]; 

	for (int i = 0; i < n; ++i) {
		printf("Input Matrix %c's size:\n", 'A' + i);
		int n, m; cin >> n >> m;
		/*if (i>0 && n != matrix[i - 1].m) {
			printf("size mismatch,re-input:\n");
			--i; continue;
		}*/
		matrix[i].resize(n, m);

		printf("Input Matrix %c's contents:\n", 'A' + i);
		//readMarix(matrix + i);
	}
	printf("\n");
	//for (int i = 0; i < n; ++i)matrix[i].print(true);

	//矩阵连乘
	bool flag = true;string str;
	for (int i = 1; i < n; ++i) {
		if (matrix[i].n != matrix[i - 1].m)flag = false;
	}
	if (flag) {
		long long **dp = new long long*[n];
		int **s = new int*[n];
		for (int i = 0; i < n; ++i) {
			dp[i] = new long long[n];
			s[i] = new int[n];
		}
		for (int i = 0; i < n; ++i)dp[i][i] = 0;
		for (int r = 2; r <= n; ++r) {
			for (int i = 0; i <= n - r; ++i) {
				int j = i + r - 1;
				dp[i][j] = INF;
				for (int k = i; k < j; ++k) {
					long long tmp = dp[i][k] + dp[k + 1][j] + matrix[i].n*(matrix[k + 1].n*matrix[j].m);
					if (tmp < dp[i][j]) {
						dp[i][j] = tmp;
						s[i][j] = k;
					}
				}
			}
		}
		printf("%I64d\n", dp[0][n - 1]);

		print_chain(0, n - 1, s, str);
		cout << str << endl;
	}

	//分析算式
	while (1) {
		cin >> str;
		if (str == "q")break;
		Matrix<BigInt>res = Calc(str);

		printf("result:\n");
		res.print();
	}
}

int main() {
	while (1) {
		try {
			test_2();
		}
		catch (exception &e) {
			cout << e.what() << endl;
		}
	}
	return 0;
}
/*
3
3 2
1 2 3 4 5 6
2 5
1 2 3 4 5 6 7 8 9 10
5 4
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
/////
4 50 10 10 40 40 30 30 5
/////
4
2 3
1 2 3 4 5 6
2 3
1 2 3 4 5 6
3 1
1 2 3
1 5
1 2 3 4 5
(A+B)*C*D
*/