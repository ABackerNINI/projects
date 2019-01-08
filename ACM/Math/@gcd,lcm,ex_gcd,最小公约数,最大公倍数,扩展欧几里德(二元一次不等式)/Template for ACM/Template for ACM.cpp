//Template for ACM

#define LL long long
#define INF 0x7FFFFFFF
#define LINF 0x7FFFFFFF7FFFFFFF

#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN ()

//要求:a,b不为0;|a|<|b|
//返回:若b为负,则返回负值
LL gcd_1(LL a, LL b) {
	return a == 0 ? b : gcd_1(b%a, a);
}

//要求:a,b不为0
//返回:正值
LL gcd_2(LL a, LL b) {
	if (abs(a) > abs(b))swap(a, b);

	LL t;
	while (a != 0) {
		t = a;
		a = b%a;
		b = t;
	}
	return abs(b);
}

//要求:a,b不为0
//返回:正值
LL lcm(LL a, LL b) {
	return abs(a / gcd_2(a, b)*b);
}

//解不定式ax+by=1
//x,y为一组特解
//通解:x=x0-bt y=y0+at (t为任意整数)
void extended_gcd(LL a, LL b, LL &x, LL &y) {
	if (b == 0) {
		x = 1;
		y = 0; //any integer is ok;
	}
	else {
		LL t;
		extended_gcd(b, a%b, x, y);
		t = x;
		x = y;
		y = t - (a / b)*y;
	}
}

//乘法逆元:给出2个数M和N(0< M < N),且M与N互质,找出一个最小正数K满足(K * M) % N = 1
void test_1() {
	LL m, n,x,y; 
	
	while (1) {
		cin >> m >> n;
		extended_gcd(m, n, x, y);

		x %= n;
		if (x <= 0) x += n;

		cout << x << endl;
	}
}

int main() {
	test_1();

	return 0;
}