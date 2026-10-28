/**
 * Author: Thieu Nguyen Huy
 * Description: Fast set for sets that only have integers in [1, N]
 * Time: O(log64(n)) for update and lowerbound, upperbound
 * Status: Well-tested
 * Usage: call init() first
 * Memory: O(N)
 * Status: Well-tested
 */
struct FastSet {
    static const int N = 250000 + 5;
    static const int BLOCK = 64;
    static const int LAYER = 3;
    uint64_t a[N + 5]{};
    int layer_start[LAYER];
    FastSet(){
        int start = 0, pos = 1;
        for(int i = 0; i < LAYER; ++i) {
            layer_start[i] = start;
            start += pos;
            pos = pos * BLOCK;
        }
    }
    void init() { fill(a, a + N + 5, 0); }

    void update(int x) {
        assert(1 <= x && x <= N);
        //add if x not in set and vice versa
        int id = x >> 6, prev = layer_start[LAYER - 1] + id;
        a[prev] ^= (1ULL << (x & (BLOCK - 1)));
        for (int i = LAYER - 2; i >= 0; --i) {
            x >>= 6, id >>= 6;
            int digit = x & (BLOCK - 1), cur = id + layer_start[i];
            if ((a[prev] > 0) != ((a[cur] >> digit) & 1ULL)) a[cur] ^= (1ULL << digit);
            prev = cur;
        }
    }

    int get_next(uint64_t mask, int l) {
        if (l >= BLOCK) return -1;
        mask &= ~uint64_t(0) << l;
        return mask ? __builtin_ctzll(mask) : -1;
    }

    int find_next(int x) { // return first ele >= x or -1 if no ele
        int id = x >> 6;
        int foo = get_next(a[id + layer_start[LAYER - 1]], x & (BLOCK - 1));
        if (foo != -1) return x - (x & (BLOCK - 1)) + foo;
        x >>= 6, id >>= 6;
        for (int i = LAYER - 2; i>=0; --i) {
            int digit = (x & (BLOCK - 1)) + 1;
            int cur = layer_start[i] + id;
            int foo = get_next(a[cur], digit);
            if (foo != -1) {
                id = (id << 6) + foo;
                for (int j = i + 1; j < LAYER; ++j) {
                    int digit = __builtin_ctzll(a[id + layer_start[j]]);
                    id = (id << 6) + digit;
                }
                return id;
            }
            x >>= 6, id >>= 6;
        }
        return -1;
    }

    int get_prev(uint64_t mask, int l) {
        if (l < BLOCK) mask &= (1ULL << l) - 1;
        return mask ? 63 - __builtin_clzll(mask) : -1;
    }

    int find_prev(int x) { // return last ele < x or -1 if no ele
        int id = x >> 6;
        int foo = get_prev(a[id + layer_start[LAYER - 1]], x & (BLOCK - 1));
        if (foo != -1) return x - (x & (BLOCK - 1)) + foo;
        x >>= 6, id >>= 6;
        for(int i = LAYER - 2; i>=0; --i) {
            int digit = (x & (BLOCK - 1)) + 1;
            int cur = layer_start[i] + id;
            int foo = get_prev(a[cur], digit - 1);
            if (foo != -1) {
                id = (id << 6) + foo;
                for(int j = i + 1; j < LAYER; ++j) {
                    int digit = (63 - __builtin_clzll(a[id + layer_start[j]]));
                    id = (id << 6) + digit;
                }
                return id;
            }
            x >>= 6, id >>= 6;
        }
        return -1;
    }

    int get_min() {
        return find_next(1);
    }

    int get_max() {
        return find_prev(N + 1);
    }
};