/**
 * Author: Le Pham Duy Khoa
 * Description: A time segment tree, used to support deletion in a
 * DS that supports addition and rollback with an additional \log N factor.
 * Note that the queries from the DS has to be offline.
 * Usage: 
 * 1: Edit MAX_TIME, ope, Q (description below)
 * 2: Implement add(), rollback() and query() (description below)
 * 3: Turn the addition/deletion updates into tuples [x,l,r],
 * which means perform update x at time l and delete at time r + 1.
 * 4: Call update(l, r, x) on all tuples, then call solve_queries()
 * to solve the queries offline.
 * rollback(k) to rollback k times, unite() and Findset()
 * to merge and find root.
 * Time: O(T(n)\log N), where T(n) is the time complexity for the DS.
 * Status: Tested on one problem
 */
namespace segtree_time{ //time is 1-indexed
    //ope is the update type put into the segtree,
    //Q is the type of the query answers.
    using ope = pii;
    using Q = int;
    //MAX_TIME is the maximum time allowed
    const int MAX_TIME = 3e5;
    vector<vector<ope>> group(4 * MAX_TIME + 5);
    void update(int v, int TL, int TR, int l, int r, const ope &x){
        if(r < TL || l > TR) return;
        if(l <= TL && TR <= r){
            group[v].push_back(x); return;
        }
        int TM = ((TL + TR) >> 1);
        update(v << 1, TL, TM, l, r, x);
        update((v << 1) | 1, TM + 1, TR, l, r, x);
    }
    void update(int l, int r, const ope &x){
        assert(1 <= l && l <= r && r <= MAX_TIME);
        update(1, 1, MAX_TIME, l, r, x);
    }
    Q calc(int i){} //answer i-th query here
    void add(ope &x){} //do operation x to your DS here
    //rollback the last k operations of your DS here.
    //Note that ALL operations are counted, EVEN IF they don't change the DS.
    void rollback(int k){} 
    void DFS(int v, int TL, int TR, vector<pii> &que, int &ptr, vector<Q> &ans){
        if(ptr == que.size()) return;
        for(ope &x: group[v]) add(x);
        if(TL != TR){
            int TM=((TL + TR) >> 1);
            DFS(v << 1, TL, TM, que, ptr, ans);
            DFS((v << 1) | 1,TM + 1, TR, que, ptr, ans);
        }
        else{
            for(; ptr < que.size() && que[ptr].fi == TL; ptr++){
                ans[que[ptr].se] = calc(que[ptr].se);
            }
        }
        rollback(group[v].size());
    }
    //a query is of format {time_of_query, index_of_query}
    vector<Q> solve_queries(vector<pii> &queries){
        sort(queries.begin(), queries.end());
        int ptr = 0;
        vector<Q> ans(queries.size());
        DFS(1, 1, MAX_TIME, queries, ptr, ans);
        return ans;
    }
};
using namespace segtree_time;