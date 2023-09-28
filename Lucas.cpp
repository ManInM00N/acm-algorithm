namespace combine
{
    ll p = 1e9 + 7;
    ll p2 = 1e9 + 9;
    inline ll quickpow(ll a, ll b)
    { // 快速幂
        ll res = 1;
        a %= p;
        while (b)
        {
            if (b & 1)
                res = res * a % p;
            a = a * a % p;
            b >>= 1;
        }
        return res % p;
    }
    inline ll inv(ll a)
    { // 逆元（还要取模）
        return quickpow(a, p - 2);
    }
    ll fact[1000005];
    void Init() // 组合数初始化；
    {
        // inv[1] = 1;
        // for (int i = 2; i <= n; i++)
        // {
        //     inv[i] = (m- m/i) * inv[m%i] % m;
        // }//在模数为合数时线性求逆元
        fact[0] = 1;
        for (int i = 1; i <= 1000004; ++i)
            fact[i] = fact[i - 1] * i % p;
    }
    inline ll C(ll m, ll n)
    { // 求组合
        return m < n ? 0 : (fact[m] * inv(fact[n], p) % p) * (inv(fact[m - n], p) % p);
    }
    inline ll Lucas(ll m, ll n)
    { // 卢卡斯定理
        return n == 0 ? 1 : C(m % p, n % p) * Lucas(m / p, n / p) % p;
    }
}
