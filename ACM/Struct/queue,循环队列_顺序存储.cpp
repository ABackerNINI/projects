#include "stdio.h"
#include <iostream>

using namespace std;

template<typename DataType>class Queue{
public:
	typedef Queue<DataType>queue;

	Queue(int initSize = 128) :maxsize(Fmt(initSize)){
		data = new DataType[maxsize];
		front = rear = size = 0;
	}
	Queue(const queue &q) :maxsize(0), data(NULL){
		*this = q;
	}
	Queue(queue &&q){
		*this = std::move(q);
	}

	queue &operator=(const queue &q){
		if (maxsize < q.maxsize){
			if (data)delete[]data;
			data = new DataType[q.maxsize];
			maxsize = q.maxsize;
		}
		int mod = Mod();
		for (int i = 0; i < q.size; ++i){
			data[i] = q.data[(i + q.front)&mod];
		}front = 0; rear = size = q.size;
		return *this;
	}
	queue &operator=(queue &&q){
		swap(data, q.data);
		size = q.size;
		maxsize = q.maxsize;
		front = q.front;
		rear = q.rear;
		return *this;
	}

	void Push(const DataType &val){
		if (size == maxsize) Fit();

		data[rear] = val;
		++rear; ++size;
		if (rear == maxsize)rear = 0;
	}
	void Push(DataType &&val){
		if (size == maxsize) Fit();

		data[rear] = std::move(val);
		++rear; ++size;
		if (rear == maxsize)rear = 0;
	}
	void Pop(){
		if (size == 0)throw out_of_range("Error:Queue is empty!");

		++front; --size;
		if (front == maxsize)front = 0;
	}

	const DataType &Front(){
		if (size == 0)throw out_of_range("Error:Queue is empty!");

		return data[front];
	}

	int Size(){
		return size;
	}
	bool Empty(){
		return size == 0;
	}
	void Clear(){
		front = rear = size = 0;
	}

	//debug
	void Print(){
		int mod = Mod();
		for (int i = 0; i < size; ++i){
			printf("\t%d", data[(front + i)&mod]);
		}printf("\n");
	}

	~Queue(){ 
		if (data)delete[]data;
	}
private:
	void Fit(){
		int mod = Mod();
		DataType *tmp = new DataType[maxsize << 1];
		for (int i = 0; i < size; ++i){
			tmp[i] = data[(front + i)&mod];
		}front = 0; rear = size;

		delete[]data;

		data = tmp;
		maxsize <<= 1;
	}
	int Mod(){
		int ret = 0;
		for (int i = 0; maxsize ^ (1 << i); ++i){
			ret += (1 << i);
		}return ret;
	}
	int Fmt(int initSize){
		int tmp = 1 << 30;
		for (int i = 0; i < 30; ++i, tmp >>= 1){
			if (tmp&initSize){
				if (tmp == initSize)return tmp;
				return tmp << 1;
			}
		}
		return 1;
	}

	DataType *data; int size, maxsize; int front, rear;
};

int main(){
	/*printf("Queue�����:\n\t1.Ĭ�Ϲ��캯��,copy��move���캯��,��������;copy��move��ֵ�����;\n\t"
		"2.�ռ�ѭ������;��vector�ռ䴦��ʽ��ͬ,���ռ䲻��ʱ�ռ�����һ��,Ҳ������ʱָ������\n\t"
		"3.�ռ䳤�ȱ�֤Ϊ2^k,������ȡģ����ʱ������λ�������,�����Ч��.\n");

	Queue<int>q;

	int opt;
	while (printf(">"), ~scanf("%d", &opt)){
		if (opt == 0)break;

		if (opt<-1){ printf("Input Error!\n"); continue; }

		try{
			if (opt > 0)q.Push(opt);
			else if (opt == -1)q.Pop();

			q.Print();
		}
		catch (exception &e){
			cout << e.what() << endl;
		}
	}*/

	return 0;
}