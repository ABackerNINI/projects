
#include<map>
#include<conio.h>
#include<string>
#include<queue>
#include<iostream>

#include "url.h"
#include "analyse.h"
#include "commen.h"
#include "Socket.h"
#include <thread>

using namespace std;

Analyse Als;
URL_QUEUE q;

void *BFS(int id){
	URL_QUEUE::URL front;
	Download *dld;
	try{
		dld = new Download();
	}
	catch (exception &e){ cout << "thread" << id << ":" << e.what() << endl; return NULL; }
	while (1){
		if (!q.Empty()) { front = q.Front(true); }
		else { printf("thread%d:queue is empty!\n", id); std::this_thread::sleep_for(std::chrono::milliseconds(1000));  continue; }

		char *content;
		try{ content = dld->DLoad(front.url.c_str()); }
		catch (exception &e){ cout << "thread" << id << ":" << e.what() << endl; continue; }

		q.GetURL(content, front.deep + 1);
		Als.analyse(content);

		mtx.lock();
		if (finished % 20 == 0){
			Als.print(); Als.fprt();
		}
		printf("%04d %02d %2d %6d %s\n", ++finished, front.deep, id, strlen(content), front.url.c_str());
		mtx.unlock();

		if (finished > MAXOFWEBS)break;
	}
	return NULL;
}

int main(){
	string pURL; int n; cin >> n;

	for (int i = 0; i < n; ++i){ cin >> pURL; q.Push(URL_QUEUE::URL(pURL, 0)); m.Insert(pURL.c_str()); }
	start = clock();

	vector<thread>threads;
	for (int i = 0; i < MAXOFTHREADS; ++i){
		threads.push_back(thread(BFS, i));
	}
	for (int i = 0; i < threads.size(); ++i)threads[i].join();

	Als.print(); Als.fprt();
	system("pause");

	return 0;
}


