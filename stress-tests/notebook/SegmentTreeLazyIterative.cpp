#include "../utilities/template.h"
#include "../../content/data-structures/SegmentTreeLazyIterative.h"

template<> ll segtree<ll,ll>::TT(ll& a,ll& b){return min(a,b);}
template<> void segtree<ll,ll>::UT(ll& f,ll& a){a+=f;}
template<> void segtree<ll,ll>::UU(ll& a,ll& f){a+=f;}
int main(){mt19937 rng(8);for(int n=1;n<100;++n){vector<ll>a(n);segtree<ll,ll> st(1LL<<60,0,a);for(int it=0;it<1000;++it){int l=rng()%n,r=rng()%n;if(l>r)swap(l,r);if(rng()%2){ll v=(int)(rng()%200)-100;st.update(l,r,v);for(int j=l;j<=r;++j)a[j]+=v;}else assert(st.query(l,r)==*min_element(a.begin()+l,a.begin()+r+1));}}}
