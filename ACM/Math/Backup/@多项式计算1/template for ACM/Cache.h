#pragma once

#ifndef _CALC_CACHE_ABACKER_
#define _CALC_CACHE_ABACKER_

#include <iostream>

using namespace std;

class Cache{
public:
	Cache(){ cur = -1; memset(used, 0, sizeof(used)); }
	void Set(char c,const double &val){
		data[c - 'A'] = val;
	}
	void Push(const double &val){
		data[(++cur) % 26] = val; used[cur] = 1;
	}
	void PrintCur(){
		cout << "\t" << char(cur + 'A') << "->" << data[cur % 26] << endl;
	}
	void PrintData(){
		for (int i = 0, j = 0; i < 26; ++i){
			if (used[i]){
				cout << "\t" << char(i + 'A') << ": " << data[i];
				++j;
			}
			if ((j + 1) % 7 == 0)cout << endl;
		}cout << endl;
	}
	const double &Get(char c){
		if (!used[c - 'A']){
			char e[30]; sprintf(e, "Error:'%c' Is NOT Initialized!", c);
			throw exception(e);
		}
		return data[c - 'A'];
	}
private:
	int cur; double data[26]; bool used[26];
};

#endif;