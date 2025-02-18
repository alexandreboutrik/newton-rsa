#ifndef METODOS_H_INCLUDED
#define METODOS_H_INCLUDED

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/fwd.hpp>
#include <cmath>
#include <cstdlib>
#include <optional>
#include <tuple>
#include <set>

using namespace std;
using namespace boost::multiprecision;

cpp_dec_float_50 bfmod(cpp_dec_float_50 x, cpp_dec_float_50 y) {
  return x - y * floor(x / y);
}

set<cpp_int> prime_factors(cpp_int n, int p) {

  set<cpp_int> factors;

  if (n == 1)
    return factors;

  if ((p * p) > n) {
    factors.insert(n);
    return factors;
  }

  if (n % p == 0) {
    factors.insert(p);
    set<cpp_int> rest = prime_factors(n / p, p);
    factors.insert(rest.begin(), rest.end());
  } else {
    set<cpp_int> rest = prime_factors(n, p + 1);
    factors.insert(rest.begin(), rest.end());
  }

  return factors;
}

cpp_int euler_totient(cpp_int n) {

  set<cpp_int> factors = prime_factors(n, 2);
  cpp_dec_float_50 phi = (cpp_dec_float_50) n;

  // Multiply the product (1 - (1/p)) for each prime factor p
  for (cpp_int p : factors)
    phi *= (1 - (1 / (cpp_dec_float_50) p));

  return (cpp_int) phi;
}

// Power Function with modulus
// Compute num pwq mod modulus
optional<cpp_int> pow(cpp_int a, cpp_int b, cpp_int n) {

  if (n == 0)
    return nullopt;

  if (b < 0) {
    cpp_int phi_n = euler_totient(n) - 1;
    return pow(a, phi_n, n);
  }

  cpp_int result = 1;

  while (b > 0) {
    if (b % 2 == 1)
      result = (result*a) % n;
    b = b / 2;
    a = (a*a) % n;
  }

  return result;
}

optional<cpp_int> eea(cpp_int a, cpp_int n) {

  cpp_int t = 0, new_t = 1;
  cpp_int r = n, new_r = a;

  while (new_r != 0) {
    cpp_int quotient = r / new_r; // Floor division

    cpp_int temp_t = t;
    t = new_t;
    new_t = temp_t - quotient * new_t;

    cpp_int temp_r = r;
    r = new_r;
    new_r = temp_r - quotient * new_r;
  }

  if (r > 1)
    return nullopt;

  if (t < 0)
    t += n;

  return t;
}

optional<cpp_int> flt(cpp_int a, cpp_int n) {

  if (gcd(a, n) != 1)
    return nullopt;

  return pow(a, -1, n);
}

tuple<cpp_dec_float_50,cpp_int> f_2(cpp_int a, cpp_int n) {

  cpp_int k = 0;
  cpp_dec_float_50 x = 1;

  while (1) {
    k += 1;

    cpp_dec_float_50 x_old = x;
    x = (x * (2 - (((cpp_dec_float_50)a * x) / (cpp_dec_float_50)n)));

    if (x_old == x)
      return {x,k};
  }

  exit(EXIT_FAILURE);
}

cpp_dec_float_50 f_1(cpp_int a, cpp_int n) {

  cpp_dec_float_50 x = 1;
  cpp_dec_float_50 f = ((cpp_dec_float_50) a * x) + 1; // F(d)
  cpp_dec_float_50 f_ = (cpp_dec_float_50) a;          // F'(d)
  
  cpp_dec_float_50 g = (x - (f / f_));
  cpp_dec_float_50 h = (cpp_dec_float_50) n;

  x = bfmod(g, h);

  return x;
}

optional<cpp_int> nr(cpp_int a, cpp_int n) {

  if (gcd(a, n) != 1)
    return nullopt;

  auto d1 = f_1(a, n);
  auto [d2, k] = f_2(a, n);

  cpp_int alpha = 1;
  for (; alpha < a; alpha++) {
    if ((round(bfmod(((cpp_dec_float_50)a * round(d1-(cpp_dec_float_50)alpha*d2)), (cpp_dec_float_50)n))) == 1)
      break;
  }

  cout << "f1: " << d1 << "--- f2: " << d2 << "--- alpha: " << alpha << endl;
  
  return (cpp_int) (d1-(cpp_dec_float_50)alpha*d2);
}

#endif // ! METODOS_H_INCLUDED

