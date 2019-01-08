#pragma once

#ifndef _CALC_FRACTIONAL_ABACKER_
#define _CALC_FRACTIONAL_ABACKER_

#define LL long long
#define EPS 1e-10

#include <cmath>
#include <algorithm>

using namespace std;

LL gcd(LL a, LL b);

class Fraction{
public:
	Fraction(){}
	Fraction(LL fenzhi, LL fenmu) :fenzhi(fenzhi), fenmu(fenmu){ yueFen(); }
	Fraction(double val){
		Fraction L((LL)val, 1), R((LL)val + 1, 1), Mid;
		double d;
		do{
			Mid = (L + R) / (Fraction)2;
			d = (double)Mid.fenzhi / Mid.fenmu - val;
			if (d < 0)L = Mid;
			else R = Mid;
			L.Print(); R.Print(); Mid.Print();
			printf("%.15f\n", d);
		} while (d<-EPS || d > EPS);
		*this = Mid;
	}
	Fraction(int val){
		fenzhi = val; fenmu = 1;
	}
	Fraction(LL val){
		fenzhi = val; fenmu = 1;
	}

	Fraction &operator+=(Fraction &num){
		fenzhi = fenmu*num.fenzhi + fenzhi*num.fenmu;
		fenmu *= num.fenmu;
		yueFen();
		return *this;
	}
	Fraction &operator-=(Fraction &num){}
	Fraction &operator*=(Fraction &num){}
	Fraction &operator/=(Fraction &num){
		fenzhi *= num.fenmu;
		fenmu *= num.fenzhi;
		yueFen();
		return *this;
	}
	Fraction operator+(Fraction &num){
		Fraction tmp = *this;
		tmp += num;

		return tmp;
	}
	Fraction operator/(Fraction &num){
		Fraction tmp = *this;
		tmp /= num;

		return tmp;
	}

	void Print(){
		printf("%lld/%lld\n", fenzhi, fenmu);
	}

private:
	LL fenzhi, fenmu;

	void yueFen(){
		if (fenmu < 0){ fenzhi = -fenzhi; fenmu = -fenmu; }
		LL cd = gcd(min(abs(fenzhi), fenmu), max(abs(fenzhi), fenmu));
		fenzhi /= cd;
		fenmu /= cd;
	}
};

#endif;