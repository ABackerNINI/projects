
#include<map>
#include<conio.h>
#include<string>
#include<queue>
#include<iostream>

#include "analyse.h"
#include "download.h"
#include "commen.h"
#include <thread>

using namespace std;

queue<URL>q; Analyse als; 

/*URL getTop(){
	URL front;
	while (finished < MAXOFWEBS){
		mtx.lock();
		if (q.empty()){ mtx.unlock(); std::this_thread::sleep_for(std::chrono::milliseconds(1000)); }
		else { front = q.front(); q.pop(); mtx.unlock(); break; }
	}return front;
}

inline void print(int id, URL &front, string &content){
	std::lock_guard<std::mutex>lck(mtx);
	if (finished % 20 == 0){
		als.print(); als.fprt();
	}
	printf("%04d %02d %02d %6d %s\n", ++finished, front.deep, id, content.size(), front.url.c_str());
}*/

void *BFS(int id){
	Download dld; URL front;
	while (1){
		try{
			mtx.lock();
			if (!q.empty()){ front = q.front(); q.pop(); }
			else { mtx.unlock(); std::this_thread::sleep_for(std::chrono::milliseconds(1000));  continue; }
			mtx.unlock();
			string content = dld.download(front.url);
			getURLs(content, q, front.deep + 1);
			als.analyse(content);

			mtx.lock();
			if (finished % 20 == 0){
				als.print(); als.fprt();
			}
			printf("%04d %02d %2d %6d %s\n", ++finished, front.deep, id, content.size(), front.url.c_str());
			//cout << ++finished << " " << front.deep << " " << front.url << endl;
			mtx.unlock();
		}
		catch (...){}

		if (finished > MAXOFWEBS)break;
	}
	return NULL;
}

int main(){
	string pURL; int n; cin >> n;
	
	for (int i = 0; i < n; ++i){
		cin >> pURL; q.push(URL(pURL, 0)); m[pURL] = true;
	}
	start = clock();

	vector<thread>threads;
	for (int i = 0; i < MAXOFTHREADS; ++i){
		threads.push_back(thread(BFS, i));
	}
	for (int i = 0; i < threads.size(); ++i)threads[i].join();

	getch();

	return 0;
}


