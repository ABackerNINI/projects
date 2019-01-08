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

bool isCap(char c);//������Commen.h

class Cache {
public:
	Cache() :autoStrNum(0) {};
	//Ϊpush����������һ��������
	void push(double num) {
		string str;
		do {
			str = "";
			str += ((autoStrNum++) % 26) + 'A';
		} while (used[str]);

		data[str] = num;
		lastPush = str;
	}
	//��numӳ�䵽str��
	void set(const string &str, double num) {
		data[str] = num;
		used[str] = true;

		_str.push_back(str);
		lastPush = str;
	}
	//��ȡstr��Ӧ��num
	double get(const string &str) {
		if(used[str]||(str.size()==1&&isCap(str[0])))
			return data[str];
		else {
			string e = "Error: '" + str + "' is NOT initialized!";
			throw exception(e.data());
		}
	}
	//��ӡ�ϴ�push��������
	void printLastPush() {
		cout << "\t" << lastPush << " <- ";// << data[lastPush];
		printf("%.6f\t", data[lastPush]);
		doubleToFraction(data[lastPush]);
		cout << endl;
	}
	//��ӡȫ������
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