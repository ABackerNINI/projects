//Template for ACM

#define ll long long
#define INF 0x7FFFFFFF
#define LINF 0x7FFFFFFFFFFFFFFF

#include "stdio.h"
#include "stdlib.h"

#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN ()

struct Point{
	ll x, y;
};

//�жϵ�p��ֱ��p1-p2����߻����ұ�
//����:>0,���		<0,�ұ�		0,ֱ����
inline ll isLeft(const Point &p1, const Point &p2, const Point &p){
	return (p.y - p1.y)*(p2.x - p1.x) - (p.x - p1.x)*(p2.y - p1.y);
}

//�жϵ�p�Ƿ����߶�p1-p2��
//����:true,���߶���
inline bool isContain(const Point &p1, const Point &p2, const Point &p){
	if (p.x<min(p1.x, p2.x) || p.x>max(p1.x, p2.x) || p.y<min(p1.y, p2.y) || p.y>max(p1.y, p2.y))return false;
	else return true;
}

//�жϵ�p�Ƿ��ڶ����polygon��;�����polygon��n����˳ʱ�����ʱ�����
//����:1,��ͼ����		0,��ͼ����		-1,��ͼ����
int isContain(Point *polygon, int n, const Point &p){
	ll isleft = 0,tmp;
	for (int i = 0; i < n; ++i){
		if (isleft > 0){
			tmp = isLeft(polygon[i], polygon[(i + 1) % n], p);
			if (tmp < 0)return -1;
			if (tmp == 0 && isContain(polygon[i], polygon[(i + 1) % n], p))return 0;
		}
		else if (isleft < 0){
			tmp = isLeft(polygon[i], polygon[(i + 1) % n], p);
			if (tmp > 0)return -1;
			if (tmp == 0 && isContain(polygon[i], polygon[(i + 1) % n], p))return 0;
		}
		else { isleft = isLeft(polygon[i], polygon[(i + 1) % n], p); }
	}
	return 1;
}

int main(){
	Point pol[10],p;int n;
	while (~scanf("%d", &n)){
		for (int i = 0; i < n; ++i){
			cin >> pol[i].x >> pol[i].y;
		}cin >> p.x >> p.y;

		printf("%d\n", isContain(pol, n, p));
	}

	return 0;
}