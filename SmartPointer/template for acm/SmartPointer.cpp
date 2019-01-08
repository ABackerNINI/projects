//
//	Create by ABacker on 3/31/2016
//

#include "SmartPointer.h"

SPtr<int>_test0(SPtr<int>val) {
	SPtr<int>_val;
	_val = *val + 1;
	std::cout << *val << "  " << *_val << std::endl;

	return _val;
}

void test() {
	SPtr<int>a(3);
	SPtr<int>b = a;
	SPtr<int>c;
	SPtr<int>d = _test0(b);
	c = d;
	
	std::cout << *a << "  " << *b << "  " << *c << "  " << *d << std::endl;
}

int main() {
	test();

	return 0;
}