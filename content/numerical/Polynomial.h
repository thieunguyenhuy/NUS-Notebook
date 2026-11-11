/**
 * Author: David Rydh, Per Austrin
 * Date: 2003-03-16
 * Description: Polynomial with coefficients in increasing degree order.
 * Evaluation uses Horner's method; diff() differentiates in place.
 * divroot(x0) divides by $(x-x_0)$ and discards the remainder.
 * Time: O(n) per operation
 */
#pragma once
struct Poly {
  vector<double> a;
  double operator()(double x) const {
    double val = 0;
    for (int i = (int)a.size() - 1; i >= 0; --i) val = val * x + a[i];
    return val;
  }
  void diff() {
    for (int i = 1; i < (int)a.size(); ++i) a[i - 1] = i * a[i];
    if (!a.empty()) a.pop_back();
  }
  void divroot(double x0) {
    if (a.empty()) return;
    double b = a.back(); a.back() = 0;
    for (int i = (int)a.size() - 2; i >= 0; --i) {
      double c = a[i];
      a[i] = a[i + 1] * x0 + b; b = c;
    }
    a.pop_back();
  }
};
