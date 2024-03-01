template<class T>
constexpr T power(T a, ll b ,ll p) {
    T res = 1;
    for (; b; b /= 2, a *= a,a%=p) {
        if (b % 2) {
            res *= a;
            res%= p ;
        }
    }
    return res;
}

template<class T = long long>//求解 a^x == b(%p)
T BSGS(T a,T b,T p,T Min = 0ll){
    map<T,ll> hash;
    b%=p;
    T t=sqrt(p)+1;
	for(register T i=0;i<t;++i)
		hash[(T)b*power(a,i,p)%p]=i;//将每个j对应的值插入Hash表
	a=power(a,t,p);
	if(!a) return b==0?1:-1;//特判
	for(register T i=1;i<=t;++i) {//在Hash表中查找是否有i对应的j值
		T val=power(a,i,p);
		int j=hash.find(val)==hash.end()?-1:hash[val];
		if(j>=0&&i*t-j>=0) return i*t-j;
	}
	return -1;//无解返回-1
}