
//(a ^ b) % mod
ll fastPow(ll a,ll b,ll mod){
	ll ret = 1; a %= mod;
	while (b){
		if (b & 1){ ret *= a; ret %= mod; }
		a *= a; a %= mod;
		b >>= 1;
	}
	return ret;
}

///
// 快速计算 (a ^ p) % m 的值
///
ll fastPow(ll a, ll p, ll m)  
{   
    if (p == 0) return 1;  
    ll  r = a % m;  
    ll  k = 1;  
    while (p > 1)  
    {  
        if ((p & 1)!=0) k = (k * r) % m;   
       
        r = (r * r) % m;  
        p >>= 1;  
    }  
    return (r * k) % m;  
}  