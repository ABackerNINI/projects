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

//Ҫ��:a,b��Ϊ0;|a|<|b|
//����:��bΪ��,�򷵻ظ�ֵ
LL gcd_1(LL a, LL b) {
	return a == 0 ? b : gcd_1(b%a, a);
}

//Ҫ��:a,b��Ϊ0
//����:��ֵ
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

//Ҫ��:a,b��Ϊ0
//����:��ֵ
LL lcm(LL a, LL b) {
	return abs(a / gcd_2(a, b)*b);
}

//�ⲻ��ʽax+by=1
//x,yΪһ���ؽ�
//ͨ��:x=x0-bt y=y0+at (tΪ��������)
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

//�˷���Ԫ:����2����M��N(0< M < N),��M��N����,�ҳ�һ����С����K����(K * M) % N = 1
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