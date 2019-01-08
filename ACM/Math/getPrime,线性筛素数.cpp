//#include...

#define MAXOFPRIME 1000

unsigned int prime[MAXOFPRIME / 3], cnt = 0;//[2,MAXOFPRIME]范围内的所有素数和素数的个数
bool flag[MAXOFPRIME];//flag[i],i是否为素数

void getPrime(){
	memset(flag, true, sizeof(flag));

	int i, j, tmp;
	for (i = 2; i <= MAXOFPRIME; ++i){
		if (flag[i])prime[cnt++] = i;

		for (j = 0; j < cnt; ++j){
			if (tmp = i*prime[j], tmp>MAXOFPRIME)break;
			flag[tmp] = false;//tmp位置表示的数可以分解为i*prime[j]
			if (i%prime[j] == 0)break;
		}
	}
}