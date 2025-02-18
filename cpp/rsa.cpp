#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

#include "metodos.hpp"

using namespace std;
using namespace boost::multiprecision;

bool is_prime(cpp_int n) {

  // Check if a number is prime using the trivial division method.

  if (n < 2)
    return false;

  cpp_int sq = (n / 2) + 1;
  for (int i = 2; i < sq; i++) {
    if ((n % i) == 0)
      return false;
  }
  return true;
}

optional<cpp_int> generate_e(cpp_int phi) {

  // Generate the smallest possible 'e' such that (1 < e < phi) and gcd(e, phi)
  // = 1. Returns None if no valid 'e' exists.

  for (int e = 2; e < phi; e++) {
    if (gcd(e, phi) == 1)
      return e;
  }
  return nullopt;
}

cpp_int handle_nullopt(optional<cpp_int> n) {
  if (n)
    return n.value();

  return -1;
}

int main() {

  // Step 0
  cpp_int x;
  cout << "Enter the message 'x': ";
  cin >> x;

  // Step 1: Generate the modulus 'n'
  cpp_int p;
  cout << "Enter 'p': ";
  cin >> p;
  if (is_prime(p) == false)
    cout << "p is not a prime number" << endl;
  cpp_int q;
  cout << "Enter 'q': ";
  cin >> q;
  if (is_prime(q) == false)
    cout << "q is not a prime number" << endl;

  cpp_int n = p * q;

  // Step 2: Compute the totient of the modulus 'phi'
  cpp_int phi_var = (p - 1) * (q - 1);

  // Step 3: Generate the parameter 'e'
  cpp_int e = handle_nullopt(generate_e(phi_var));

  // Step 4: Compute the parameter 'd'
  cpp_int d_eea = handle_nullopt(eea(e, phi_var)); // EEA - Extended Euclidean Algorithm
  cpp_int d_flt = handle_nullopt(flt(e, phi_var)); // FLT - Fermat's Little Theorem
  cpp_int d_nr  = handle_nullopt(nr(e, phi_var));
  //cpp_int d_f1 = f_1(e, phi_var);                  // NR - Newton-Raphson
  //auto [d_f2, k] = f_2(e, phi_var);       // Correction Function

  // Step 5: Cryptographic function 'ex', 'dx'
  cpp_int ex = handle_nullopt(pow(x, e, n)); // Encrypt using the public key
  cpp_int dx = handle_nullopt(pow(ex, d_eea, n)); // Descrypt using the private key
  if (dx != x)
    cout << "something went wrong in 'D(x)'" << endl;

  cpp_int sx = handle_nullopt(pow(x, d_eea, n)); // Encrypt using the public key
  cpp_int vx = handle_nullopt(pow(sx, e, n));    // Descrypt using the private key
  if (vx != x)
    cout << "something went wrong in 'V(x)'" << endl;

  cout << "\nE(" << x << ") = " << ex << " ; " << "D(x) = " << dx << endl;
  cout << "\nS(" << x << ") = " << sx << " ; " << "V(x) = " << vx << endl;

  cout << "\nPublic Key: (e=" << e << ", n=" << n << ")" << endl;
  cout << "\nPrivate Key: (p=" << p << ", q=" << q << ", d=" << d_eea << ")"
       << endl;

  cout << "\n(Debug) 'd' parameter (private exponent): " << endl;
  cout << "  EEA:          " << d_eea << endl;
  cout << "  FLT:          " << d_flt << endl;
  cout << "  NR :          " << d_nr << endl;
  //cout << "NR f2:          " << d_f2 << ", iteractions: " << k << endl;

  return 0;
}
