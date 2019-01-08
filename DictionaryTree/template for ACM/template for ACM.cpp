#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <ctime>

#include <conio.h>
#include <windows.h>

using namespace std;

#define MAXSIZEOFWORD 1000
#define DEBUG 0x1
#define DEBUG_PRINT_ALL_WORDS 0x1 //输出以查询词为首的所有单词

class Trie {
private:
	struct Node {
		bool isWord; unsigned int prefix; Node *next[26];
		Node() { memset(next, 0, sizeof(next)); isWord = false; prefix = 0; }
	};

public:
	Trie() { root = new Node; size = usize = mem = 0; }

	void Insert(const char *str) {
		Node *root = this->root; bool isNew = false;
		while (*str) {
			if (!isLetter(*str)) { Insert(++str); break; }

			int ch = lowercase(*str++) - 'a';
			if (root->next[ch] == NULL) { root->next[ch] = new Node; isNew = true; ++mem; }

			root = root->next[ch];
			++root->prefix;
		}
		root->isWord = true;

		++size; if (isNew)++usize;
	}
	unsigned int Query(const char *str) {
		string prior = "\t"; prior.append(str);
		Node *root = this->root;
		while (*str) {
			if (!isLetter(*str)) { throw exception("Error:Wrong Input!"); }

			int ch = lowercase(*str++) - 'a';
			if (root->next[ch] == NULL)return 0;

			root = root->next[ch];
		}

#if (DEBUG&DEBUG_PRINT_ALL_WORDS)
		Print_All(prior, root);
#endif

		return root->prefix;
	}

	long long Mem() {
		return mem*sizeof(Node);
	}

	//返回:单词总数
	long long Size() {
		return size;
	}

	//返回:不同单词数
	long long USize() {
		return usize;
	}

	~Trie() {
		del(this->root);
	}

private:
	Node *root; long long size, usize, mem;

	bool isLetter(char c) { 
		return c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z';
	}
	char lowercase(char c) {
		return c < 'a' ? c + 32 : c;
	}
	void del(Node *root) {
		for (int i = 0; i < 26; ++i) {
			if (root->next[i] != NULL)del(root->next[i]);
		}
		delete root;
	}

#if (DEBUG&DEBUG_PRINT_ALL_WORDS)
	//输出root位置下所有单词
	void Print_All(string prior, Node *root) {
		if (root->isWord)cout << prior << endl;
		for (int i = 0; i < 26; ++i) {
			if (root->next[i] != NULL) {
				string tmp = prior + (char)('a' + i);
				Print_All(tmp, root->next[i]);
			}
		}
	}
#endif
};

//读取文件并统计
void test_1() {
	DWORD begin = GetTickCount();
	if (freopen("test.txt", "r", stdin) == NULL) {
		printf("Error:Fail to read the test file!");
		
		getch();return;
	};

	Trie tree;
	char word[MAXSIZEOFWORD];
	while (~scanf("%s", word))tree.Insert(word);

	freopen("CON", "r", stdin);

	printf("单词总数:%I64d\n不同单词数:%I64d\n占内存:%I64dKb\n用时: %dms\n", tree.Size(), tree.USize(), tree.Mem()/1024, GetTickCount() - begin);

	while (printf(">"), ~scanf("%s", word)) {
		try {
			printf("\n\t以'%s'为首的单词共出现:%u次\n", word, tree.Query(word));
		}
		catch (exception &e) {
			cout << "\t" << e.what() << endl;
		}
	}

	fclose(stdin);
}

//手动输入单词并统计
void test_2() {
	Trie tree;
	char word[MAXSIZEOFWORD];
	while (~scanf("%s", word))tree.Insert(word);

	printf("单词总数:%I64d\n不同单词数:%I64d\n", tree.Size(), tree.USize());

	while (printf(">"), ~scanf("%s", word)) {
		try {
			printf("\n\t以'%s'为首的单词共出现:%u次\n", word, tree.Query(word));
		}
		catch (exception &e) {
			cout << "\t" << e.what() << endl;
		}
	}
}


int main(){
	test_1();

	return 0;
}