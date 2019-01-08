//
//	Created by ABacker on 6/3/2016
//

#include <iostream>
using namespace std;


class Complex {
	friend Complex operator+(const Complex &c1, double real);
	friend Complex operator+(double real, const Complex &c1);
public:
	//Complex(double real) :real(real), unreal(0) {}
	Complex(double real, double unreal) :real(real), unreal(unreal) {}

	Complex& operator+=(const Complex &right) {
		this->real += right.real;
		this->unreal += right.unreal;

		return *this;
	}
	Complex operator+(const Complex &right) {
		Complex ret = *this;
		ret += right;

		return ret;
	}
	void Print(bool isNewLine = true) {
		cout << real << "+" << unreal << "i";
		if (isNewLine)cout << endl;
	}
private:
	double real, unreal;
};

Complex operator+(const Complex &c1,double real) {
	Complex ret = c1;
	ret.real += real;

	return ret;
}
Complex operator+(double real, const Complex &c1) {
	Complex ret = c1;
	ret.real += real;

	return ret;
}

int main() {
	Complex x(3, 6), y(4, 5), z(0, 0);
	z = x + y; z.Print();
	z = 2.4 + x; z.Print();
	z = y + 3.5; z.Print();

	system("pause");
	return 0;
}