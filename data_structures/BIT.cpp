// Most of the implementation comes from e-maxx.ru, although several
// things can also be found on the TopCoder tutorial about BITs
// community.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees
// e-maxx.ru/algo/fenwick_tree
template <typename T>
class FenwickTree {
 public:
  FenwickTree() {}

  FenwickTree(unsigned int n) { Init(n); }

  T Query(int x) const {
    T result = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) result += data[i];
    return result;
  }

  T QueryInterval(int x, int y) const { return Query(y) - Query(x - 1); }

  T QuerySingle(int x) const {
    T result = data[x];
    if (x > 0) {
      int y = (x & (x + 1)) - 1;
      x -= 1;
      while (x != y) {
        result -= data[x];
        x = (x & (x + 1)) - 1;
      }
    }
    return result;
  }

  void Update(int x, T delta) {
    for (int i = x; i < (int)data.size(); i = (i | (i + 1))) data[i] += delta;
  }

  unsigned int size() const { return data.size(); }

  void Init(unsigned int n) { data.assign(n, 0); }

  vector<T> data;
};

// Extension of the Fenwick Tree to 2D
template <typename T>
class FenwickTree2D {
 public:
  FenwickTree2D() {}

  FenwickTree2D(unsigned int m, unsigned int n) { Init(m, n); }

  T Query(int x, int y) const {
    T result = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) result += data[i].Query(y);
    return result;
  }

  void Update(int x, int y, T delta) {
    for (int i = x; i < (int)data.size(); i = (i | (i + 1)))
      data[i].Update(y, delta);
  }

  void Init(unsigned int m, unsigned int n) {
    if (data.size() == m) {
      for (int i = 0; i < (int)m; i++) data[i].Init(n);
    } else {
      data.assign(m, FenwickTree<T>(n));
    }
  }

  vector<FenwickTree<T> > data;
};

/*
** BIT Linear Construction Snippet
**

class Fenwick{
  int *m, N;
public:
  Fenwick(int a[], int n);
};

Fenwick::Fenwick(int a[], int n){
  N = n;
  m = new int[N];
  memset(m, 0, sizeof(int)*N);
  for(int i=0;i<N;++i){
    m[i] += a[i];
    if((i|(i+1))<N) m[i|(i+1)] += m[i];
  }
}
*/