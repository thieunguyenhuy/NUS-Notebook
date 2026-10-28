#include "../utilities/template.h"
#include "../../content/strings/SuffixAutomaton.h"

int main(){mt19937 gen(18);for(int it=0;it<1000;++it){SuffixAutomaton sam;set<string>sub;for(int j=0;j<5;++j){string s;int p=0,n=gen()%15;for(int i=0;i<n;++i){char c=gen()%3;s+=c;p=sam.addc(p,c);}for(int l=0;l<n;++l)for(int r=l+1;r<=n;++r)sub.insert(s.substr(l,r-l));}for(int len=1;len<=5;++len){int cnt=1;for(int j=0;j<len;++j)cnt*=3;for(int code=0;code<cnt;++code){string s;int x=code,p=0;for(int j=0;j<len;++j){char c=x%3;x/=3;s+=c;if(p!=-1)p=sam.g[p].nxt[c];}assert((p!=-1)==bool(sub.count(s)));}}}}
