#pragma once

#ifndef _CALC_CACHE_ABACKER_
#define _CALC_CACHE_ABACKER_

#include <iostream>

using namespace std;

#pragma warning(disable:4996)

bool doubleToFraction(double val);

//缓存之前的计算结果,并将其映射为大写字母
class Cache{
public:
	Cache(){ cur = -1; memset(used, 0, sizeof(used)); }

	//设置字符c的映射等于val
	void Set(char c,const double &val){
		data[c - 'A'] = val;
	}

	//获取字符c的映射
	const double &Get(char c){
		if (!used[c - 'A']){
			char e[30]; sprintf(e, "Error:'%c' Is NOT Initialized!", c);
			throw exception(e);
		}
		return data[c - 'A'];
	}

	//缓存val,并将其映射为大写字母
	void Push(const double &val){
		data[(++cur) % 26] = val; used[cur] = 1;
	}

	//输出上一次缓存的映射关系
	void PrintLastPush(){
		cout << "\t" << char(cur + 'A') << "->"<< data[cur % 26];
		doubleToFraction(data[cur % 26]);
		cout << endl;
	}

	//输出所有映射关系
	void PrintAll(){
		for (int i = 0, j = 0; i < 26; ++i){
			if (used[i]){
				cout << "\t" << char(i + 'A') << ": " << data[i];
				doubleToFraction(data[i]);
				++j;
			}
			if ((j + 1) % 7 == 0)cout << endl;
		}cout << endl;
	}
private:
	int cur; double data[26]; bool used[26];
};

#endif;