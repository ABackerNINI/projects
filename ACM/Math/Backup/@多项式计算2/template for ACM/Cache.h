#pragma once

#ifndef _CALC_CACHE_ABACKER_
#define _CALC_CACHE_ABACKER_

#include <iostream>

using namespace std;

#pragma warning(disable:4996)

bool doubleToFraction(double val);

//����֮ǰ�ļ�����,������ӳ��Ϊ��д��ĸ
class Cache{
public:
	Cache(){ cur = -1; memset(used, 0, sizeof(used)); }

	//�����ַ�c��ӳ�����val
	void Set(char c,const double &val){
		data[c - 'A'] = val;
	}

	//��ȡ�ַ�c��ӳ��
	const double &Get(char c){
		if (!used[c - 'A']){
			char e[30]; sprintf(e, "Error:'%c' Is NOT Initialized!", c);
			throw exception(e);
		}
		return data[c - 'A'];
	}

	//����val,������ӳ��Ϊ��д��ĸ
	void Push(const double &val){
		data[(++cur) % 26] = val; used[cur] = 1;
	}

	//�����һ�λ����ӳ���ϵ
	void PrintLastPush(){
		cout << "\t" << char(cur + 'A') << "->"<< data[cur % 26];
		doubleToFraction(data[cur % 26]);
		cout << endl;
	}

	//�������ӳ���ϵ
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