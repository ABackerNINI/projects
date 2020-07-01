
#include<conio.h>
#include<string>
#include<iterator>
#include<algorithm>
#include<hash_set>
#include<string.h>
#include<queue>
#include<map>
#include<iostream>

#include "analyse.h"
#include "download.h"

using namespace std;


struct URL{
	int deep;
	string url;
	URL(string url, int deep) :url(url), deep(deep){}
};

map<string, bool>m; int CNT = 1; Download dld; Analyse als;

void getURLs(string &content, queue<URL>&q){
	char href[] = "a href=\"http"; int cnt = 0; string url = "http";
	for (int i = 0; i < content.size(); ++i){
		if (content[i] == href[cnt])++cnt;
		else cnt = 0;

		if (cnt == 12){
			for (int j = i + 1; j<content.size() && content[j] != '"' && content[j] != '\n'; ++j, ++i)url += content[j];
			if (!m[url] && CNT <= 10000000 && checkTime(url)){ q.push(URL(url, q.front().deep + 1)); m[url] = true; ++CNT; }
			cnt = 0; url = "http";
		}
	}
}

void bfs(string s){
	queue<URL>q; int count = 0;
	q.push(URL(s, 0)); m[s] = true;
	while (!q.empty()){
		string content = dld.download(q.front().url);

		cout << count++ << " " << q.front().deep << " " << content.size() << " " << q.front().url << endl;
		getURLs(content, q); als.analyse(content);

		if (count % 10 == 0){
			freopen("out.txt", "w", stdout);
			printf("%d\n", count);
			als.print();
			freopen("CON", "w", stdout);
		}
		q.pop();
	}
}

int main(){
	DWORD startTime = GetTickCount();
	char *URL = "finance.baidu.com";//"finance.sina.com.cn";//"finance.ifeng.com";//"business.sohu.com";//"finance.qq.com";//³õÊ¼µÄURL

	bfs(URL);

	als.print();

	printf("Done! %ds\n", (GetTickCount() - startTime) / 1000);

	return 0;
}


