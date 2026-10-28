#include "../utilities/template.h"
#include "../../content/data-structures/Matrix.h"

Matrix slow(Matrix a, Matrix b){Matrix c(a.n,b.m);for(int i=0;i<a.n;++i)for(int j=0;j<b.m;++j)for(int k=0;k<a.m;++k)c[i][j]=(c[i][j]+(__uint128_t)a[i][k]*b[k][j])%Matrix::MOD;return c;}
int main(){
    mt19937 rng(3);Matrix empty(vector<vector<ll>>{});assert(empty.n==0 && empty.m==0);
    for(int it=0;it<500;++it){int n=1+rng()%12,m=1+rng()%12,k=1+rng()%12;
        Matrix a(n,m),b(m,k),c(k,n);for(auto*p:{&a,&b,&c})for(auto&r:p->val)for(auto&x:r)x=rng()%Matrix::MOD;
        assert((a*b).val==slow(a,b).val);assert(((a*b)*c).val==slow(slow(a,b),c).val);
    }
    Matrix a(vector<vector<ll>>{{-1,2},{3,-4}}),p(2,2);p[0][0]=p[1][1]=1;
    for(int e=0;e<30;++e){assert(a.binpow(e).val==p.val);p=slow(p,a);}
}
