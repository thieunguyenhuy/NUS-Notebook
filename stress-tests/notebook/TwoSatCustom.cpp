#include "../utilities/template.h"
#include "../../content/graph/TwoSat.h"

int main(){mt19937 gen(17);for(int it=0;it<3000;++it){int n=1+gen()%7;TwoSat ts(n);vector<pii>cs;for(int j=0;j<20;++j){int u=1+gen()%(2*n),v=1+gen()%(2*n);cs.push_back({u,v});ts.add_u_or_v(u,v);}auto eval=[&](int u,int mask){return u<=n?bool(mask>>(u-1)&1):!bool(mask>>(u-n-1)&1);};bool exists=false;for(int mask=0;mask<(1<<n);++mask){bool ok=true;for(auto[u,v]:cs)ok&=eval(u,mask)||eval(v,mask);exists|=ok;}auto a=ts.get_equation();assert((a!=vi{-1})==exists);if(exists){int mask=0;for(int i=1;i<=n;++i)mask|=a[i]<<(i-1);for(auto[u,v]:cs)assert(eval(u,mask)||eval(v,mask));}}}
