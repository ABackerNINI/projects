
int upper_bound(int *array, int L, int R, int val){

	int mid;
	while (L < R){
		mid = (L + R) >> 1;
		if (!(val < array[mid]))L = ++mid;
		else R = mid;
	}

	return L;
}
