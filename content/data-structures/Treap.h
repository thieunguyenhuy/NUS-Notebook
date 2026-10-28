/**
 * Author: Le Pham Duy Khoa
 * Description: An explicit treap that supports split(), merge(),
 * insert(), and erase().
 * Usage: Declare pnode t = nullptr for an empty treap,
 * then use the functions. If you want to handle more data in each node,
 * then reimplement get_val() and refresh().
 * Time: $O(\log N)$
 * Status: Tested on two problems
 */
mt19937_64 rng(6736);
struct node{
    int x, sz = 1;
    ull y;
    node *le = nullptr, *ri = nullptr;
    node(int x): x(x), y(rng()) {}
};
namespace treap{
    using pnode = node*;
    int get_val(pnode &p){ return p != nullptr ? p->sz : 0; }
    void refresh(pnode &p){ p->sz = get_val(p->le) + get_val(p->ri) + 1; }
    //first is <=x, second is >x
    pair<pnode, pnode> split(pnode t, int x){
        if(t == nullptr) return {nullptr, nullptr};
        pair<pnode, pnode> ans;
        if(t->x <= x){
            ans = split(t->ri, x);
            t->ri = ans.fi; ans.fi = t;
            refresh(ans.fi);
        } else {
            ans = split(t->le, x);
            t->le = ans.se; ans.se = t;
            refresh(ans.se);
        }
        return ans;
    }
    //assume all t1->x < t2->x (ordering between trees)
    pnode merge(pnode t1, pnode t2){
        if(t1 == nullptr || t2 == nullptr) return t1 == nullptr ? t2 : t1;
        if(t1->y >= t2->y){
            t1->ri = merge(t1->ri, t2); 
            refresh(t1); return t1;
        }
        t2->le = merge(t1, t2->le); 
        refresh(t2); return t2;
    }
}