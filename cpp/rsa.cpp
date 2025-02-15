// #include<bits/stdc++.h> Fazer teste em relação a este include
#include <iostream>
#include <numeric>
#include <optional>
#include <cmath>
#include <tuple>

using namespace std;

bool is_prime(int n) {

   // Check if a number is prime using the trivial division method.

    if (n < 2)
        return false;

    int sq = (n / 2) + 1;
    for (int i = 2; i < sq; i++) {
        if ((n % i) == 0)
            return false;
    }
    return true;
}

optional<int> generate_e(int phi) {

    // Generate the smallest possible 'e' such that (1 < e < phi) and gcd(e, phi) = 1.
    // Returns None if no valid 'e' exists.

    for (int e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            return e;
    }
    return nullopt;
}

optional<int> eea(int a, int n) {

    // Compute the modular inverse of a under modulo n using the Extended Euclidean Algorithm.
    // Returns the modular inverse if it exists, otherwise returns None.

    int t = 0, new_t = 1;
    int r = n, new_r = a;

    while (new_r != 0) {
        int quotient = r / new_r;       // Floor division

        int temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;

        int temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }

    // If r is not 1, then a has no modular inverse
    if (r > 1)
        return nullopt;

    // Ensure the result is positive
    if (t < 0)
        t += n;

    return t;
}

// Power function with modulus
// Compute num pwr mod modulus
optional<int> pow(int a, int b, int n) {
    if (n == 0)
        return nullopt;
    if (b < 0)
        return (int) pow(a,((b + n) % n)) % n;
    return (int) pow(a, b) % n;
}

optional<int> flt(int a, int n) {

    // Compute the modular inverse of a under modulo n using the Fermat's Little Theorem.
    // Returns the modular inverse if it exists, otherwise returns None.

    if (gcd(a,n) != 1)
        return nullopt;

    return pow(a, -1, n);
}

tuple<int, int> f_2 (int a, int n, int x = 1) {

    // Correction Function

    int k = 0;

    while(1) {
        k += 1;

        int x_old = x;
        x = (x * (2 - ((a * x) / n)));

        if (x_old == x)
            return {x, k};

    }

    exit(EXIT_FAILURE);
}

int f_1 (int a, int n, int x = 1) {

    // One iteraction of Newton-Raphson.

    int f = (a * x) + 1;                // F(d)
    int f_ = a;                         // F'(d)
    x = (x - (f / f_)) % n;

    return x;
}

int handle_nullopt(optional<int> n) {
    if (n)
        return n.value();

    return -1;
}

int main() {

    // Step 0: Ask for a message
    int x;
    cout << "Enter the message 'x': " << endl;
    cin >> x;

    // Step 1: Generate the modulus 'n'
    int p;
    cout << "Enter 'p': " << endl;
    cin >> p;
    if (is_prime(p) == false)
        cout << "p is not a prime number" << endl;
    int q;
    cout << "Enter 'q': " << endl;
    cin >> q;
    if (is_prime(q) == false)
        cout << "q is not a prime number" << endl;

    int n = p * q;

    // Step 2: Compute the totient of the modulus 'phi'
    int phi = (p - 1) * (q - 1);

    // Step 3: Generate the parameter 'e'
    int e = handle_nullopt(generate_e(phi));

    // Step 4: Compute the parameter 'd'
    int d_eea = handle_nullopt(eea(e, phi));     // EEA - Extended Euclidean Algorithm
    int d_flt = handle_nullopt(flt(e, phi));     // FLT - Fermat's Little Theorem
    int d_f1 = f_1(e, phi);                      // NR - Newton-Raphson
    auto [d_f2, k] = f_2(e, phi);                // Correction Function

    // Step 5: Cryptographic function 'ex', 'dx'
    int ex = handle_nullopt(pow(x, e, n));       // Encrypt using the public key
    int dx = handle_nullopt(pow(ex, d_eea, n));  // Descrypt using the private key
    if (dx != x)
        cout << "something went wrong in 'D(x)'" << endl;

    int sx = handle_nullopt(pow(x, d_eea, n));   // Encrypt using the public key
    int vx = handle_nullopt(pow(sx, e, n));      // Descrypt using the private key
    if (vx != x)
        cout << "something went wrong in 'V(x)'" << endl;

    cout << "\nE(" << x << ") = " << ex << " ; " << "D(x) = " << dx << endl;
    cout << "\nS(" << x << ") = " << sx << " ; " << "V(x) = " << vx << endl;

    cout << "\nPublic Key: (e=" << e << ", n=" << n << ")" << endl;
    cout << "\nPrivate Key: (p=" << p << ", q=" << q << ", d=" << d_eea << ")" << endl;

    cout << "\n(Debug) 'd' parameter (private exponent): " << endl;
    cout << "  EEA:          " << d_eea << endl;
    cout << "  FLT:          " << d_flt << endl;
    cout << "NR f1:          " << d_f1 << endl;
    cout << "NR f2:          " << d_f2 << ", iteractions: " << k << endl;

    return 0;
}
