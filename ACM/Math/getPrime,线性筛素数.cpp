//#include...

#define MAXOFPRIME 1000

unsigned int prime[MAXOFPRIME / 3], cnt = 0;//[2,MAXOFPRIME]��Χ�ڵ����������������ĸ���
bool flag[MAXOFPRIME];//flag[i],i�Ƿ�Ϊ����

void getPrime(){
	memset(flag, true, sizeof(flag));

	int i, j, tmp;
	for (i = 2; i <= MAXOFPRIME; ++i){
		if (flag[i])prime[cnt++] = i;

		for (j = 0; j < cnt; ++j){
			if (tmp = i*prime[j], tmp>MAXOFPRIME)break;
			flag[tmp] = false;//tmpλ�ñ�ʾ�������Էֽ�Ϊi*prime[j]
			if (i%prime[j] == 0)break;
		}
	}
}