#pragma once

#ifndef _STRING_WEB_SPIDER_
#define _STRING_WEB_SPIDER_

#include<string>
#include<iostream>

using namespace std;

bool checkTime(string &URL){
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

#define KEYN 10

string keys[KEYN] = { "金融", "电信","能源","物流","地产","互联网","医疗","电力","环保","交通" };

class Analyse{
public:
	Analyse(){
		memset(weight, 0, sizeof(weight));
	}

	void print(){
		for (int i = 0; i < KEYN; ++i)cout << keys[i] << " " << weight[i] << endl;
	}

	void analyse(const string &content){
		int cnt = 0;
		/*char div[] = "<div";  int L = 0, R = 0;
		char enddiv[] = "</div>";

		for (int i = 0; i < content.size(); ++i){
			if (content[i] == div[cnt])++cnt;
			else cnt = 0;

			if (cnt == 4){
				L = ++i; cnt = 0;
				for (R = L; R < content.size(); ++R, ++i){
					if (content[R] == enddiv[cnt])++cnt;
					else cnt = 0;

					if (cnt == 6){
						break;
					}
				}
				if (R - L>2000)break;
				cnt = 0;
			}
		}*/

		//cout << content.substr(L, R) << endl;

		for (int i = 0; i < KEYN; ++i){
			cnt = 0;
			for (int j = 0; j < content.size(); ++j){
				if (content[j] == keys[i][cnt])++cnt;
				else cnt = 0;

				if (cnt == keys[i].size()){ ++weight[i]; cnt = 0; }
			}
		}
	}

private:
	int weight[10];
};

class KMP
{
public:
	//计算subs在s中出现的次数
	int search(char *s, const char *subs, int *next){
		int cnt = 0, ret = 0, len = strlen(subs); Next(subs, next, len); --s;
		while (*++s){
			if (cnt > 0 && *s != subs[cnt]){
				cnt = next[cnt];
			}
			else if (*s == subs[cnt])++cnt;

			if (cnt == len){
				++ret;
				cnt = next[cnt - 1];
			}
		}
		return ret;
	}

private:
	void Next(const char *s, int *next, int len = -1){
		if (len == -1)len = strlen(s);

		next[0] = 0; int k;
		for (int i = 1; i < len; i++){
			k = next[i - 1];
			while (s[i] != s[k] && k != 0)
				k = next[k - 1];

			if (s[i] == s[k])next[i] = k + 1;
			else next[i] = 0;
		}
	}
};


#endif