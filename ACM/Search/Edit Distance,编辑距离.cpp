#include <iostream>

using namespace std;

#define MAXN (1000+5)

int dist[MAXN][MAXN];//dist[i][j]保存s1的前i位与s2的前j位的编辑距离

int edit_dist(const string &s1, const string &s2){
	int n1 = s1.size(), n2 = s2.size();
	for (int i = 0; i <= n1; ++i)dist[i][0] = i;
	for (int i = 0; i <= n2; ++i)dist[0][i] = i;

	for (int i = 1; i <= n1; ++i){
		for (int j = 1; j <= n2; ++j){
			if (s1[i - 1] == s2[j - 1])dist[i][j] = dist[i - 1][j - 1];
			else dist[i][j] = dist[i - 1][j - 1] + 1;

			dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
			dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
			//printf("%d ", dist[i][j]);
		}
		//printf("\n");
	}
	return dist[n1][n2];
}


int main(){
	/*string s1, s2; cin >> s1 >> s2;
	cout << edit_dist(s1, s2) << endl;*/

	return 0;
}