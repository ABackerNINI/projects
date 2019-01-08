//
//	Created by ABacker on 6/3/2016
//

#include <iostream>

using namespace std;

class MyString {
	friend ostream &operator <<(ostream &out, MyString &obj);
	friend istream &operator >>(istream &in, MyString &obj);
public:
	//依次为空构造函数,move构造函数,复制构造函数,参数构造函数*3
	MyString() :data(NULL) {}
	MyString(MyString &&str) {
		data = str.data;
		str.data = NULL;
	}
	MyString(const MyString &str) {
		unsigned int n = strlen(str.data) + 1;
		data = new char[n];
		memcpy(data, str.data, sizeof(char)*n);
	}
	explicit MyString(const char *str) {
		unsigned int n = strlen(str) + 1;
		data = new char[n];
		memcpy(data, str, sizeof(char)*n);
	}
	MyString(const string &str) {
		unsigned int n = str.length() + 1;
		data = new char[n];
		memcpy(data, str.data(), sizeof(char)*n);
	}
	MyString(char *&&str) {
		data = str;
		str = NULL;
	}

	MyString &operator=(MyString &&str) {
		data = str.data;
		str.data = NULL;
		return *this;
	}
	template<typename T>MyString &operator=(T &&str) {
		*this = MyString(::forward<T>(str));
		return *this;
	}

	MyString &operator+=(const MyString &str) {
		if (data) {
			unsigned int n1 = strlen(data), n2 = strlen(str.data) + 1;
			char *_data = new char[n1 + n2];
			memcpy(_data, data, sizeof(char)*n1);
			memcpy(_data + n1, str.data, sizeof(char)*n2);
			delete[]data;
			data = _data;
		}
		else { *this = str; }

		return *this;
	}
	MyString operator+(const MyString &str) const {
		MyString tmp = *this;
		tmp += str;

		return tmp;
	}

	unsigned int Lenth() const {
		return data == NULL ? 0 : strlen(data);
	}
	bool Empty()const {
		return Lenth() == 0;
	}
	const char *Data()const {
		return data;
	}
	void Print(bool isNewLine = true) const {
		printf("%s", data);
		if (isNewLine)printf("\n");
	}

	~MyString() {
		if (data)delete[]data;
	}

protected:
	char *data;
};

ostream &operator <<(ostream &out, MyString &obj) {
	out << obj.data;
	return out;
}
istream& operator >>(istream &in, MyString &obj) {
	in >> obj.data;
	return in;
}

class MyString_ex :public MyString {
public:
	MyString_ex() {
		data = NULL;
		_lenth = 0;
		++_instances;
	}
	MyString_ex(MyString_ex &&str) :MyString(::move(str)) {
		_lenth = str._lenth;
	}
	MyString_ex(const MyString_ex &str) :MyString(str) {
		_lenth = str._lenth;
		++_instances;
	}
	MyString_ex(const string &str) :MyString(str) {
		_lenth = str.length();
		++_instances;
	}
	template<typename T>MyString_ex(T &&str) : MyString(::forward<T>(str)) {//const char*;char *&&;
		_lenth = strlen(data);
		++_instances;
	}

	MyString_ex &operator=(MyString_ex &&str) {
		data = str.data;
		_lenth = str._lenth;
		str.data = NULL;
		--_instances;

		return *this;
	}
	template<typename T>MyString_ex &operator=(T &&str) {
		*this = MyString_ex(::forward<T>(str));
		return *this;
	}

	MyString_ex &operator+=(const MyString_ex &str) {
		MyString::operator+=(str);
		_lenth += str._lenth;

		return *this;
	}
	MyString_ex operator+(const MyString_ex &str) const {
		MyString_ex tmp = *this;
		tmp += str;

		return tmp;
	}

	unsigned int Lenth() const {
		return _lenth;
	}

	static unsigned int instances() {
		return _instances;
	}

	~MyString_ex() {
		if (data)--_instances;
	}
private:
	unsigned int _lenth;
	static unsigned int _instances;
};

unsigned int MyString_ex::_instances = 0;

int main() {
	char *_str = new char[20];
	strcpy(_str, "1234");

	MyString str(move(_str));
	str.Print();
	printf("%d\n", _str);

	MyString str1(move(str));
	str1.Print();

	printf("\n\n");

	/////////////////////////////////

	_str = new char[20];
	strcpy(_str, "5678");

	MyString_ex str_ex(move(_str));
	str_ex.Print();
	printf("%d\n", MyString_ex::instances());
	printf("%d\n", _str);

	MyString_ex str_ex1(move(str_ex));
	str_ex1.Print();
	printf("%d\n", MyString_ex::instances());

	MyString_ex str_ex2;
	str_ex2 = move(str_ex1);
	str_ex2.Print();
	printf("%d\n", MyString_ex::instances());

	MyString_ex str_ex3("ex3");
	str_ex3.Print();
	str_ex3 = "ex3_1";
	str_ex3.Print();
	str_ex3 += "test3";
	str_ex3.Print();
	printf("%d\n", str_ex3.Lenth());
	str_ex3 += str_ex2;
	str_ex3.Print();
	printf("%d\n", str_ex3.Lenth());
	cout << str_ex3 << endl;
	printf("%d\n", MyString_ex::instances());

	MyString_ex str_ex4;
	str_ex4 = MyString_ex(" ") + str_ex3;
	str_ex4.Print();
	printf("%d\n", str_ex4.Lenth());
	printf("%d\n", MyString_ex::instances());

	system("pause>nul");

	return 0;
}