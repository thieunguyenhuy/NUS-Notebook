// Compile without the notebook's rep, sz, all, vi, or pii macros/aliases.
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = long long;
namespace polynomial {
#include "../../content/numerical/Polynomial.h"
#include "../../content/numerical/PolyRoots.h"
#include "../../content/numerical/PolyInterpolate.h"
}
namespace recurrence {
#include "../../content/numerical/LinearRecurrence.h"
ll modpow(ll a, ll e) {
  ll res = 1;
  for (; e; e >>= 1, a = a * a % mod) if (e & 1) res = res * a % mod;
  return res;
}
#include "../../content/numerical/BerlekampMassey.h"
#include "../../content/numerical/MatrixInverse-mod.h"
}
namespace matrices {
#include "../../content/numerical/Determinant.h"
#include "../../content/numerical/MatrixInverse.h"
#include "../../content/numerical/GaussElimination.h"
#include "../../content/numerical/Tridiagonal.h"
}
namespace integerDet {
#include "../../content/numerical/IntDeterminant.h"
}
namespace binary {
#include "../../content/numerical/GaussElimination2.h"
}
namespace optimization {
#include "../../content/numerical/GoldenSectionSearch.h"
#include "../../content/numerical/Simplex.h"
}
namespace fourier {
#include "../../content/numerical/FastFourierTransform.h"
}
namespace modularFourier {
#include "../../content/numerical/FastFourierTransformMod.h"
}
namespace numberTheoretic {
#include "../../content/numerical/NumberTheoreticTransform.h"
}
namespace online {
#include "../../content/numerical/NTTOnline.h"
}
namespace subset {
#include "../../content/numerical/FastSubsetTransform.h"
}
mt19937 rng(1234567);
int rnd(int n) { return int(rng() % n); }
bool near(double a, double b, double eps = 1e-7) {
  return abs(a - b) <= eps * max({1.0, abs(a), abs(b)});
}
void testPolynomials() {
  polynomial::Poly empty;
  empty.diff(); empty.divroot(3); assert(empty(7) == 0);
  assert(polynomial::interpolate({}, {}, 0).empty());
  assert(polynomial::polyRoots({{}}, -10, 10).empty());
  assert(polynomial::polyRoots({{1}}, -10, 10).empty());
  assert(polynomial::polyRoots({{-20, 1}}, -10, 10).empty());
  assert(polynomial::polyRoots({{1, 0, 1}}, -10, 10).empty());
  assert(polynomial::polyRoots({{-1, 1, 0}}, -1, 1) == vector<double>{1});
  assert(polynomial::polyRoots({{1, -2, 1}}, 1, 1) == vector<double>{1});
  for (int it = 0; it < 500; ++it) {
    polynomial::Poly p{{1}};
    vector<double> expected;
    int n = 1 + rnd(6);
    for (int j = 0; j < n; ++j) {
      double root = rnd(9) - 4;
      expected.push_back(root);
      vector<double> a(p.a.size() + 1);
      for (int k = 0; k < (int)p.a.size(); ++k) {
        a[k] -= root * p.a[k]; a[k + 1] += p.a[k];
      }
      p.a = a;
    }
    sort(expected.begin(), expected.end());
    expected.erase(unique(expected.begin(), expected.end()), expected.end());
    auto roots = polynomial::polyRoots(p, -4, 4);
    if (roots.size() != expected.size()) {
      cerr << "Coefficients:"; for (double v : p.a) cerr << ' ' << v;
      cerr << "\nExpected:"; for (double v : expected) cerr << ' ' << v;
      cerr << "\nActual:"; for (double v : roots) cerr << ' ' << setprecision(17) << v;
      cerr << '\n'; abort();
    }
    for (int i = 0; i < (int)roots.size(); ++i) assert(near(roots[i], expected[i]));
    auto q = p; double root = expected[0]; q.divroot(root);
    for (double x : {-2.5, 0.5, 7.0}) assert(near(p(x), (x - root) * q(x)));
    vector<double> x(n + 1), y(n + 1);
    for (int i = 0; i <= n; ++i) { x[i] = i - 3; y[i] = p(x[i]); }
    auto a = polynomial::interpolate(x, y, n + 1);
    for (int i = 0; i <= n; ++i) assert(near(a[i], p.a[i]));
  }
}
void testRecurrences() {
  using namespace recurrence;
  assert(berlekampMassey({}).empty());
  assert(berlekampMassey({0, 0, 0}).empty());
  assert(linearRec({3}, {1}, LLONG_MAX) == 3);
  for (int it = 0; it < 1000; ++it) {
    int n = 1 + rnd(8);
    vector<ll> s(100), tr(n);
    for (ll &x : tr) x = rnd(mod);
    for (int i = 0; i < n; ++i) s[i] = rnd(mod);
    for (int i = n; i < (int)s.size(); ++i)
      for (int j = 0; j < n; ++j) s[i] = (s[i] + s[i - j - 1] * tr[j]) % mod;
    auto recovered = berlekampMassey(vector<ll>(s.begin(), s.begin() + 2 * n));
    assert((int)recovered.size() <= n);
    for (int i = 2 * n; i < (int)s.size(); ++i) {
      ll value = 0;
      for (int j = 0; j < (int)recovered.size(); ++j)
        value = (value + recovered[j] * s[i - j - 1]) % mod;
      assert(value == s[i]);
    }
    for (int k : {0, n - 1, n, 37, 99}) assert(linearRec(s, tr, k) == s[k]);
  }
}
ll bruteDet(const vector<vector<ll>> &a) {
  int n = (int)a.size(); vector<int> p(n); iota(p.begin(), p.end(), 0);
  ll result = 0;
  do {
    ll product = 1; int parity = 0;
    for (int i = 0; i < n; ++i) {
      product *= a[i][p[i]];
      for (int j = 0; j < i; ++j) parity ^= (p[j] > p[i]);
    }
    result += parity ? -product : product;
  } while (next_permutation(p.begin(), p.end()));
  return result;
}
int modRank(vector<vector<ll>> a) {
  int n = (int)a.size(), rank = 0;
  for (int col = 0; col < n; ++col) {
    int pivot = rank;
    while (pivot < n && !a[pivot][col]) ++pivot;
    if (pivot == n) continue;
    swap(a[pivot], a[rank]);
    ll inv = recurrence::modpow(a[rank][col], recurrence::mod - 2);
    for (int i = rank + 1; i < n; ++i) {
      ll factor = a[i][col] * inv % recurrence::mod;
      for (int j = col; j < n; ++j)
        a[i][j] = (a[i][j] - factor * a[rank][j] % recurrence::mod + recurrence::mod) % recurrence::mod;
    }
    ++rank;
  }
  return rank;
}
void testMatrices() {
  for (int it = 0; it < 500; ++it) {
    int n = rnd(6);
    vector<vector<ll>> a(n, vector<ll>(n)), modular = a;
    vector<vector<double>> real(n, vector<double>(n));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
      a[i][j] = rnd(11) - 5;
      real[i][j] = a[i][j];
      modular[i][j] = (a[i][j] % recurrence::mod + recurrence::mod) % recurrence::mod;
    }
    ll expected = bruteDet(a), md = integerDet::mod;
    auto acopy = a; auto rcopy = real;
    assert(integerDet::det(acopy) == (expected % md + md) % md);
    assert(near(matrices::det(rcopy), expected));
    auto inverse = real;
    int rank = matrices::matInv(inverse);
    assert((rank == n) == (expected != 0));
    if (rank == n) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
      double value = 0;
      for (int k = 0; k < n; ++k) value += real[i][k] * inverse[k][j];
      assert(near(value, i == j));
    }
    auto minv = modular;
    int mrank = recurrence::matInv(minv);
    assert(mrank == modRank(modular));
    if (mrank == n) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
      ll value = 0;
      for (int k = 0; k < n; ++k) value = (value + modular[i][k] * minv[k][j]) % recurrence::mod;
      assert(value == (i == j));
    }
  }
  vector<double> ans;
  vector<vector<double>> a;
  assert(matrices::gauss(a, ans) == 1);
  ans.resize(3); assert(matrices::gauss(a, ans) == 2);
  a = {{1, 1, 3}, {1, -1, 1}};
  assert(matrices::gauss(a, ans) == 1 && near(ans[0], 2) && near(ans[1], 1));
  a = {{1, 1, 2}, {2, 2, 5}}; assert(matrices::gauss(a, ans) == 0);
  a = {{1, 1, 2}}; assert(matrices::gauss(a, ans) == 2);
  a = {{1}}; assert(matrices::gauss(a, ans) == 0);
  assert(matrices::tridiagonal({0, 2}, {1}, {1}, {3, 8}) == vector<double>({2, 3}));
  for (int it = 0; it < 500; ++it) {
    int n = rnd(40);
    vector<double> diag(n, 5), super(max(0, n - 1), -1), sub = super, x(n), b(n);
    for (double &v : x) v = rnd(21) - 10;
    for (int i = 0; i < n; ++i) {
      b[i] = diag[i] * x[i];
      if (i) b[i] += sub[i - 1] * x[i - 1];
      if (i + 1 < n) b[i] += super[i] * x[i + 1];
    }
    auto solution = matrices::tridiagonal(diag, super, sub, b);
    for (int i = 0; i < n; ++i) assert(near(solution[i], x[i]));
  }
}
void testBinary() {
  using namespace binary::Gauss;
  for (int it = 0; it < 1000; ++it) {
    int rows = rnd(8), cols = rnd(7);
    vector<T> input(rows);
    for (T &row : input) for (int j = 0; j <= cols; ++j) row[j] = rnd(2);
    auto satisfies = [&](T x, bool homogeneous) {
      for (const T &row : input) {
        bool lhs = false;
        for (int j = 0; j < cols; ++j) lhs ^= row[j] && x[j];
        if (lhs != (homogeneous ? false : row[cols])) return false;
      }
      return true;
    };
    int count = 0;
    for (int mask = 0; mask < (1 << cols); ++mask) count += satisfies(T(mask), false);
    init(rows, cols, input); int rank = gauss();
    assert((rank == -1) == (count == 0));
    if (rank == -1) continue;
    assert(count == (1 << (cols - rank)) && satisfies(ans, false));
    auto basis = get_basis(); assert((int)basis.size() == cols - rank);
    for (T v : basis) assert(v.any() && satisfies(v, true));
  }
}
void testTransforms() {
  vector<fourier::C> emptyFFT; fourier::fft(emptyFFT);
  vector<ll> emptyNTT; numberTheoretic::ntt(emptyNTT);
  assert(online::multiply({}, {1}).empty());
  for (int it = 0; it < 500; ++it) {
    int n = rnd(45), m = rnd(45), size = n && m ? n + m - 1 : 0;
    vector<double> a(n), b(m), c(size);
    vector<int> ai(n), bi(m), ci(size);
    vector<ll> al(n), bl(m), cl(size);
    for (int i = 0; i < n; ++i) { a[i] = rnd(201) - 100; ai[i] = al[i] = rnd(10000); }
    for (int i = 0; i < m; ++i) { b[i] = rnd(201) - 100; bi[i] = bl[i] = rnd(10000); }
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
      c[i + j] += a[i] * b[j];
      ci[i + j] = (ci[i + j] + (ll)ai[i] * bi[j]) % modularFourier::FFT::MOD;
      cl[i + j] = (cl[i + j] + al[i] * bl[j]) % numberTheoretic::mod;
    }
    auto fc = fourier::conv(a, b); assert(fc.size() == c.size());
    for (int i = 0; i < size; ++i) assert(near(fc[i], c[i]));
    assert(modularFourier::FFT::multiply(ai, bi) == ci);
    assert(numberTheoretic::conv(al, bl) == cl);
    auto oc = online::multiply(ai, bi); assert(oc.size() == cl.size());
    for (int i = 0; i < size; ++i) assert(oc[i] == cl[i]);
    int k = 1 << rnd(6); ai.resize(k); bi.resize(k); ci.assign(k, 0);
    for (int i = 0; i < k; ++i) { ai[i] = rnd(11) - 5; bi[i] = rnd(11) - 5; }
    for (int i = 0; i < k; ++i) for (int j = 0; j < k; ++j) ci[i & j] += ai[i] * bi[j];
    assert(subset::conv(ai, bi) == ci);
  }
  for (int it = 0; it < 100; ++it) {
    int n = 1 + rnd(150);
    online::OnlineConvolution conv(n);
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
      a[i] = rnd(online::mod); b[i] = rnd(online::mod);
      ll expected = 0;
      for (int j = 0; j <= i; ++j) expected = (expected + (ll)a[j] * b[i - j]) % online::mod;
      assert(conv.extend(i, a[i], b[i]) == expected);
    }
  }
}
void testOptimization() {
  using namespace optimization;
  assert(near(gss(-100, 100, [](double x) { return (x - 2) * (x - 2); }), 2));
  double lower = 1e20, upper = lower + 1e6;
  double point = gss(lower, upper, [](double x) { return x; });
  assert(lower <= point && point <= upper);
  vd x;
  assert(LPSolver({}, {}, {}).solve(x) == 0);
  assert(LPSolver({}, {}, {1}).solve(x) == inf);
  assert(LPSolver({}, {}, {-1}).solve(x) == 0 && x == vd{0});
  assert(LPSolver({{}}, {-1}, {}).solve(x) == -inf);
  assert(LPSolver({{}}, {1}, {}).solve(x) == 0);
  assert(LPSolver({{1}, {-1}}, {0, -1}, {1}).solve(x) == -inf);
  assert(LPSolver({{-1}, {-1}}, {-1, -1}, {-1}).solve(x) == -1);
  for (int it = 0; it < 1000; ++it) {
    // Bounded 2D programs; enumerate every candidate vertex independently.
    vvd A = {{1, 0}, {0, 1}};
    vd b = {double(1 + rnd(10)), double(1 + rnd(10))};
    vd c = {double(rnd(11) - 5), double(rnd(11) - 5)};
    for (int i = 0; i < 5; ++i) { A.push_back({double(rnd(11) - 5), double(rnd(11) - 5)}); b.push_back(rnd(21) - 5); }
    vvd edges = A; vd limits = b;
    edges.push_back({-1, 0}); limits.push_back(0);
    edges.push_back({0, -1}); limits.push_back(0);
    double expected = -inf;
    for (int i = 0; i < (int)edges.size(); ++i) for (int j = 0; j < i; ++j) {
      double d = edges[i][0] * edges[j][1] - edges[i][1] * edges[j][0];
      if (abs(d) < 1e-9) continue;
      double u = (limits[i] * edges[j][1] - edges[i][1] * limits[j]) / d;
      double v = (edges[i][0] * limits[j] - limits[i] * edges[j][0]) / d;
      bool valid = true;
      for (int k = 0; k < (int)edges.size(); ++k)
        if (edges[k][0] * u + edges[k][1] * v > limits[k] + 1e-7) valid = false;
      if (valid) expected = max(expected, c[0] * u + c[1] * v);
    }
    double actual = LPSolver(A, b, c).solve(x);
    if (expected == -inf) assert(actual == -inf);
    else {
      assert(isfinite(actual) && near(actual, expected));
      assert(x[0] >= -1e-7 && x[1] >= -1e-7);
      for (int i = 0; i < (int)A.size(); ++i) assert(A[i][0] * x[0] + A[i][1] * x[1] <= b[i] + 1e-7);
    }
  }
}
int main() {
  testPolynomials(); testRecurrences(); testMatrices(); testBinary();
  testTransforms(); testOptimization();
  cout << "Numerical regression tests passed (all 19 headers).\n";
}
