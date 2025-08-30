#include "power.hpp"

namespace power {

double naivePower(int x, int n) {
  if (x == 0) {
    return 0;
  }
  if (n == 0) {
    return 1;
  }
  return x * naivePower(x, n - 1);
}

double unoptimizedDCPower(int x, int n) {
  if (x == 0) {
    return 0;
  }
  if (n == 0) {
    return 1;
  }
  if (n % 2 == 0) {
    return unoptimizedDCPower(x, n / 2) * unoptimizedDCPower(x, n / 2);
  } else {
    return x * unoptimizedDCPower(x, n / 2) * unoptimizedDCPower(x, n / 2);
  }
}

double optimizedDCPower(int x, int n) {
  if (x == 0) {
    return 0;
  }
  if (n == 0) {
    return 1;
  }
  
  double temp = optimizedDCPower(x, n / 2);
  if (n % 2 == 0) {
    return temp * temp;
  } else {
    return x * temp * temp;
  }
}

}

