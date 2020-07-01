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

map<string, bool>m;

bool CheckTime(string &URL){
	char t[] = "/2015"; int cnt = 0;
	for (int i = 0; i < URL.size(); ++i){
		if (URL[i] == t[cnt])++cnt;
		else cnt = 0;

		if (cnt == 5){
			if (i + 5 < URL.size() && URL[i + 5] == '/')return true;
			else cnt = 0;
		}
	}
	return false;
}

void GetURL(const char *content, queue<URL>&q, int deep){
	if (finished + q.size() > MAXOFWEBS)return;

	const static char href[] = "a href=\"http"; int cnt = 0, len = strlen(content); string url = "http";
	for (int i = 0; i < len; ++i){
		if (content[i] == href[cnt])++cnt;
		else cnt = 0;

		if (cnt == 12){
			for (int j = i + 1; url.size() < 100 && j < len && content[j] != '"' && content[j] != '\n'; ++j, ++i)url += content[j];

			if (finished + q.size() < MAXOFWEBS&& CheckTime(url)){
				mtx.lock();
				if (!m[url]){ 
					q.push(URL(url, deep));
					m[url] = true; 
				}
				mtx.unlock();
			}
			cnt = 0; url = "http";
		}
	}
}

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