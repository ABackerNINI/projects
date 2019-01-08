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

template<typename Node, typename DataType>class ListIterator{
public:
	typedef ListIterator<Node, DataType>iterator;

	ListIterator(){}
	ListIterator(Node *p) :p(p){}

	DataType operator*(){
		return p->data;
	}
	DataType *operator->(){
		return &(p->data);
	}

	bool operator!=(const iterator &it) {
		return p != it.p;
	}
	bool operator==(const iterator &it){
		return p == it.p;
	}

	iterator &operator++(){//Ç°
		p = p->next;
		return *this;
	}
	iterator operator++(int){//ºó
		iterator tmp = *this;
		++tmp;
		return tmp;
	}

	iterator &operator+=(int n){
		while (n--){
			p = p->next;
		}
		return *this;
	}
	iterator operator+(int n){
		iterator tmp = *this;
		tmp += n; return tmp;
	}

private:
	Node *p;
};

template<typename DataType>class List{
private:
	struct Node{
		DataType data; Node *next;
		Node() :next(NULL){}
		Node(const DataType &data) : data(data), next(NULL){}
		Node(DataType &&data) : data(std::move(data)), next(NULL){}
	};
public:
	typedef ListIterator<Node, DataType>iterator;

	List(){
		head = new Node; 
		tail = head; 
		size = 0;
	}
	List(DataType *begin, DataType *end){
		head = new Node;
		assign(begin, end);
	}
	List(DataType *arr, int pos, int n){
		head = new Node;
		assign(arr, pos, n);
	}

	void assign(DataType *begin, DataType *end){
		assign(begin, 0, end - begin);
	}
	void assign(DataType *arr, int pos, int n){
		Clear();size = n;

		tail = head;
		while (n--){
			tail->next = new Node(arr[pos++]);
			tail = tail->next;
		}
	}


	DataType &Front(){
		return head->next->data;
	}
	DataType &Back(){
		return tail->data;
	}

	iterator operator[](int idx){
		if (idx == -1)return iterator(head);

		iterator it = Begin();
		for (int i = 0; i < idx; ++i){
			++it;
		}return it;
	}
	List &operator+=(const List &list){
		tail->next = list.head->next;
		tail = list.tail;
		return *this;
	}
	List operator+(const List &list){
		List tmp = *this;
		tmp += list;
		return tmp;
	}

	void Pop_back(int n = 1){
		if (size < n)throw out_of_range("Not enough to pop(n)");

		size -= n;
		tail = at(size);
		Clear(tail);
		tail->next = NULL;
	}
	void Pop_front(){
		if (size == 0)throw - 1;

		Node *tmp = head->next;
		head->next = tmp->next;
		delete tmp;

		--size;
		if (size == 0)tail = head;
	}
	void Push_back(const DataType &val){
		tail->next = new Node(val);
		tail = tail->next;
		++size;
	}
	void Push_front(const DataType &val){
		Node *tmp = new Node(val);
		tmp->next = head->next;
		head->next = tmp;
		++size;
	}

	void Insert(int pos, const DataType &val){
		Node *tmp = head;
		for (int i = 0; i < pos; ++i){
			tmp = tmp->next;
		}
		Node *temp = new Node(val);
		temp->next = tmp->next;
		tmp->next = temp;
		if (pos == size){
			tail = tail->next;
		}
		++size;
	}
	void Insert(int pos, DataType *arr, int n = 1){

	}
	void Insert(int pos, const List &list, int n = 1){}
	void Insert(int pos, List &&list, int n = 1){}
	void Delete(int pos){
		if (pos == size - 1){
			Pop_back();
		}
		else{
			Node *tmp = at(pos - 1);
			Node *temp = tmp->next->next;
			delete[]tmp->next;
			tmp->next = temp;
		}
	}
	void Delete(int pos, int n = 1){}

	int  Size(){
		return size;
	}
	bool Empty(){ 
		return size == 0; 
	}
	void Swap(int pos1, int pos2){}
	void Clear(){
		
	}
	void print(){
		Node *tmp = head->next;
		while (tmp != NULL){
			cout << tmp->data;//printf("%d->", tmp->data);
			tmp = tmp->next;
		}
		printf("NULL\n");
	}

	iterator Begin(){
		return iterator(head->next);
	}
	iterator End(){
		return iterator(NULL);
	}

	~List(){ Clear(); if (head)delete head; }

	//debug
	void Print(){
		iterator it;
		for (it = list.Begin(); it != list.End(); ++it){
			printf("(%d,%d)->", it->x, it->y);
		}printf("NULL\n");
	}
private:
	Node *head, *tail; int size;

	Node *at(int idx){
		if (idx == -1)return head;

		Node *tmp = head;
		for (int i = 0; i <= idx; ++i){
			tmp = tmp->next;
		}return tmp;
	}

	//delete from head->next
	void clear(Node *head){
		Node *tmp;
		tmp = tail = head->next;
		while (tail != NULL){
			tmp = tail->next;
			delete tail;
			tail = tmp;
		}tail = head; size = 0;
		tail->next = NULL;
	}
};

int arr[] = { 1, 2, 3, 4, 5, 6, 7 };


int main(){
	List<int>list; int n;
	list.assign(arr, arr + 6);

	while (printf(">"), cin >> n){
		if (n == 0)break;

		if (n < -1){ printf("Error Input!\n"); continue; }
		try{
			if (n>0){
				list.Push_back(n);
			}
			else{
				list.Pop_back();
			}
		}
		catch (exception &e){
			cout << e.what() << endl;
		}
	}

	return 0;
}