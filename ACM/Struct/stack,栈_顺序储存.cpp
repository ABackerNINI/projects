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

//默认构造函数,copy和move构造函数,析构函数;copy和move赋值运算符;
//与vector空间处理方式相似,当空间不足时自增一倍;
template<typename DataType>class Stack{
public:
	Stack(int capacity = 128) :capacity(capacity){
		data = new DataType[capacity];
		size = 0;
	}
	Stack(const Stack<DataType>&stack){
		*this = stack;
	}
	Stack(Stack<DataType>&&stack){
		*this = std::move(stack);
	}

	Stack &operator=(const Stack<DataType>&stack){
		data = new DataType[capacity = stack.capacity];
		memcpy(data, stack.data, sizeof(DataType)*stack.size);

		return *this;
	}
	Stack &operator=(Stack<DataType>&&stack){
		std::swap(data, stack.data);
		size = stack.size;
		capacity = stack.capacity;

		return *this;
	}

	void Push(const DataType &val){
		if (size == capacity)Fit();
		data[size++] = val;
	}
	void Pop()throw(out_of_range){
		if (--size == -1)throw out_of_range("Error:Pop with Stack being empty!");
	}

	const DataType &Top(){
		return data[size];
	}

	bool Empty(){
		size == 0;
	}
	void Clear(){
		size = 0;
	}
	int Size(){
		return size;
	}
	int Capacity(){
		return capacity;
	}

	~Stack(){
		if (data)delete[]data;
	}

	//debug
	void Print(){
		for (int i = 0; i < size; ++i){
			printf("\t%d", data[i]);
		}printf("\n");
	}
	
private:
	DataType *data; int size, capacity;

	void Fit(){
		DataType *tmp = new DataType[capacity <<= 1];
		memcpy(tmp, data, sizeof(DataType)*size);
		delete[]data; data = tmp;
	}
};

int main(){
	/*Stack<int>s;

	int n;
	while (printf(">"), ~scanf("%d", &n)){
		if (n == 0)break;
		
		if (n < -1){ printf("Error Input!\n"); continue; }

		try{
			if (n>0)s.Push(n);
			else if (n == -1)s.Pop();

			s.Print();
		}
		catch (exception &e){
			cout << e.what() << endl;
		}
	}*/

	return 0;
}