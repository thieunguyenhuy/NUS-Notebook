#include "../utilities/template.h"
#include "../../content/data-structures/PersistentLazyIT.h"

int main(){
    const int n=31;mytree.resize(n);vector<int> roots{0};vector<vector<ll>> hist(1,vector<ll>(n));mt19937 rng(4);
    for(int it=0;it<8000;++it){int ver=rng()%roots.size(),l=rng()%n,r=rng()%n;if(l>r)swap(l,r);
        if(rng()%2){ll v=(ll)(int)rng()*10;auto a=hist[ver];for(int j=l;j<=r;++j)a[j]+=v;
            roots.push_back(mytree.update(roots[ver],l+1,r+1,v));hist.push_back(a);}
        else{auto before=nodes.size();assert(mytree.get(roots[ver],l+1,r+1)==accumulate(hist[ver].begin()+l,hist[ver].begin()+r+1,0LL));assert(nodes.size()==before);}
    }
    for(int i=0;i<(int)roots.size();++i)assert(mytree.get(roots[i],1,n)==accumulate(all(hist[i]),0LL));
}
