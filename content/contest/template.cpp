//#pragma GCC optimize("O3,avx2,tune=native")
#include <bits/stdc++.h>
#include<cassert>
using namespace std;
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define fi first
#define se second
#define endl '\n'
#define MASK(i) (1ULL << (i))
#define BIT(n, i) (((n) >> (i)) & 1ULL)
#define LOG(n) (63 - __builtin_clzll(n))
template <class T> bool maximize(T &x, T y) { return x < y ? x = y, true : false; }
template <class T> bool minimize(T &x, T y) { return x > y ? x = y, true : false; }
const int N = 1e6 + 5;
void solve(){
    
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    if(fopen("input.txt", "r")){
        freopen("input.txt", "r", stdin);
    }
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}