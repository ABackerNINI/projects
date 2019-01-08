//Template for ACM

#define LL long long
#define INF 0x7FFFFFFF
#define LINF 0x7FFFFFFF7FFFFFFF

#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#include <time.h>
#include <conio.h>

using namespace std;

class Union_Find_Set {
public:
	Union_Find_Set():data(NULL) {}
	Union_Find_Set(unsigned int n) :size(n) {
		data = new int[n];
		memset(data, -1, sizeof(int)*n);
	}

	void Resize(unsigned int n) {
		if (data)delete[]data;

		size = n;
		data = new int[n];
		memset(data, -1, sizeof(int)*n);
	}

	int Find(int pos) {
		if (data[pos] < 0)return pos;
		else return data[pos] = Find(data[pos]);
	}
	void Union(int pos1, int pos2) {
		int f1 = Find(pos1);
		int f2 = Find(pos2);

		if (data[f1] > data[f2])swap(f1, f2);

		data[f1] += data[f2];
		data[f2] = f1;
	}

	~Union_Find_Set() {
		if (data)delete[]data;
	}

	//debug
	void Print() {
		for (unsigned int i = 0; i < size; ++i) {
			printf("%d ", data[i]);
		}
		printf("\n");
	}

private:
	int *data; unsigned int size;
};

#define WIDTH 4
#define HEIGHT 4

struct Pos {
	int x, y;
	Pos() {}
	Pos(int x, int y) :x(x), y(y) {}
	bool valid() {
		return x >= 0 && x < WIDTH&&y >= 0 && y < HEIGHT;
	}
	int toPos() {
		return x + WIDTH*y;
	}
};

//[s,t)
int random(int s, int t) {
	return s + rand() % (t - s);
}

int steps[4][2] = { (1,0),(0,1),(-1,0),(0,-1) };
bool maze[WIDTH][HEIGHT][4];

void PrintMaze() {
	for (int x = 0; x < WIDTH; ++x) {
		for (int y = 0; y < HEIGHT; ++y) {
			if (maze[x][y][3] == true)printf("-");
			else printf(" ");
		}
		printf("\n");
		for (int y = 0; y < HEIGHT; ++y) {
			if (maze[x][y][2] == true)printf("|");
			else printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	srand(time(0));
	memset(maze, true, sizeof(maze));

	Union_Find_Set ufs;
	ufs.Resize(WIDTH*HEIGHT);

	Pos pos1,pos2;
	for (int i = 0; ufs.Find(0) != ufs.Find(WIDTH*HEIGHT - 1); ++i) {
		pos1.x = random(0, WIDTH); pos1.y = random(0, HEIGHT);
		int dir = random(0, 4);
		printf("%d %d %d\n", pos1.x, pos1.y, dir);

		pos2.x = pos1.x + steps[dir][0];
		pos2.y = pos1.y + steps[dir][1];

		if (pos2.valid() && maze[pos1.x][pos1.y][dir] == true) {
			if (ufs.Find(pos1.toPos()) != ufs.Find(pos2.toPos())) {
				maze[pos1.x][pos1.y][dir] = false;
				maze[pos2.x][pos2.y][(dir + 2) % 4] = false;
				ufs.Union(pos1.toPos(), pos2.toPos());
			}
		}

		PrintMaze(); getch();
		//printf("%d %d %d\n",i, ufs.Find(0), ufs.Find(WIDTH*HEIGHT - 1));
	}

	return 0;
}