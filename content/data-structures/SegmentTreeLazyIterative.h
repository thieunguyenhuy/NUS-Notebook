/**
 * Author: Le Pham Duy Khoa
 * Description: Non-recursion segment tree with range updates and range queries.
 * Usage: T, U are the node and lazy types. TT, UT, UU represents merging two nodes,
 * applying lazy to a node, and merging two lazies.
 * Time: O(\log N) for each operation
 * Status: Tested on range add update and range min query.
 */
template<class T,class U, 
auto TT, auto UT, auto UU> struct segtree{
    //Tid, Uid are default values of T, U, 
    //representing empty node and empty lazy (no change). 
    T Tid;
    U Uid;
    segtree(T _Tid, U _Uid, vector<T> &a){
        Tid = _Tid, Uid = _Uid;
        build(a);
    }
    vector<T> seg;
    vector<U> d;
    int n, lg;
    void refresh(int v){ 
        seg[v] = TT(seg[v<<1], seg[(v<<1)|1]);
    }
    //0-index
    void build(vector<T> &a){
        int siz = a.size();
        for(n = 1; n < siz;) n <<= 1;
        seg.assign(n<<1, Tid), d.assign(n, Uid), lg = __lg(n);
        for(int i = 0; i < siz; i++) seg[n + i] = a[i];
        for(int i = n - 1; i >= 1; i--) refresh(i);
    }
    void apply(int v, U &f){
        seg[v] = UT(f, seg[v]);
        if(v < n) d[v] = UU(f, d[v]);
    }
    void push(int v){
        apply(v << 1, d[v]), apply((v << 1) | 1, d[v]);
        d[v] = Uid;
    }
    void update(int l, int r, U &f){ //update in [l, r]
        l += n, r += (n + 1);
        if(l >= r) return;
        for(int i = lg; i >= 1; i--){
            if((l >> i << i) != l) push(l >> i);
            if((r >> i << i) != r) push(r >> i);
        }
        int l0 = l, r0 = r;
        for(;l < r; l >>= 1, r >>= 1){
            if(l & 1){
                apply(l, f);
                l++;
            }
            if(r & 1){
                r--;
                apply(r, f);
            }
        }
        l = l0, r = r0;
        for(int i = 1; i <= lg; i++){
            if((l >> i << i) != l) refresh(l >> i);
            if((r >> i << i) != r) refresh(r >> i);
        }
    }
    T query(int l, int r){ // query in [l, r]
        l += n, r += (n + 1);
        if(l >= r) return Tid;
        for(int i = lg; i >= 1; i--){
            if((l >> i << i) != l) push(l >> i);
            if((r >> i << i) != r) push(r >> i);
        }
        T le = Tid, ri = Tid;
        for(;l < r; l >>= 1, r >>= 1){
            if(l & 1){
                le = TT(le, seg[l]);
                l++;
            }
            if(r & 1){
                r--;
                ri = TT(seg[r], ri);
            }
        }
        return TT(le, ri);
    }
};