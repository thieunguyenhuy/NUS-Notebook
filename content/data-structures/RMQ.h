/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Min Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b]) in constant time.
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
template<class T>
struct RMQ {
	vector<vector<T>> sparse;
	vector<int> loga;
	RMQ(const vector<T>& v) : sparse(1, v){
		loga.assign(sz(v) + 1, 0);
		for (int i = 2; i < loga.size(); i++) loga[i] = loga[i >> 1] + 1;
		for (int k = 1; (1 << k) <= sz(v); k++) {
			sparse.emplace_back(sz(v) - (1 << k) + 1);
			for(int j = 0; j < sz(sparse[k]); j++)
				sparse[k][j] = min(sparse[k - 1][j], sparse[k - 1][j + (1 << (k - 1))]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = loga[b - a + 1];
		return min(sparse[dep][a], sparse[dep][b - (1 << dep) + 1]);
	}
};
