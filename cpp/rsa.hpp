#ifndef RSA_H_INCLUDED
#define RSA_H_INCLUDED

#include <stdexcept>
#include <optional>

#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

bool is_prime(cpp_int n) {

  if (n < 2)
    return false;

  cpp_int sq = (n / 2) + 1;
  for (int i = 2; i < sq; i++)
    if ((n % i) == 0)
      return false;

  return true;
}

optional<cpp_int> generate_e(cpp_int phi) {

  for (int e = 2; e < phi; e++)
    if (gcd(e, phi) == 1)
      return e;

  return nullopt;
}

cpp_int handle_nullopt(optional<cpp_int> n, const char *re) {
  if (n)
    return n.value();

  throw runtime_error(re);
}

#endif // RSA_H_INCLUDED
