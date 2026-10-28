#include "../utilities/template.h"
#include "../../content/data-structures/MoQueries.h"

vector<ll>values;ll total;
namespace MoAlgo {void add(int i,array<int,2>&){total+=values[i];}void remove(int i,array<int,2>&){total-=values[i];}T_ans calc(array<int,2>&){return total;}}
int main(){mt19937 gen(15);for(int it=0;it<300;++it){int n=1+gen()%30;values.resize(n);for(ll&x:values)x=(int)(gen()%100)-50;vector<pii>qs;vector<ll>exp;vector<vi>g(n);vi par(n);for(int v=1;v<n;++v){par[v]=gen()%v;g[v].push_back(par[v]);g[par[v]].push_back(v);}for(int j=0;j<100;++j){int l=gen()%n,r=gen()%n;if(l>r)swap(l,r);qs.push_back({l,r});exp.push_back(accumulate(values.begin()+l,values.begin()+r+1,0LL));}total=0;assert(MoAlgo::mo_inter(qs)==exp);for(int j=0;j<100;++j){auto[u,v]=qs[j];vi seen(n);for(int x=u;;x=par[x]){seen[x]=1;if(x==0)break;}int c=v;while(!seen[c])c=par[c];ll want=values[c];for(int x=u;x!=c;x=par[x])want+=values[x];for(int x=v;x!=c;x=par[x])want+=values[x];exp[j]=want;}total=0;assert(MoAlgo::mo_tree(qs,g)==exp);}}
