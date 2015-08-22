#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

// Implementation based on the code provided at Petr's blog. Nevertheless,
// an easy and helpful explanation can be found in TopCoder's forums
// http://petr-mitrichev.blogspot.com/2013/05/fenwick-tree-range-updates.html
// http://apps.topcoder.com/forums/?module=RevisionHistory&messageID=1407869
template <typename T>
class RangedFenwickTree {
 public:
  RangedFenwickTree() {}

  RangedFenwickTree(unsigned int n) { Init(n); }

  T Query(int at) const {
    T mul = 0, add = 0;
    int start = at;
    while (at >= 0) {
      mul += dataMul[at];
      add += dataAdd[at];
      at = (at & (at + 1)) - 1;
    }
    return mul * start + add;
  }

  T QueryInterval(int x, int y) const { return Query(y) - Query(x - 1); }

  void Update(int x, int y, T delta) {
    InternalUpdate(x, delta, -delta * (x - 1));
    if (y + 1 < (int)this->size()) InternalUpdate(y + 1, -delta, delta * y);
  }

  unsigned int size() const { return dataMul.size(); }

  void Init(unsigned int n) {
    dataMul.assign(n, 0);
    dataAdd.assign(n, 0);
  }

  vector<T> dataMul, dataAdd;

 private:
  void InternalUpdate(int x, T mul, T add) {
    for (int i = x; i < (int)this->size(); i = (i | (i + 1))) {
      dataMul[i] += mul;
      dataAdd[i] += add;
    }
  }
};

// Extension of the Ranged Fenwick Tree to 2D
template <typename T>
class RangedFenwickTree2D {
 public:
  RangedFenwickTree2D() {}

  RangedFenwickTree2D(unsigned int m, unsigned int n) { Init(m, n); }

  T Query(int x, int y) const {
    T mul = 0, add = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
      mul += dataMul[i].Query(y);
      add += dataAdd[i].Query(y);
    }
    return mul * x + add;
  }

  T QuerySubmatrix(int x1, int y1, int x2, int y2) const {
    T result = Query(x2, y2);
    if (x1 > 0) result -= Query(x1 - 1, y2);
    if (y1 > 0) result -= Query(x2, y1 - 1);
    if (x1 > 0 && y1 > 0) result += Query(x1 - 1, y1 - 1);
    return result;
  }

  void Update(int x1, int y1, int x2, int y2, T delta) {
    for (int i = x1; i < (int)dataMul.size(); i |= i + 1) {
      dataMul[i].Update(y1, y2, delta);
      dataAdd[i].Update(y1, y2, -delta * (x1 - 1));
    }
    for (int i = x2 + 1; i < (int)dataMul.size(); i |= i + 1) {
      dataMul[i].Update(y1, y2, -delta);
      dataAdd[i].Update(y1, y2, delta * x2);
    }
  }

  void Init(unsigned int m, unsigned int n) {
    // dataMul efficient initialization
    if (dataMul.size() == m) {
      for (int i = 0; i < (int)m; i++) dataMul[i].Init(n);
    } else {
      dataMul.assign(m, RangedFenwickTree<T>(n));
    }
    // dataAdd efficient initialization
    if (dataAdd.size() == m) {
      for (int i = 0; i < (int)m; i++) dataAdd[i].Init(n);
    } else {
      dataAdd.assign(m, RangedFenwickTree<T>(n));
    }
  }

  vector<RangedFenwickTree<T> > dataMul, dataAdd;
};

int main() {
  // EXAMPLE USAGE
  // Solution for http://www.spoj.com/problems/USUBQSUB/

  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  RangedFenwickTree2D<long long> f(n + 1, n + 1);
  while (m--) {
    int kind, x1, y1, x2, y2;
    cin >> kind >> x1 >> y1 >> x2 >> y2;
    if (kind == 1) {
      cout << f.QuerySubmatrix(x1, y1, x2, y2) << '\n';
    } else {
      int value;
      cin >> value;
      f.Update(x1, y1, x2, y2, value);
    }
  }

  return 0;
}
