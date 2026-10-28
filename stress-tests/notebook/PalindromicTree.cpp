#include "../utilities/template.h"
#include "../../content/strings/PalindromicTree.h"

int main(){mt19937 rng(10);for(int it=0;it<2000;++it){PalindromicTree::init();string s;set<string> pal;int n=rng()%60;for(int i=0;i<n;++i){char c='a'+rng()%4;s+=c;PalindromicTree::add_letter(c-'a');for(int j=0;j<=i;++j){string t=s.substr(j),u=t;reverse(all(u));if(t==u)pal.insert(t);}assert(PalindromicTree::sz==(int)pal.size()+2);}}}
