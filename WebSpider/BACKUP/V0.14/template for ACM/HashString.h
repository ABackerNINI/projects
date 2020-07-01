#pragma once

#ifndef _HASHSTRING_WEB_SPIDER_
#define _HASHSTRING_WEB_SPIDER_

#include <string>
#include <vector>

using namespace std;

#define MAXN ()

//通过两次hash的方法将字符串是否存在的信息存储起来,IsExist(string)如果存在返回true,不存在返回false;重载了[]运算
class HashString{
public:
	HashString(int maxn) :data(NULL), maxn(maxn << 1), size(0){
		data = new vector<unsigned int>[this->maxn];
	}
	void Insert(const char *string){
		++size;
		data[Hash(string)].push_back(Key(string));
	}
	bool IsExist(const char *string)const{
		unsigned int hash = Hash(string);
		int len = data[hash].size();
		if (len > 0){
			unsigned int key = Key(string);
			for (int i = 0; i < len; ++i){
				if (data[hash][i] == key)return true;
			}
		}
		return false;

	}
	bool operator[](const char *string)const{
		return IsExist(string);
	}
	double Alpha(){
		return (double)size / maxn;
	}

	~HashString(){
		if (data)delete[]data;
	}
private:
	vector<unsigned int>*data; int maxn, size;
	const static unsigned int seed1 = 131, seed2 = 1313;

	unsigned int Key(const char *string)const{
		int len = strlen(string); unsigned int hash = 0;
		for (int i = 0; i < len; ++i){
			hash = hash*seed2 + string[i];
		}
		return hash;
	}
	unsigned int Hash(const char *string)const{
		int len = strlen(string); unsigned int hash = 0;
		for (int i = 0; i < len; ++i){
			hash = hash*seed1 + string[i];
		}
		return hash%maxn;
	}
};

#endif;