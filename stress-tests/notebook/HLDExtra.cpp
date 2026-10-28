#include "../utilities/template.h"
#include "../../content/graph/HLD.h"
int main() {
    mt19937 gen(19);
    for (int it = 0; it < 100; ++it) {
        int n = 1 + gen() % 50;
        vector<vi> graph(n); vi par(n), depth(n), vals(n);
        for (int v = 1; v < n; ++v) {
            par[v] = gen() % v; depth[v] = depth[par[v]] + 1;
            graph[v].push_back(par[v]); graph[par[v]].push_back(v);
        }
        HLD<false> hld(graph); hld.tree->set(0, n, 0);
        for (int q = 0; q < 1000; ++q) {
            int u = gen() % n, v = gen() % n; vi path;
            int a = u, b = v;
            while (a != b) {
                if (depth[a] < depth[b]) swap(a, b);
                path.push_back(a); a = par[a];
            }
            path.push_back(a);
            if (gen() % 2) {
                int x = (int)(gen() % 100) - 50;
                hld.modifyPath(u, v, x); for (int p : path) vals[p] += x;
            } else {
                int want = INT_MIN; for (int p : path) want = max(want, vals[p]);
                assert(hld.queryPath(u, v) == want);
            }
        }
        // The snippet intentionally uses an owning raw pointer; clean up in the test.
        auto destroy = [&](Node* p, auto& self) -> void {
            if (!p) return; self(p->l, self); self(p->r, self); delete p;
        };
        destroy(hld.tree, destroy);
    }
}
