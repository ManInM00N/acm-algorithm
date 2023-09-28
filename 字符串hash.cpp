const ll base = 131;
const ll mod1=1e9+7,mod2=1e9+9;

struct hash_val
{
    vector<unsigned long long>has1,has2;
	vector<unsigned long long>base1,base2;
	int p1=131,p2=13331;
	Hash(string s) {
		int n=s.length();
		has1.resize(n+1,0);
		has2.resize(n+1,0);
		base1.resize(n+1,1);
		base2.resize(n+1,1);
		for (int i=1;i<=n;i++) {
			has1[i]=has1[i-1]*p1+s[i-1];
			has2[i]=has2[i-1]*p2+s[i-1];
			base1[i]=base1[i-1]*p1;
			base2[i]=base2[i-1]*p2;
		}
	}
	ull calchas1(int l,int r) {
		return has1[r]-base1[r-l+1]*has1[l-1];
	}
	ull calchas2(int l,int r) {
		return has2[r]-base2[r-l+1]*has2[l-1];	
	}
	bool same(int l1,int r1,int l2,int r2) {
		return calchas1(l1,r1)==calchas1(l2,r2)&&calchas2(l1,r1)==calchas2(l2,r2);
	}
};
hash_val a[N];


void print(__int128 x)//大数据输出128位int
{
    if (!x) return ;
    if (x < 0) putchar('-'),x = -x;
    print(x / 10);
    putchar(x % 10 + '0');
}
inline void read(__int128 &X)//大数据读入128位int
{
    X = 0;
    int w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    if (w) X = -X;
}