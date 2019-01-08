#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <Windows.h>

//注意,此文档编码为UTF-16LE,控制台显示方式为UTF-8.所以此文件中的printf所包含的中文不能正确显示.
//数据文件编码为UTF-8,而wchar_t不能很好地处理UTF-8,所以某些字符不能被正确显示,如部分音标.
//处理UTF-8比较麻烦.
//控制台显示方式不能设置为UTF-16LE.不知道原因.

int IsLowercaseLetter(wchar_t ch) {
    return ch >= L'a'&&ch <= L'z';
}

int IsLetter(wchar_t ch) {
    return (ch >= L'a'&&ch <= L'z') || (ch >= L'A'&&ch <= L'Z');
}

wchar_t Lowercase(wchar_t ch) {
    if (ch >= L'A'&&ch <= L'Z')
        ch += 32;
    return ch;
}

//可以通过这个结构扩展更详细的词典,如例句,不同时态,近反义词等
typedef struct word {
    wchar_t *wordSelf;         //单词
    wchar_t *phoneticAlphabet; //音标
    wchar_t *explanation;      //释义
}Word;

//节点
typedef struct node {
    int isWord;
    Word *word;
    struct node *next[26];
}Node;

//字典树
typedef struct tree {
    int wordCount;
    struct node *next[26];
}Tree;

//构造节点
Node *InitNode() {
    Node *node = (Node *)malloc(sizeof(Node));
    node->isWord = 0;
    node->word = NULL;
    memset(node->next, 0, sizeof(node->next));
    return node;
}

//释放节点
void FreeNode(Node *node) {
    if (node->word != NULL) {
        free(node->word->wordSelf);//这里有问题,暂时不知道原因,free的时候会出错
        free(node->word->phoneticAlphabet);
        free(node->word->explanation);
        free(node->word);
    }

    int i;
    for (i = 0; i < 26; ++i) {
        if (node->next[i] != NULL) {
            FreeNode(node->next[i]);
        }
    }

    free(node);
}

//构造字典树
Tree *InitTree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->wordCount = 0;
    int i;
    for (i = 0; i < 26; ++i) {
        tree->next[i] = InitNode();
    }
    return tree;
}

//释放字典树
void FreeTree(Tree *tree) {
    int i;
    for (i = 0; i < 26; ++i) {
        if (tree->next[i] != NULL) {
            FreeNode(tree->next[i]);
        }
    }

    free(tree);
}

//插入单词
void InsertWord(Tree *tree, const wchar_t *wordStr, Word *word) {
    Node *root = tree->next[Lowercase(wordStr[0]) - L'a'];
    int ch;
    while (*(++wordStr)) {
        ch = Lowercase(*wordStr) - L'a';
        if (root->next[ch] == NULL) {
            root->next[ch] = InitNode();
        }
        root = root->next[ch];
    }
    root->isWord = 1;
    root->word = word;
    ++tree->wordCount;
}

//切割数据行
Word *CutLine(wchar_t *line) {
    int i, l = 0, r = 0, e = 0;
    wchar_t *p;
    for (i = 0, p = line; ; ++i, ++p) {
        if (*p == L'[') {
            *p = L'\0';
            l = i;
        } else if (*p == L']') {
            *p = L'\0';
            r = i;
        } else if (*p == L'\0' || *p == L'\n') {
            *p = L'\0';
            e = i;
            break;
        }
    }
    int flag = 0;
    for (i = 0; i < l; ++i) {
        if (IsLetter(line[i]) == 0) {
            flag = 1;
            break;
        }
    }

    Word *word = NULL;
    if (flag == 0) {
        word = (Word *)malloc(sizeof(Word));
        if (l == 0) {
            l = 0;
        }
        word->wordSelf = (wchar_t *)malloc(sizeof(wchar_t)*(l));
        word->phoneticAlphabet = (wchar_t *)malloc(sizeof(wchar_t)*(r - l));
        word->explanation = (wchar_t *)malloc(sizeof(wchar_t)*(e - r));
        wcscpy(word->wordSelf, line);
        wcscpy(word->phoneticAlphabet, line + l + 1);
        wcscpy(word->explanation, line + r + 1);
    }
    return word;
}

//读取数据文件,构造1*26的字典树,返回收录的单词个数,-1出错
int ReadData(Tree *tree, const wchar_t *path) {
    FILE *file = _wfopen(path, L"r");//,ccs=UTF-8,UTF-16LE
    if (file == NULL) {
        return -1;
    }

    wchar_t line[500];
    Word *word;
    int count = 0;
    while (fgetws(line, 500, file) != NULL) {
        word = CutLine(line);
        if (word != NULL) {
            InsertWord(tree, line, word);
        }

        //wprintf(L"%s\n", line);
        //printf("%s", line);
        ++count;
    }
    return count;
}

//查找单词,返回单词所在节点
Node *QueryWord(Tree *tree, const wchar_t *word) {
    Node *root = tree->next[word[0] - L'a'];
    wchar_t ch;
    while (*(++word)) {
        ch = *word - L'a';
        if (root->next[ch] == NULL) {
            return NULL;
        }
        root = root->next[ch];
    }
    return root;
}

//打印匹配的n个单词,返回已打印的单词个数
int PrintNextNWords(Node *root, int n) {
    int i;
    int tmp = n;
    for (i = 0; i < 26; ++i) {
        if (root->next[i] != NULL) {
            if (root->next[i]->isWord) {
                wprintf(L" %s\n", root->next[i]->word->wordSelf);
                --n;
            }
            if (n == 0)break;
            if (n > 0) {
                n -= PrintNextNWords(root->next[i], n);
            }
        }
    }
    return tmp - n;
}

int main() {
    //设置UTF-8显示方式
    SetConsoleOutputCP(65001);//1200
    //CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体来支持中文显示。
    //info.cbSize = sizeof(info);
    //info.dwFontSize.Y = 16; // leave X as zero
    //info.FontWeight = FW_NORMAL;
    //wcscpy(info.FaceName, L"Consolas");
    //SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &info);

    const wchar_t *path = L"english dictionary.txt";
    Tree *tree = InitTree();
    int count = ReadData(tree, path);
    if (count == -1) {
        getchar();
        return -1;
    }

    wprintf(L"%d\n", count);

    wchar_t line[200];
    while (1) {
        wprintf(L"\n>");
        wscanf(L"%[^\n]", line);
        getchar();
        Node *node = QueryWord(tree, line);
        if (node != NULL) {
            if (node->isWord) {
                wprintf(L"[%s]:%s\n", node->word->wordSelf, node->word->explanation);//不显示音标
                wprintf(L"[%s]:|%s|%s\n", node->word->wordSelf, node->word->phoneticAlphabet, node->word->explanation);//显示音标
                PrintNextNWords(node, 8);
            } else {
                PrintNextNWords(node, 8);
            }
        }
    }
    FreeTree(tree);

    return 0;
}