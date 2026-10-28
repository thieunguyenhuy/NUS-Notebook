#include "../utilities/template.h"
#include "../../content/strings/SuffixArray.h"

int main(){mt19937 rng(9);for(int it=0;it<10000;++it){int n=rng()%100;string s(n,0);for(char&c:s)c=rng()%8;SuffixArray sa(s);vi exp(n);iota(all(exp),0);sort(all(exp),[&](int a,int b){return s.substr(a)<s.substr(b);});assert(sa.sa==exp);for(int j=1;j<n;++j){int a=exp[j-1],b=exp[j],k=0;while(a+k<n&&b+k<n&&s[a+k]==s[b+k])++k;assert(sa.lcp[j]==k);}}}
