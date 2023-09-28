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
    }
    ll work()
    {
        d[1] = 1;
        ll ans = 1;
        for (ll i = 2, l, r = 1; i <= len; i++)
        {
            if (i <= r)
                d[i] = min(d[r - i + l], r - i + 1);
            while (pattern[i - d[i]] == pattern[i + d[i]])
                d[i]++;
            ans = max(ans, d[i]);
            if (i + d[i] - 1 > r)
                l = i - d[i] + 1, r = i + d[i] - 1;
        }
        return ans - 1;
    }
};