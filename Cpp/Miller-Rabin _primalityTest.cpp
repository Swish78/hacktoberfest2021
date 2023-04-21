#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

bool miller_rabin(long long n, int k=5) {
  // Check some basic primality conditions
  if (n < 2) {
    return false; // n is less than 2, so it can't be prime
  }
  if (n == 2 || n == 3) {
    return true; // n is 2 or 3, so it's prime
  }
  if (n % 2 == 0) {
    return false; // n is even, so it can't be prime
  }

  // Write n-1 as d * 2^r, where d is odd
  long long d = n - 1;
  int r = 0;
  while (d % 2 == 0) {
    d /= 2; // divide d by 2 until it becomes odd
    r++;   // keep track of how many times we divided by 2
  }

  // Perform the Miller-Rabin test k times
  for (int i = 0; i < k; i++) {
    // Choose a random witness a in the range [2, n-2]
    long long a = rand() % (n - 3) + 2;
    long long x = pow(a, d) % n;

    // Check whether a is a witness for the compositeness of n
    if (x == 1 || x == n - 1) {
      continue; // a is not a witness, so try another random value
    }
    for (int j = 0; j < r - 1; j++) {
      x = (x * x) % n; // compute x^2 mod n
      if (x == n - 1) {
        break; // a is not a witness, so try another random value
      }
    }
    if (x != n - 1) {
      return false; // a is a witness, so n is composite
    }
  }
  return true; // n passed all k tests, so it's probably prime
}
