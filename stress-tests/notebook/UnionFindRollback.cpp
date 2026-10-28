#include "../utilities/template.h"
#include "../../content/data-structures/UnionFindRollback.h"

int main(){
    const int n=15;DsuRollback uf(n);vector<pii> ops;mt19937 rng(5);
    for(int it=0;it<10000;++it){if(!ops.empty() && rng()%3==0){int k=1+rng()%ops.size();uf.rollback(k);ops.resize(ops.size()-k);}
        else {int u=rng()%n,v=rng()%n;uf.unite(u,v);ops.push_back({u,v});}
        vi p(n);iota(all(p),0);auto f=[&](int u,auto& self)->int{return p[u]==u?u:self(p[u],self);};
        for(auto[u,v]:ops)p[f(u,f)]=f(v,f);int cc=0;
        for(int i=0;i<n;++i){cc+=f(i,f)==i;int cnt=0;for(int j=0;j<n;++j){assert((uf.Findset(i)==uf.Findset(j))==(f(i,f)==f(j,f)));cnt+=f(i,f)==f(j,f);}assert(uf.get_sz(i)==cnt);}assert(uf.cc==cc);
    }
    RollbackUF snapshot(4);int t=snapshot.time();snapshot.join(0,1);snapshot.join(1,2);snapshot.rollback(t);assert(snapshot.size(0)==1);
}
