#include "../utilities/template.h"
#include "../../content/graph/MaxFlow.h"

int main(){mt19937 gen(16);for(int it=0;it<1000;++it){int n=2+gen()%6;Dinic f(n);vector<tuple<int,int,ll>>es;for(int u=0;u<n;++u)for(int v=0;v<n;++v)if(u!=v&&gen()%3==0){ll c=gen()%10;f.add(u,v,c);es.push_back({u,v,c});}ll want=LLONG_MAX;for(int mask=1;mask<(1<<n);mask+=2)if(!(mask>>(n-1)&1)){ll c=0;for(auto[u,v,w]:es)if((mask>>u&1)&&!(mask>>v&1))c+=w;want=min(want,c);}assert(f.maxFlow(0,n-1)==want);vector<pii>cut;for(auto[u,v,w]:es)if(w>0&&f.level[u]&&!f.level[v])cut.push_back({u,v});assert(f.minCut()==cut);}}
