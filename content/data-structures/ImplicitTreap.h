/**
 * Author: Le Pham Duy Khoa
 * Description: An implicit treap on an array that supports
 * deleting an element, inserting an element in any position
 * and splitting the array into two parts (prefix/suffix).
 * Usage: Declare pnode t = nullptr for an empty array,
 * then use the functions. If you want to handle more data in each node,
 * then reimplement refresh(). Note that the array is 1-indexed.
 * Time: $O(\log N)$
 * Status: Tested on one problem
 */
mt19937_64 rng(6736);
struct node{
  int val, sz = 1;
  uint64_t y;
  node *le = nullptr, *ri = nullptr;
  node(int val): val(val), y(rng()) {}
};
namespace implicit_treap{ //1-index
  using pnode = node*;
  int get_sz(pnode &p){ return p != nullptr ? p->sz : 0; }
  void refresh(pnode &p){ p->sz = get_sz(p->le) + get_sz(p->ri) + 1; }
  //first is [1, i], second is [i + 1, n]
  pair<pnode, pnode> split(pnode t, int i){
    if(t == nullptr) return {nullptr, nullptr};
    pair<pnode, pnode> ans;
    if(get_sz(t->le) + 1 <= i){
      ans = split(t->ri, i - get_sz(t->le) - 1);
      t->ri = ans.first; ans.first = t;
      refresh(ans.first);
    }
    else{
      ans = split(t->le, i);
      t->le = ans.second; ans.second = t;
      refresh(ans.second);
    }
    return ans;
  }
  //t1 is treap of a1,...,an. t2 is treap of b1,...,bm.
  //Merge into a1,...,an,b1,...,bm.
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
