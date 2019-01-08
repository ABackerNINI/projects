// template for ACM.cpp
//

#include "stdio.h"
#include <stdlib.h>//定义杂项函数及内存分配函数
#include <math.h>
#include <string.h>

#include <iostream>//数据输入输出流
#include <string>//c++中的string类 他不能用strcpy等c函数去操作
#include <vector>//STL vetor
/*#include <list>//STL list
#include <map>// STL map
#include <queue>// STL queue
#include <stack>//sTL stack
#include <bitset>//bitset可按位定义串//比如：bitset <1000> all;定义一个1000位的串
#include <algorithm>//STL各种算法 比如 swap sort merge max min 比较
#include <numeric>//常用数字操作 一般和algorithm搭配使用*/
#include <conio.h>

using namespace std;

struct node
{
public:
	int value;
	node* next;

	node(){ next = NULL; }//constructor
	node(int val){ value = val; next = NULL; }//constructor
};


class List
{
public:
	node* addNode(){
		
	}

	node* addNode(int pos){

		this->_size++;
	}

	int deleteNode(int pos){
		this->_size--;

		return this->_size;
	}

	int deleteNode(){
		this->_size--;

		return this->_size;
	}

	node* createList(int lenth){
		node *head,*tail;
		head = tail = (node *)malloc(sizeof(node));
		
		if (head == NULL)
			return NULL;

		int val;
		for (int i = 0; i < lenth; i++){
			//在此录入数据
			scanf("%d", &val);
			//end

			tail->next = new node(val);
			tail = tail->next;
		}

		this->head = head;
		this->tail = tail;
		this->_size += lenth;

		return head;
	}

	int size(){
		return this->_size;
	}

	node *begin(){
		return this->head->next;
	}

	node *end(){
		return NULL;
	}

	class iterator{
	public:
		iterator(){}

		node operator++(int){
			node temp = *it;
			it = it->next;
			return temp;
		}

		node &operator++(){
			it = it->next;
			return *it;
		}

		node *operator=(node *nod){
			it = nod;
			return it;
		}

		node *operator->(){
			return it;
		}

		bool operator!=(node *nod){
			if (it == nod)
				return false;
			else
				return true;
		}

	private:
		node *it;
	};

private:
	int _size = 0;
	node *head;
	node *tail;
};



int main(){
	int N = 5;

	List l;
	
	node* head = l.createList(N);
	node* tail = head;

	List::iterator it;

	for (it = l.begin(); it != l.end(); it++){
		printf("%d ", it->value);
	}

	getch();
	return 0;
}

