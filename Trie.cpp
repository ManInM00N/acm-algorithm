class trie{
    int nex[1000007][27],idx;
    int cnt[1000007];
    void insert(string ss){
        int p=0;
        for (int i = 0; i < ss.length(); i++)
        {
            int j =ss[i]-'a';
            if (!nex[p][j]) nex[p][j]=idx++;
            p=nex[p][j];
            cnt[p]++;
        } 
    }
    bool find(string ss){
        int p =0;
        for (int i = 0; i < ss.length(); i++)
        {
            int j = ss[i]-'a';
            if (!nex[p][j]) return 0;
            p = nex[p][j];
        }
        return 1;
    }
};