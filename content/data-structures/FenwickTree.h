/**
 * Author: Le Pham Duy Khoa
 * Description: Computes prefix sums a[1] + ... + a[i], point update (a[i] += x) 
 * and finding lower bound for prefix sums
 * Time: $O(\log n)$.
 * Status: Tested on one problem.
 */
struct fenwick{
    vector<ll> bit;
    int n;
    fenwick(int n) : bit(n + 1), n(n) {};
    void update(int i, ll x){
        for(; i < bit.size(); i += (i&(-i))){
            bit[i] += x;
        }
    }
    ll query(int i){
        ll curr=0;
        for(;i; i -= (i & (-i))){
            curr += bit[i];
        }
        return curr;
    }
    ll range(int l, int r){
        return (query(r) - query(l - 1));
    }
    //find first position such that sum >= x (non-empty)
    int lower_bound(int x){
        int pos = 0;
        ll sum = 0;
        for(int i = __lg(n); i>=0; i--){
            if(pos + (1 << i) < bit.size() && bit[pos + (1 << i)] + sum < x){
                sum += bit[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos + 1;
    }
};