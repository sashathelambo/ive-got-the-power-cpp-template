#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>
#include <vector>

#include "src/power.hpp"

using clock_type = std::chrono::high_resolution_clock;
using ns = std::chrono::nanoseconds;

template <typename PowFn>
double measure_avg_ns(PowFn pow_fn, int x, int n, int trials) {
  volatile double sink = pow_fn(x, n);
  (void)sink;

  std::uint64_t total_ns = 0;
  for (int t = 0; t < trials; ++t) {
    auto start = clock_type::now();
    volatile double r = pow_fn(x, n);
    auto end = clock_type::now();
    (void)r;
    total_ns += std::chrono::duration_cast<ns>(end - start).count();
  }
  return static_cast<double>(total_ns) / static_cast<double>(trials);
}

bool approx_equal(double a, double b, double rel_eps = 1e-10, double abs_eps = 1e-12) {
  if (std::isinf(a) && std::isinf(b)) return true;
  if (std::isnan(a) || std::isnan(b)) return false;
  double diff = std::fabs(a - b);
  if (diff <= abs_eps) return true;
  double mag = std::max(std::fabs(a), std::fabs(b));
  return diff <= rel_eps * mag;
}

int main() {
  std::vector<int> xs = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> ns_vals = {1, 5, 10, 15, 20, 25, 30, 35, 40, 45};
  int trials = 10;

  std::cout << "=== Power Algorithm Performance Analysis ===" << '\n';
  std::cout << "Testing with " << trials << " trials per (x, n) pair" << '\n';
  std::cout << '\n';

  std::cout << "algorithm,x,n,avg_ns" << '\n';

  int correctness_issues = 0;

  for (int x : xs) {
    for (int n : ns_vals) {
      double r1 = power::naivePower(x, n);
      double r2 = power::unoptimizedDCPower(x, n);
      double r3 = power::optimizedDCPower(x, n);
      
      if (!(approx_equal(r1, r2) && approx_equal(r2, r3))) {
        std::cerr << "Warning: results differ for x=" << x << ", n=" << n << " => "
                  << r1 << ", " << r2 << ", " << r3 << '\n';
        correctness_issues++;
      }

      double t1 = measure_avg_ns(power::naivePower, x, n, trials);
      double t2 = measure_avg_ns(power::unoptimizedDCPower, x, n, trials);
      double t3 = measure_avg_ns(power::optimizedDCPower, x, n, trials);

      std::cout << "naivePower," << x << "," << n << "," << std::fixed << std::setprecision(2) << t1 << '\n';
      std::cout << "unoptimizedDCPower," << x << "," << n << "," << std::fixed << std::setprecision(2) << t2 << '\n';
      std::cout << "optimizedDCPower," << x << "," << n << "," << std::fixed << std::setprecision(2) << t3 << '\n';
    }
  }


  return 0;
}
