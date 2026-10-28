#include "../utilities/template.h"
#include "../../content/data-structures/ImplicitTreap.h"

void visit(node*p,vi&a){if(!p)return;visit(p->le,a);a.push_back(p->x);visit(p->ri,a);assert(p->sz==(p->le?p->le->sz:0)+(p->ri?p->ri->sz:0)+1);}
void destroy(node*p){if(!p)return;destroy(p->le);destroy(p->ri);delete p;}
int main(){node*t=nullptr;vi a;mt19937 gen(7);for(int it=0;it<10000;++it){if(a.empty()||gen()%2){int k=gen()%(a.size()+1),x=gen();implicit_treap::insert(t,k,x);a.insert(a.begin()+k,x);}else{int k=gen()%a.size();implicit_treap::erase(t,k+1);a.erase(a.begin()+k);}vi got;visit(t,got);assert(got==a);}destroy(t);}
