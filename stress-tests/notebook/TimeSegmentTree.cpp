#include "../utilities/template.h"
#include "../../content/data-structures/TimeSegmentTree.h"

#include "../../content/data-structures/UnionFindRollback.h"
DsuRollback uf(8);
namespace segtree_time {Q calc(int){return uf.cc;}void add(ope&x){uf.unite(x.first,x.second);}void rollback(int k){uf.rollback(k);}}
int main(){mt19937 gen(14);vector<array<int,4>>ops;for(int j=0;j<500;++j){int l=1+gen()%30,r=1+gen()%30;if(l>r)swap(l,r);int u=gen()%8,v=gen()%8;segtree_time::update(l,r,{u,v});ops.push_back({l,r,u,v});}vector<pii>qs;for(int i=0;i<100;++i)qs.push_back({1+gen()%30,i});auto ans=solve_queries(qs);for(auto[t,i]:qs){vi p(8);iota(all(p),0);auto f=[&](int u,auto&self)->int{return p[u]==u?u:self(p[u],self);};for(auto[l,r,u,v]:ops)if(l<=t&&t<=r)p[f(u,f)]=f(v,f);int cc=0;for(int u=0;u<8;++u)cc+=f(u,f)==u;assert(ans[i]==cc);}assert(uf.cc==8&&uf.st.empty());assert(solve_queries(qs)==ans);}
