string trim_zeros(const string& a) {
  size_t idx = 0;
  while (a[idx] == '0' && idx < a.size()) idx++;
  if (idx == a.size()) idx--;

  return a.substr(idx);
}

string big_sub(const string& n1, const string& n2) {
  string a = trim_zeros(n1);
  string b = trim_zeros(n2);

  bool minus = false;
  if (esMayor(b, a)) {
    swap(a, b);
    minus = true;
  }

  int i, j, d = (a.length() - b.length());
  for (i = b.length() - 1; i >= 0; i--) {
    if (a[i + d] >= b[i])
      a[i + d] -= b[i] - '0';
    else {
      j = -1;
      while (a[i + d + j] == '0') {
        a[i + d + j] = '9';
        j--;
      }
      a[i + d + j]--;

      a[i + d] += 10 - b[i] + '0';
    }
  }

  return (minus ? "-" : "") + trim_zeros(a);
}

string big_add(const string& a, const string& b) {
  int LA = a.size(), LB = b.size(), L = max(LA, LB), carry = 0;

  string x = string(L, '0');

  while (L--) {
    LA--;
    LB--;

    if (LA >= 0) carry += a[LA] - '0';
    if (LB >= 0) carry += b[LB] - '0';

    if (carry < 10)
      x[L] = '0' + carry, carry = 0;
    else
      x[L] = '0' + carry - 10, carry = 1;
  }

  if (carry) x = '1' + x;
  return x;
}

string big_mult(string a, string b) {
  if (a == "0" || b == "0")
    return "0";
  else if (a.size() == 1) {
    int m = a[0] - '0';

    string ans = string(b.size(), '0');

    int lleva = 0;

    for (int i = b.size() - 1; i >= 0; i--) {
      int d = (b[i] - '0') * m + lleva;
      lleva = d / 10;
      ans[i] += d % 10;
    }
    if (lleva) ans = (char)(lleva + '0') + ans;
    return ans;
  } else if (b.size() == 1)
    return big_mult(b, a);
  else {
    string ans = "0";
    string ceros = "";
    for (int i = a.size() - 1; i >= 0; i--) {
      string s = big_mult(string(1, a[i]), b) + ceros;
      ceros += "0";
      ans = big_add(ans, s);
    }
    return ans;
  }
}