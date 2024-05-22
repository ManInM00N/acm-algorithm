const ll base = 131;
const ll mod1=1e9+7,mod2=1e9+9;
struct hash_val
{
    vector<unsigned long long>has1,has2;
	vector<unsigned long long>base1,base2;
	int p1=131,p2=13331;
	hash_val(string s) {
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
	unsigned long long calchas1(int l,int r) {
		return has1[r]-base1[r-l+1]*has1[l-1];
	}
	unsigned long long calchas2(int l,int r) {
		return has2[r]-base2[r-l+1]*has2[l-1];	
	}
	bool same(int l1,int r1,int l2,int r2) {
		return calchas1(l1,r1)==calchas1(l2,r2)&&calchas2(l1,r1)==calchas2(l2,r2);
	}
};
hash_val a[N];

ll zz[N];
const ll P = 13331;
const ll mod = 1e9+7;
template<class Ty1,class Ty2> 
inline const pair<Ty1,Ty2> operator+(const pair<Ty1, Ty2>&p1, const pair<Ty1, Ty2>&p2)//重载pair运算符
{
    pair<Ty1, Ty2> ret;
    ret.first = p1.first + p2.first;
    ret.second = p1.second + p2.second;
    return ret;
}
class Segment
{
public:
    struct tree
    {
        int l, r;
        ll len;
        ll h1,h2;//正逆向哈希,可求解区间内更新查询回文问题
    };
    int num;
    vector<tree> tr;
    vector<int> arr;
    Segment(){};
    template <class T>
    Segment(T n) : num(n + 7)
    {
        tr.resize(4 * num);//线段树哈希
        arr.resize(num, 0);
    };
    void pushup(ll p)
    {
        tr[p].h1 = (tr[rs].h1*zz[tr[ls].len]+tr[ls].h1)%mod;
        tr[p].h2 = (tr[ls].h2*zz[tr[rs].len]+tr[rs].h2)%mod;
    }
    template <class T, class V, class W>
    void build(V l, W r,T p=1ll )
    {
        tr[p].l = l;
        tr[p].r = r;
        tr[p].len = r-l+1;;
        tr[p].h1=tr[p].h2 = arr[l];
        if (l == r)
            return;
        long long mid = l + r >> 1;
        build(l, mid,ls);
        build(mid + 1, r,rs);
        pushup(p);
    }
    template <class T, class V>
    void update(T x, T y, V z,V p = 1ll )
    {
        if (tr[p].l >= x && tr[p].r <= y)
        {
            tr[p].h1 =tr[p].h2 = z;
            // tr[p].lazy += z;
            return;
        }
        long long mid = tr[p].l + tr[p].r >> 1;
        // pushdown(p);
        if (mid >= x)
            update(x, y, z,ls);
        if (mid < y)
            update(x, y, z,rs);
        pushup(p);
    }

    template <class T, class V, class W>
    Pa query( T x, W y,V p=1ll)
    {
        if (tr[p].l >= x && tr[p].r <= y)
        {
            return Pa(zz[tr[p].l-x]*tr[p].h1%mod,zz[y-tr[p].r]*tr[p].h2%mod);
            // return tr[p].sum;
        }
        long long mid = tr[p].l + tr[p].r >> 1;
        Pa sum = {0,0};
        if (mid >= x)
            sum = sum + query(x, y,ls);
        if (mid < y)
            sum = sum + query( x, y,rs);
        sum.first%=mod;
        sum.second%=mod;
        return sum;
    }
};
void init(){
    zz[0] = 1;
    repi(i,1,n+10){
        zz[i] = zz[i-1]*P%mod;
    }
}