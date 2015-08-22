vector<int> primes;  // Filled with prime numbers <= n (at least)

void factorial_prime_factor(const int n, vector<int>& v) {
  v.clear();
  for (size_t i = 0; primes[i] <= n && i < primes.size(); i++) {
    const int& p = primes[i];
    double q = (n / (double)p);
    int d = int(q);

    while (q >= p) {
      q /= p;
      d += int(q);
    }

    v.push_back(d);
  }
}
