#pragma once

#ifndef _URL_WEB_SPIDER_
#define _URL_WEB_SPIDER_

#include <string>
#include <vector>

#include "commen.h"

using namespace std;
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
				if (!m[url.c_str()]){
					q.push(URL(url, deep));
					m.Insert(url.c_str());
				}
				mtx.unlock();
			}
			cnt = 0; url = "http";
		}
	}
}

#endif;