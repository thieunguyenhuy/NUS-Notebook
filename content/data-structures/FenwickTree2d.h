/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums a[i,j] for all i<=I, j<=J, and increases single elements a[i,j].
 * Usage: Requires update positions to be known in advance 
 * in form vector<pair<int,int>> as constructor for FT2, or construct with limX only and call fakeUpdate().
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 * Status: stress-tested
 */
struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw - 1] < sum)
				pos += pw, sum -= s[pos - 1];
		}
		return pos;
	}
};

struct FT2 {
	vector<vi> ys; vector<FT> ft;
    bool call_init = false;
	void fakeUpdate(int x, int y) {
		for (; x < sz(ys); x |= x + 1) ys[x].push_back(y);
	}
	FT2(int limx, vector<pair<int,int>> &updates){
        ys.resize(limx + 5);
		for(auto [x, y]: updates) fakeUpdate(x, y);
		init();
	}
	FT2(int limx) : ys(limx + 5) {}
	void init() {
        call_init = true;
		for (vi& v : ys) sort(all(v)), ft.emplace_back(sz(v));
	}
	int ind(int x, int y) {
		return (int)(lower_bound(all(ys[x]), y) - ys[x].begin()); }
	void update(int x, int y, ll dif) {
        if(!call_init) init();
		for (; x < sz(ys); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	ll query(int x, int y) { //calculates sum for <=x, <=y.
        if(!call_init) init();
        x++, y++;
		ll sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x - 1].query(ind(x - 1, y));
		return sum;
	}
};
