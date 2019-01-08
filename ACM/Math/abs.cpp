inline int abs(int val){
	int i = val >> 31;
	return ((val ^ i) - i);
}

inline ll abs(ll val){
	ll i = val >> 63;
	return ((val^i) - i);
}