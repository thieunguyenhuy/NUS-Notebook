#include "../utilities/template.h"
#include "../../content/math/MillerRabin.h"

int main(){for(int n=0;n<100000;++n){bool prime=n>=2;for(int d=2;d*d<=n;++d)if(n%d==0){prime=false;break;}assert(MillerRabin::isPrime(n)==prime);}assert(!MillerRabin::isPrime(341550071728321ULL));assert(MillerRabin::isPrime(18446744073709551557ULL));}
