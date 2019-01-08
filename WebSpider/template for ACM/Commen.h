#pragma once

#ifndef _COMMEN_WEB_SPIDER_
#define _COMMEN_WEB_SPIDER_

#include <string>
#include <time.h>
#include <mutex>
#include "HashString.h"

using namespace std;

#define MAXOFWEBS 100000
#define MAXOFTHREADS 30

mutex mtx; 
int finished = 0; 
clock_t start; 
HashString m(MAXOFWEBS << 1);


bool find_kmp(const string &s,const string &subs, int *next){
	int cnt = 0, len1 = s.size(), len2 = subs.size();
	for (int i = 0; i<len1; ++i){
		if (cnt > 0 && s[i] != subs[cnt])cnt = next[cnt];
		else if (s[i] == subs[cnt])++cnt;

		if (cnt == len2)return true;
	}
	return false;
}

/*void getNext(const char *subs, int *next, int len){
	next[0] = 0; int k;
	for (int i = 1; i < len; i++){
		k = next[i - 1];
		while (subs[i] != subs[k] && k != 0)
			k = next[k - 1];

		if (subs[i] == subs[k])next[i] = k + 1;
		else next[i] = 0;
	}
}*/

void getNext(const string &subs, int *next){
	next[0] = 0; int k; int len = subs.size();
	for (int i = 1; i < len; i++){
		k = next[i - 1];
		while (subs[i] != subs[k] && k != 0)
			k = next[k - 1];

		if (subs[i] == subs[k])next[i] = k + 1;
		else next[i] = 0;
	}
}


#endif;