//
//	Created by ABacker on 6/14/2016
//

#include<stack>
#include<string>
#include<cstring>
#include<iostream>

using namespace std;

stack<char>OPTR;
stack<double>OPND;

template<typename _Ty>_Ty GetTop(stack<_Ty>&stack, bool pop) {
	if (stack.empty()) throw - 1;
	if (!pop)return stack.top();

	_Ty tmp = stack.top();
	stack.pop();

	return tmp;
}

double GetFigure(const string &expression, unsigned int &pos) {
	double num = 0; int deci = 0;
	for (; pos < expression.length(); ++pos) {
		if (expression[pos] >= '0'&&expression[pos] <= '9') {
			if (!deci) { num *= 10; num += expression[pos] - '0'; }
			else num += (expression[pos] - '0') / pow(10, deci++);
		}
		else if (expression[pos] == '.') deci = 1;
		else { --pos; break; }
	}

	return num;
}

bool isOPTR(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

int Prio(char c) {
	if (c == '+' || c == '-')return 1;
	if (c == '*' || c == '/' || c == '%')return 2;

	return 0;
}

void Calc(stack<char>&OPTR, stack<double>&OPND) {
	char sym = GetTop(OPTR, true);

	double ans = 0, b = 0, a = 0;
	b = GetTop(OPND, true);
	a = GetTop(OPND, true);

	switch (sym) {
	case '+':ans = a + b; break;
	case '-':ans = a - b; break;
	case '*':ans = a * b; break;
	case '/':ans = a / b; break;
	case '%':ans = (double)((long long)(a + 0.5) % (long long)(b + 0.5)); break;
	default:throw - 1;
	}

	cout << "\t" << a << " " << sym << " " << b << " " << "=" << " " << ans << endl;

	OPND.push(ans);
}

double Calc(const string &expression) {
	while (!OPTR.empty())OPTR.pop();
	while (!OPND.empty())OPND.pop();

	OPTR.push('=');

	for (unsigned int i = 0; i < expression.length(); ++i) {
		if (expression[i] == '=' || expression[i] == ' ')continue;
		else if (expression[i] == '(') OPTR.push('(');
		else if (expression[i] == ')') {
			while (GetTop(OPTR, false) != '(') Calc(OPTR, OPND);

			GetTop(OPTR, true);
		}
		else if (expression[i] >= '0'&&expression[i] <= '9')OPND.push(GetFigure(expression, i));
		else if (isOPTR(expression[i])) {
			while (Prio(expression[i]) <= Prio(GetTop(OPTR, false))) Calc(OPTR, OPND);

			OPTR.push(expression[i]);
		}
		else throw - 1;
	}

	while (GetTop(OPTR, false) != '=')Calc(OPTR, OPND);

	if (OPTR.size() > 1 || OPND.size() != 1)throw - 1;

	return OPND.top();
}

#include<set>

class IntSet {
public:
	virtual void Insert(int value) {
		data.insert(value);
	}
	void Delete(int value) {
		data.erase(value);
	}
	void Print() {
		if (!data.empty()) {
			auto it = data.begin();
			cout << *(it++);
			for (; it != data.end(); ++it)cout << "," << *it;
		}
		cout << endl;
	}
	bool IsContain(int value) {
		return data.find(value) != data.end();
	}
protected:
	multiset<int>data;
};

class PureIntSet:public IntSet {
public:
	void Insert(int value) {
		if (data.find(value) == data.end())data.insert(value);
	}
private:
};

void test() {
	int a1[] = { 2,1,7,2 }, a2[] = { 1,6,8 };
	IntSet  S1, *ptr;
	PureIntSet  S2;

	ptr = &S1;
	ptr->Print();//输出为空
	ptr->Insert(3);
	ptr->Insert(3);
	ptr->Insert(5);
	ptr->Insert(3);
	ptr->Insert(5);

	ptr->Print();//输出为 3，3，5，5，3
	if (ptr->IsContain(5))
		cout << "the element  is in the set" << endl;
	else
		cout << "the element  is not in the set" << endl;

	ptr->Delete(3);
	ptr->Print();//输出为 5，5

	ptr = &S2;
	ptr->Print();//输出为空
	ptr->Insert(3);
	ptr->Insert(5);
	ptr->Insert(3); //实际插入不成功，因3已在集合中
	ptr->Print();//输出为3，5
	if (ptr->IsContain(7))
		cout << "the element  is in the set" << endl;
	else
		cout << "the element  is not in the set" << endl;
	ptr->Delete(3);
	ptr->Print();//输出为5
}

int main(){
	test();
	string exp;
	while (true) {
		try {
			printf(">");
			getline(cin, exp);
			cout << "\t" << Calc(exp) << endl;
		}
		catch (...) {
			printf("\t表达式错误!\n");
		}
	}

    return 0;
}