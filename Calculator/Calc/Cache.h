#pragma once

#ifndef _CALC_CACHE_ABACKER_
#define _CALC_CACHE_ABACKER_

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "Algorithm.h"

using namespace std;

#pragma warning(disable:4996)

bool isCap(char c);//定义与Commen.h

class Cache {
public:
	Cache() :autoStrNum(0) {};
	//为push进的数分配一个变量名
	void push(double num) {
		string str;
		do {
			str = "";
			str += ((autoStrNum++) % 26) + 'A';
		} while (used[str]);

		data[str] = num;
		lastPush = str;
	}
	//将num映射到str上
	void set(const string &str, double num) {
		data[str] = num;
		used[str] = true;

		_str.push_back(str);
		lastPush = str;
	}
	//获取str对应的num
	double get(const string &str) {
		if(used[str]||(str.size()==1&&isCap(str[0])))
			return data[str];
		else {
			string e = "Error: '" + str + "' is NOT initialized!";
			throw exception(e.data());
		}
	}
	//打印上次push进的数据
	void printLastPush() {
		cout << "\t" << lastPush << " <- ";// << data[lastPush];
		printf("%.6f\t", data[lastPush]);
		doubleToFraction(data[lastPush]);
		cout << endl;
	}
	//打印全部数据
	void printAll() {
		for (unsigned int i = 0; i < _str.size(); ++i) {
			cout << "\t" << _str[i] << ": " << data[_str[i]];
			if ((i + 1) % 7 == 0)cout << endl;
		}cout << endl;
	}

private:
	string lastPush;
	int autoStrNum;
	vector<string>_str;
	map<string, bool>used;
	map<string, double>data;
};

#endif;