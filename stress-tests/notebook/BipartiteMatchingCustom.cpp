#include "../utilities/template.h"
#include "../../content/graph/BipartieMatching.h"

int main(){mt19937 rng(13);for(int it=0;it<2000;++it){int n=1+rng()%7,m=1+rng()%7;bipartite_matching bm(n,m);vector<pii>edges;for(int u=1;u<=n;++u)for(int v=1;v<=m;++v)if(rng()%2){bm.add(u,v);edges.push_back({u,v});}auto brute=[&](int u,int mask,auto&self)->int{if(u>n)return 0;int best=self(u+1,mask,self);for(int v:bm.adj[u])if(!(mask>>(v-1)&1))best=max(best,1+self(u+1,mask|(1<<(v-1)),self));return best;};int want=brute(1,0,brute);assert(bm.max_matching()==want);auto[L,R]=bm.minimum_vertex_cover();assert((int)(L.size()+R.size())==want);for(auto[u,v]:edges)assert(find(all(L),u)!=L.end()||find(all(R),v)!=R.end());}}
