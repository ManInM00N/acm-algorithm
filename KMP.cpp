class KMP
{
public:
    int j, len;
    vector<int> nex;
    string pattern;
    KMP(){};
    KMP(string ss)
    {
        pattern = ss, len = ss.length(), nex.resize(len + 1), pattern_init();
    };
    void pattern_init()
    {
        pattern = "#" + pattern; // 默认下标从1开始;
        nex[0] = nex[1] = 0;
        for (int i = 2, j = 0; i <= len; i++)
        {
            while (j && pattern[i] != pattern[j + 1])
                j = nex[j];
            if (pattern[i] == pattern[j + 1])
                j++;
            nex[i] = j;
        }
    }
    vector<int> find_prefix(string text)
    {
        vector<int> ans;
        ans.push_back(-1); // 下标也默认从1开始;
        text = "#" + text;
        for (int i = 1, j = 0; i < text.length(); i++)
        {
            while (j && text[i] != pattern[j + 1])
                j = nex[j];
            if (text[i] == pattern[j + 1])
                j++;
            if (j == len)
            {
                // /*
                // printf("%d\n",i-len+1); // 找到完整模式串，输出出现位置
                // */
            }
            ans.push_back(j); // 当前text[i-j+1,i]是模式串的前缀，如果j==0说明与前缀无关
        }
        return ans;
    }
};
class EX_KMP
{
public:
    int len;
    vector<ll> z;
    string pattern;
    EX_KMP(){};
    EX_KMP(string ss)
    {
        pattern = ss, z.resize(len + 1);
        pattern = "#" + pattern;
        pattern_getz();
    };
    void pattern_getz()
    {
        z[1] = len;
        for (ll i = 2, l, r = 0; i <= len; i++)
        {
            if (i <= r)
                z[i] = min(z[i - l + 1], r - i + 1);
            while (pattern[1 + z[i]] == pattern[i + z[i]])
                z[i]++;
            if (i + z[i] - 1 > r)
                l = i, r = i + z[i] - 1;
        }
    }
    vector<ll> get_p(string text)
    {
        ll len2 = text.length();
        text = "#" + text;
        vector<ll> ans(len2 + 2);
        for (ll i = 1, l, r = 0; i <= len2; i++)
        {
            if (i <= r)
                ans[i] = min(z[i - l + 1], r - i + 1);
            while (1 + ans[i] <= len && i + ans[i] <= len2 && pattern[1 + ans[i]] == text[i + ans[i]])
                ans[i]++;
            if (i + ans[i] - 1 > r)
                l = i, r = i + ans[i] - 1;
        }
        return ans;
    }
};