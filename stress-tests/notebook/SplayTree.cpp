#include "../utilities/template.h"
#include "../../content/data-structures/SplayTree.h"

int check(Node* p, Node* par, vector<int>& seq) {
    if (!p) return 0;
    assert(p->parent == par);
    int l = check(p->child[0], p, seq); seq.push_back(p->value);
    int r = check(p->child[1], p, seq); assert(p->sz == l+r+1); return l+r+1;
}
int main(){
    mt19937 rng(1); vector<int> a;
    for(int it=0;it<20000;++it){
        int op=rng()%3;
        if(a.empty() || op==0){int k=rng()%(a.size()+1),v=(int)rng();tree.insert(k+1,v);a.insert(a.begin()+k,v);}
        else if(op==1){int k=rng()%a.size();tree.remove(k+1);a.erase(a.begin()+k);}
        else {int k=rng()%a.size();assert(tree.get(k+1)==a[k]);}
        vector<int> seq;check(tree.root,nullptr,seq);
        assert(seq.size()==a.size()+2);assert(equal(all(a),seq.begin()+1));
    }
}
