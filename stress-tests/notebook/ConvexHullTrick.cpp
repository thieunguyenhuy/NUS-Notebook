#include "../utilities/template.h"
#include "../../content/data-structures/ConvexHullTrickMonotonicSlopes.h"

int main(){mt19937 rng(11);for(int it=0;it<1000;++it){ConvexHullTrick c;vector<pair<ll,ll>>ls;ll m=1000000000;for(int j=0;j<100;++j){m-=rng()%10000;ll b=(ll)(int)rng();c.add(m,b);ls.push_back({m,b});for(int q=0;q<10;++q){ll x=(int)(rng()%2000)-1000,best=LLONG_MAX;for(auto[a,b]:ls)best=min(best,a*x+b);assert(c.query(x)==best);}}for(ll x=-100;x<=100;++x){ll best=LLONG_MAX;for(auto[a,b]:ls)best=min(best,a*x+b);assert(c.get(x)==best);}}}
