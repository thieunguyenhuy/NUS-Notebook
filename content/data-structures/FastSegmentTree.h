/**
 * Author: Thieu Nguyen Huy
 * Description: Non-recursion segment tree with point updates and range sum queries.
 * Usage: Call mytree.resize(n, a) before any operations.
 * Time: O(\log N) for each operation
 * Status: Well-tested
 */

struct SegmentTree {
    vector<ll> nodes;
    int n;

    SegmentTree() {}
    
    void resize(int _n, int a[]){
        // pass length and the initial array
        n = _n; nodes.assign(2 * n + 5, 0);
        build(a);
    }
    void build(int a[]) { // 1-index
        for (int i = 1; i <= n; ++i) nodes[i + n] = a[i];
        for (int i = n; i > 0; --i)
            nodes[i] = nodes[i << 1] + nodes[i << 1 | 1];
    }

    void update(int p, int val) {
        //update add
        for (nodes[p += n] += val; p >>= 1;)
            nodes[p] = nodes[p << 1] + nodes[p << 1 | 1];
    }

    ll get(int l, int r) {
        ll ansL = 0, ansR = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ansL = ansL + nodes[l++];
            if (r & 1) ansR = nodes[--r] + ansR;
        }
        return ansL + ansR;
    }
} mytree;