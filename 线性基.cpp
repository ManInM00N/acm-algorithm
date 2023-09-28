using ll = long long;
class Linear_basis{
    public:
        ll rm[61], cnt1, d[61];
        bool flag;
        void init()
        {
            memset(rm, 0, sizeof(rm));
            memset(d, 0, sizeof(d));
            flag = cnt1 = 0;
        }
        bool insert(ll x)
        {
            for (int i = 60; i >= 0; i--) // rm[i]表示第i位上为1的值，在之后rebuild()时会对 rm[] 用高斯消元法化简
            {
                if (x & (1ll << i))
                {
                    if (!rm[i])
                    {
                        rm[i] = x; // 线性基有空位就存
                        return 1;
                    }
                    x ^= rm[i]; // 去掉高位
                }
            }
            flag = 1;
            return 0; // 插入失败，即可以被异或所得.
        }
        void rebuild()
        {
            for (int i = 60; i >= 0; i--)
            {
                for (int j = i - 1; j >= 0; j--)
                {
                    if (rm[i] & (1ll << j))
                        rm[i] ^= rm[j]; // 舍去低位化简
                }
            }
            for (int i = 0; i <= 60; i++)
            {
                if (rm[i])
                {
                    d[cnt1++] = rm[i]; //
                }
            }
        }
        ll query_kth(ll k)
        { // 查询第k小的数，需对0特判，查询第k大时也要加入是否有0：第k大(2^(cnt1)-1-flag),第k小(k),须提前rebuild;
            k -= flag;
            if (!k)
                return 0;
            if (k >= (1ll << cnt1))
            {
                return -1;
            }
            ll res = 0;
            for (int i = 0; i < cnt1; i++)
            {
                if (k & (1ll << i)) // 如果线性基有n个元素，它的可异或的个数为 2^n-1,求解第k大也可以用对应二进制形式减出
                    res ^= d[i];
            }
            return res;
        }
        bool check(ll x)
        { // 检验此数是否可以由线性基异所或得
            for (int i = 60; i >= 0; i--)
            {
                if (x && (1ll << i))
                {
                    if (!rm[i])
                        return 0;
                    x ^= rm[i];
                }
            }
            return 1;
        }
        ll Max_xor()
        { // 查询可异或所得最大值
            ll res = 0;
            for (int i = 60; i >= 0; i--)
            {
                res = max(res, res ^ rm[i]);
            }
            return res;
        }
        ll Min_xor()
        { // 查找可异或所得最小值
            for (int i = 0; i < 61; i++)
            {
                if (rm[i])
                {
                    return rm[i];
                }
            }
            return 0;
        }
}
