/**
 * Author: Le Pham Duy Khoa
 * Description: Using Mo's Algorithm to answer tree path (vertex) or interval queries, 
 * adding/removing one element each step.
 * Usage: change block size and Type of ans in t_ans and blsz.
 * After that, fill in add, remove, calc, then call mo_inter(), mo_tree().
 * Note that the array/tree is 0-index.
 * Time: O(N \sqrt Q)
 * Status: tested on one tree problem and one interval problem.
 */
namespace MoAlgo{
    using T_ans = ll;
    const int blsz = 350; // block size
    //(inter[0], inter[1]) is the current interval/path BEFORE OPERATION
    void add(int idx, array<int, 2> &inter){} // add idx
    void remove(int idx, array<int, 2> &inter){} // remove idx
    T_ans calc(array<int, 2> &inter) {return ans;} 
    // compute current answer

    pii get_block(pii que){
        if((que. fi / blsz) & 1) que.se = -que.se;
        return {que.fi / blsz, que.se};   
    }
    vector<T_ans> mo_inter(vector<pii> que){
        array<int, 2> inter = {0, 0};
        add(0, inter);
        int &L = inter[0], &R = inter[1]; 
        vi order(sz(que));
        vector<ll> ans(sz(que));
        iota(all(order), 0);
        auto cmp = [&](int s, int t){ 
            return get_block(que[s]) < get_block(que[t]); 
        };
        sort(all(order), cmp);
        for (int qi : order){
            pii q = que[qi];
            while(L > q.fi){
                add(L - 1, inter); L--;
            }
            while(R < q.se){
                add(R + 1, inter); R++;
            }
            while(L < q.fi){
                remove(L, inter); L++;
            }
            while(R > q.se){
                remove(R, inter); R--;
            }
            ans[qi] = calc(inter);
        }
        return ans;
    }
    vector<T_ans> mo_tree(vector<pii> que, vector<vi>& graph, int root=0){
        int n = sz(graph);
        array<int, 2> path = {root, root};
        vi order(sz(que)), in(n), out(n), on_path(n), pa(n);
        vector<T_ans> ans(sz(que));
        int tim = 0;
        add(root, path), on_path[root] = 1;
        auto dfs = [&](int u, int p, auto& self) -> void {
            pa[u] = p;
            in[u] = tim; tim++;
            for (int v : graph[u]) if (v != p) self(v, u, self);
            out[u] = tim; tim++;
        };
        dfs(root, -1, dfs);
        iota(all(order), 0);
        auto cmp = [&](int s, int t){ 
            pii ps = {in[que[s].fi], in[que[s].se]};
            pii pt = {in[que[t].fi], in[que[t].se]};
            return get_block(ps) < get_block(pt); 
        };
        sort(all(order), cmp);
        for(int qi: order){
            vi tmp;
            tmp.reserve(n);
            auto move_end = [&](int &a, int b){
                auto step = [&](int c){
                    if (on_path[c]){
                        remove(a, path); on_path[a] = 0;
                    }
                    else{
                        add(c, path); on_path[c] = 1;
                    }
                    a = c;
                };
                for(;!(in[b] <= in[a] && in[a] <= out[b]); b = pa[b]){
                    tmp.push_back(b);
                }
                while (a != b) step(pa[a]);
                for(int i = (int)tmp.size() - 1; i >= 0; i--) step(tmp[i]);
                tmp.clear(),tmp.resize(0);
            };
            move_end(path[0], que[qi].fi);
            move_end(path[1], que[qi].se);
            ans[qi] = calc(path);
        }
        return ans;
    }
}
