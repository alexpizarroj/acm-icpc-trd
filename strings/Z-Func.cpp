/*
** Given a string S of length n, the Z Algorithm produces
** an array Z where Z[i] is the length of the longest substring
** starting from S[i] which is also a prefix of S, i.e. the
** maximum k such that S[j] = S[i + j] for all 0 <= j < k.
** Note that Z[i] = 0 means that S[0] != S[i].
*/
void z_func(const string &s) {
  const int length = s.size();
  int left = 0, right = 0;

  vi z(length);
  z[0] = 0;

  for (int i = 1; i < length; i++) {
    if (i > right) {
      int j;
      for (j = 0; i + j < length && s[i + j] == s[j]; j++)
        ;
      z[i] = j;
      left = i;
      right = i + j - 1;
    } else if (z[i - left] < right - i + 1)
      z[i] = z[i - left];
    else {
      int j;
      for (j = 1; right + j < length && s[right + j] == s[right - i + j]; j++)
        ;
      z[i] = right - i + j;
      left = i;
      right = right + j - 1;
    }
  }

  return z;
}
