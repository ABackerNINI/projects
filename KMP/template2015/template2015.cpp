//
//	Created by ABacker on 6/7/2016
//

#include<iostream>
#include<algorithm>

using namespace std;

int* create_next(_In_ const char *sub_str, _In_opt_ int *next = NULL, _In_opt_ int len = -1) {
	if (len == -1)len = strlen(sub_str);
	if (next == NULL) next = new int[len];

	next[0] = 0; int k;
	for (int i = 1; i < len; ++i) {
		k = next[i - 1];
		while (sub_str[i] != sub_str[k] && k != 0)k = next[k - 1];

		next[i] = sub_str[i] == sub_str[k] ? k + 1 : 0;
	}

	return next;
}

int search(_In_ const char *parent_str, _In_ const char *sub_str, _In_opt_ int *next = NULL) {
	int cnt = 0, ret = 0, len = strlen(sub_str);
	bool isNextNull = false;

	if (next == NULL) { next = create_next(sub_str); isNextNull = true; }

	--parent_str;
	while (*++parent_str) {
		if (cnt > 0 && *parent_str != sub_str[cnt]) {
			cnt = next[cnt - 1];
		}
		else if (*parent_str == sub_str[cnt])++cnt;

		if (cnt == len) {
			++ret;
			cnt = next[cnt - 1];
		}
	}
	if (isNextNull)delete[]next;

	return ret;
}

int main(){
	char a[] = "aaa bbb ccaacdaaad"; char b[] = "aaa";
	cout << search(a, b) << endl;

	system("pause");

    return 0;
}