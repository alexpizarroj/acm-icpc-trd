// Receives a sorted degree sequence (non ascending)
bool isGraphicSequence(const vector<int> &seq)  // O(n lg n)
{
  vector<int> sum;
  int n = seq.size();

  if (n == 1 && seq[0] != 0) return false;

  sum.reserve(n + 1);
  sum.push_back(0);
  for (int i = 0; i < n; ++i) sum.push_back(sum[i] + seq[i]);
  if ((sum[n] & 1) == 1) return false;

  for (long long k = 1; k <= n - 1 && seq[k - 1] >= k; ++k) {
    int j = distance(seq.begin(), upper_bound(seq.begin() + k, seq.end(), k,
                                              greater<int>())) +
            1;
    long long left = sum[k];
    long long right = k * (k - 1) + (j - k - 1) * k + (sum[n] - sum[j - 1]);

    if (left > right) return false;
  }

  return true;
}