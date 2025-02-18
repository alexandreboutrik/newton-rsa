#include <iostream>
#include <stdexcept>

#include <boost/multiprecision/cpp_int.hpp>

#include "rsa.hpp"
#include "metodos.hpp"

int main() {

  cpp_int x;
  cout << "Enter the message 'x': "; cin >> x;

  // Step 1: Generate the modulus 'n'
  cpp_int p, q;

  cout << "Enter 'p': "; cin >> p;
  if (is_prime(p) == false)
    throw runtime_error("p is not a prime number");

  cout << "Enter 'q': "; cin >> q;
  if (is_prime(q) == false)
    throw runtime_error("q is not a prime number");

  cpp_int n = p * q;

  // Step 2: Compute the totient of the modulus 'phi'
  cpp_int phi_var = (p - 1) * (q - 1);

  // Step 3: Generate the parameter 'e'
  cpp_int e = handle_nullopt(generate_e(phi_var), "'generate_e'");

  // Step 4: Compute the parameter 'd'
  cpp_int d_eea = handle_nullopt(eea(e, phi_var), "'eea'");  // EEA - Extended Euclidean Algorithm
  cpp_int d_fet = handle_nullopt(fet(e, phi_var), "'fet'");  // FET - Fermat-Euler Theorem
  cpp_int d_nr  = handle_nullopt(nr(e, phi_var), "'nr'");    // NR - Newton-Raphson Method

  // Step 5: Cryptographic function 'ex', 'dx'
  cpp_int ex = handle_nullopt(pow(x, e, n), "'e(x)'");       // Encrypt using the public key
  cpp_int dx = handle_nullopt(pow(ex, d_eea, n), "'d(x)'");  // Descrypt using the private key
  if (dx != x)
    throw runtime_error("something went wrong in 'D(x)");

  cpp_int sx = handle_nullopt(pow(x, d_eea, n), "'s(x)'");   // Encrypt using the public key
  cpp_int vx = handle_nullopt(pow(sx, e, n), "'v(x)'");      // Descrypt using the private key
  if (vx != x)
    throw runtime_error("something went wrong in 'V(x)");

  cout << "\nE(" << x << ") = " << ex << " ; " << "D(x) = " << dx << endl;
  cout << "\nS(" << x << ") = " << sx << " ; " << "V(x) = " << vx << endl;

  cout << "\nPublic Key: (e=" << e << ", n=" << n << ")" << endl;
  cout << "\nPrivate Key: (p=" << p << ", q=" << q << ", d=" << d_eea << ")" << endl;

  cout << "\n(Debug) 'd' parameter (private exponent): " << endl;
  cout << "  EEA:          " << d_eea << endl;
  cout << "  FET:          " << d_fet << endl;
  cout << "  NR :          " << d_nr << endl;

  return 0;
}
