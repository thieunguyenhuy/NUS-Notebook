#include "../utilities/template.h"
#include "../../content/math/FastFourierTransform.h"

int main(){mt19937 rng(12);for(int it=0;it<1000;++it){vi a(rng()%50),b(rng()%50);for(int&x:a)x=(int)(rng()%1000)-500;for(int&x:b)x=(int)(rng()%1000)-500;vi c(a.empty()||b.empty()?0:a.size()+b.size()-1);for(int i=0;i<(int)a.size();++i)for(int j=0;j<(int)b.size();++j)c[i+j]=(c[i+j]+(ll)a[i]*b[j]%FFT::MOD+FFT::MOD)%FFT::MOD;assert(FFT::multiply(a,b)==c);}}
