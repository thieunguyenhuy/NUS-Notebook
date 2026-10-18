/**
 * Author: Le Pham Duy Khoa
 * Description: DSU with undo operations
 * Usage: Call get_sz() to get size of cc, 
 * rollback(k) to rollback k times, unite() and Findset()
 * to merge and find root.
 * Time: O(\log N)
 * Status: Tested on two problems
 */
struct node{
	int dsu = -1;
};
struct DsuRollback {
	vector<node> dsu; vector<pair<int, node>> st;
    int cc;
	DsuRollback(int n) : dsu(n + 5), cc(n) {}
	int get_sz(int i){ 
		return -dsu[Findset(i)].dsu; 
	}
	int Findset(int i){ 
		if(dsu[i].dsu < 0) return i;
		return Findset(dsu[i].dsu);
	}
	void rollback(int k){
        cc += k;
        k <<= 1;
        assert(k <= st.size());
		for (int i = sz(st) - 1; i >= sz(st) - k; i--)
			dsu[st[i].fi] = st[i].se;
        for(int bruh = 0; bruh < k; bruh++) st.pop_back();
	}
	//return false if already united, true otherwise.
	bool unite(int u, int v){
		u = Findset(u), v = Findset(v);
		if (u == v) return false;
        cc--;
		if (dsu[u].dsu < dsu[v].dsu) swap(u, v);
		st.push_back({u, dsu[u]});
		st.push_back({v, dsu[v]});
		dsu[v].dsu += dsu[u].dsu; dsu[u].dsu = v;
		return true;
	}
};
