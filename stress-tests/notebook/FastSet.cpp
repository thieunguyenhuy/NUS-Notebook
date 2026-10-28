#include "../utilities/template.h"
#include "../../content/data-structures/FastSet.h"

int main(){
    auto fs=make_unique<FastSet>();set<int>s;mt19937 rng(2);
    assert(fs->get_min()==-1);assert(fs->get_max()==-1);
    assert(fs->get_next(~0ULL,64)==-1);assert(fs->get_prev(1ULL<<63,64)==63);
    for(int x:{1,63,64,4095,4096,FastSet::N}){fs->update(x);s.insert(x);}
    for(int it=0;it<100000;++it){
        int x=1+rng()%FastSet::N;
        if(rng()%2){fs->update(x);if(s.count(x))s.erase(x);else s.insert(x);}
        else{auto nx=s.lower_bound(x),pr=nx;int prev=pr==s.begin()?-1:*--pr;
            assert(fs->find_next(x)==(nx==s.end()?-1:*nx));assert(fs->find_prev(x)==prev);}
    }
    fs->init();assert(fs->get_min()==-1 && fs->get_max()==-1);
}
