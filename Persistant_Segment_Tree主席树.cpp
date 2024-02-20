template<class T = long long>
class Persistant_Segment_Tree{
public:
    constexpr static T maxn = 1e5+7;
    //与常规线段树不同  主席树结构体的l,r是对树的索引而不是区间的索引！！
    //而函数中的参数l,r则是对应的区间
    struct tree
    {
        T l, r,val;
    };
    vector<tree> tr;
    vector<T> arr,root;//root[i]为第 i 个版本的根节点编号
    T dir,siz; // dir为节点数  siz为主席树范围
    Persistant_Segment_Tree(T n = maxn) : siz(n+7){
        dir = 0;
        arr.resize(siz);
        root.resize(siz);
        tr.resize(siz<<5);
    } 
    T Build(T l,T r,T p = 0){
        p = ++dir;
        if (l==r){
            tr[p].val = arr[l];
            return p;
        }
        T mid = l+r>>1;
        tr[p].l = Build(l, mid, tr[p].l);
        tr[p].r = Build(mid + 1, r, tr[p].r);
        // pushup(p);
        return p;
    }
    inline T copy(T p){
        ++dir;
        tr[dir] = tr[p];

        // tr[dir].val ++ ;  //区间第k值的前缀和累加  若为单点历史修改则不需要
        return dir; 
    }
    constexpr inline T GetHead(T p){
        return root[p];
    }
    void pushup(T p){
        tr[p].val = tr[tr[p].l].val+tr[tr[p].r].val;
    }
    T Modify(T l, T r, T pos, T p )//区间第k值的更新  去掉val即可
    {
        p = copy(p);
        if (l==r){
            return p;
        }
        T mid = l+r>>1;
        if (pos <= mid) {
            tr[p].l = Modify(l,mid,pos,tr[p].l);
        }else {
            tr[p].r = Modify(mid+1,r,pos,tr[p].r);
        }
        // pushup(p);
        return p;
    }
    T Modify(T l, T r, T pos, T val, T p )//历史版本单点修改 
    {
        p = copy(p);
        if (l==r){
            tr[p].val = val;  //版本修改
            return p;
        }
        T mid = l+r>>1;
        if (pos <= mid) {
            tr[p].l = Modify(l,mid,pos,val,tr[p].l);
        }else {
            tr[p].r = Modify(mid+1,r,pos,val,tr[p].r);
        }
        // pushup(p);
        return p;
    }
    T Query(T l,T r,T pos, T p){
        if (l==r){
            return tr[p].val;
        }
        T mid = l+r >>1;
        if (pos<=mid){
            return Query(l,mid,pos, tr[p].l);
        }else{
            return Query(mid + 1, r, pos, tr[p].r);
        } 
    }
    T Query_Kth(T l,T r, T vl,T vr, T k){
        if (l==r){
            return l;
        }   
        T mid = l+r>>1;
        T lsum = tr[tr[vr].l].val-tr[tr[vl].l].val;
        if (lsum>=k){
            return Query_Kth(l,mid,tr[vl].l,tr[vr].l,k);
        }else {
            return Query_Kth(mid+1,r,tr[vl].r,tr[vr].r,k-lsum);
        }
    }
};
// 更新的版本 ： root[i] = modify(1,n,pos,val, root[x])
