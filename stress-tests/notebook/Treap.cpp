#include "../utilities/template.h"
#include "../../content/data-structures/Treap.h"

void visit(node*p,vi&a){if(!p)return;visit(p->le,a);a.push_back(p->x);visit(p->ri,a);assert(p->sz==(p->le?p->le->sz:0)+(p->ri?p->ri->sz:0)+1);}
int main(){node*t=nullptr;multiset<int>s;mt19937 gen(6);treap::insert(t,INT_MIN);treap::erase(t,INT_MIN);assert(t==nullptr);
    for(int it=0;it<10000;++it){int x=(int)(gen()%100)-50;if(gen()%2){treap::insert(t,x);s.insert(x);}else{treap::erase(t,x);s.erase(x);}vi a;visit(t,a);assert(a==vi(all(s)));}treap::destroy(t);}
