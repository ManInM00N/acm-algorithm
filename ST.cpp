ll st[N][20];
void init(){
    for (int k = 1; k < 20; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (i+(1ll<<(k-1))<=n)
                st[i][k]= max(st[i][k-1],st[i+(1ll<<(k-1))][k-1]);
        }
    }
    
}
ll query(ll l,ll r){
    ll len = log2(r-l+1);
    return max(st[l][len],st[r-(1ll<<(len))+1][len]);
}