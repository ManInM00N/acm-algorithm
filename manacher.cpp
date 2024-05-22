class manacher
{
public:
    vector<ll> d;
    int len;
    string pattern;
    manacher(){};
    manacher(string ss)
    {
        pattern = "$#";
        init(ss);
        len = pattern.length();
        d.resize(len + 1);
    }
    void init(string ss)
    {
        for (int i = 0; i < ss.length(); i++)
        {
            pattern.push_back(ss[i]);
            pattern.push_back('#');
        }
        pattern.push_back('&');
    }
    ll work()
    {
        d[1] = 1;
        ll ans = 1;
        for (ll i = 0, l=0, r = 1; i < len; i++)
        {
            if (i <= r)
                d[i] = min(d[r - i + l], r - i + 1);
            else d[i] = 1;
            while (pattern[i - d[i]] == pattern[i + d[i]])
                d[i]++;
            ans = max(ans, d[i]);
            if (i + d[i] - 1 > r)
                l = i - d[i] + 1, r = i + d[i] - 1;
        }
        return ans - 1;
    }
    bool check(ll l,ll r){
        ll l0 = 2 * l, r0 = 2 * r;
        ll mid = (l0 + r0) >> 1;
        if (d[mid] >= r - l + 1) {
            return 1;
        }
        return 0;
    }
};