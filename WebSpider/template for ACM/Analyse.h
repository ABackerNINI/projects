#pragma once

#ifndef _STRING_WEB_SPIDER_
#define _STRING_WEB_SPIDER_

#include<stack>
#include<string>
#include<iostream>

#include <mutex>
#include "commen.h"

#pragma warning(disable:4018)
#pragma warning(disable:4996)

using namespace std;

#define KEYN 10

const static string keys[KEYN] = { "金融", "电信","能源","物流","地产","互联网","医疗","电力","环保","交通" };

class Analyse{
public:
	Analyse(){
		memset(weight, 0, sizeof(weight));
		for (int i = 0; i < KEYN; ++i){
			getNext(keys[i].c_str(), next[i]);
		}
	}

	void print(){
		for (int i = 0; i < KEYN; ++i)cout << keys[i] << " " << weight[i] << endl;
	}
	void fprt(){
		try{
			FILE *resTxt = fopen("result.txt", "a");
			fprintf(resTxt, "%d:\n", finished);
			for (int i = 0; i < KEYN; ++i)
				fprintf(resTxt, "%s:%d\n", keys[i].c_str(), weight[i]);
			fprintf(resTxt, "----------%d/s------------", finished / ((clock() - start) / CLOCKS_PER_SEC + 1));
			fclose(resTxt);
		}
		catch (...){}
	}
	void analyse(const char *content){
		for (int i = 0; i < KEYN; ++i){
			if (find_kmp(content, keys[i], next[i]))++weight[i];
		}
	}

private:
	int weight[KEYN]; int next[KEYN][10];
};


#endif