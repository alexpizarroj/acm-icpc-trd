/*
** Segment Tree with Lazy Propagation
** Query:   sum of the elements in [a, b)
** Update:  sets every element in [a, b) to a given value X
*/

constexpr int inf = 1000000007;

struct Node {
  int s, e;       // Interval [s, e) is covered by this node
  int son[2];     // Children of this node
  int val;        // Sum of the interval;
  int lazy;       // Value yet to set to the children (inf = no pending lazy updates)
};

struct SegmentTree {
  vector<Node> T;

  SegmentTree(const vector<int>& vec) {
    const int N = vec.size();
    
    Node n;
    n.s = 0, n.e = N;
    n.son[0] = n.son[1] = -1;
    n.val = 0, n.lazy = inf;

    T.reserve(4 * N);
    T.push_back(n);
    init(0, vec);
  }
  
  explicit SegmentTree(int N, int val) : SegmentTree(vector<int>(N, val)) {}
    
  explicit SegmentTree(int N) : SegmentTree(N, 0) {}
  
  void init(int u, const vector<int>& vec) {
    Node &n = T[u];
    if (n.e - n.s == 1)
    {
      n.val = vec[n.s];
      return;
    }
    
    int mid = (n.s + n.e) / 2;
    for (int i = 0; i < 2; i++) {
      Node c(n);
      if (i == 0)
        c.e = mid;
      else {
        c.son[0] = -1;
        c.s = mid;
      }
      n.son[i] = T.size();
      T.push_back(c);
      init(n.son[i], vec);
    }
    
    n.val = T[n.son[0]].val + T[n.son[1]].val;
  }

  void update(int u, int le, int ri, int val) {
    Node &n = T[u];
    if (n.e <= le || n.s >= ri) return;

    if (n.s == le && n.e == ri) {
      n.lazy = val;
      n.val = (n.e - n.s) * val;
      return;
    }
    
    push_lazy(u);
    if (le < T[n.son[0]].e) {
      update(n.son[0], le, min(T[n.son[0]].e, ri), val);
      update(n.son[1], max(T[n.son[1]].s, le), ri, val);
    } else {
      update(n.son[1], max(T[n.son[1]].s, le), ri, val);
    }
    
    n.val = T[n.son[0]].val + T[n.son[1]].val;
  }

  void push_lazy(int u) {
    Node &n = T[u];
    if (n.lazy == inf) return;

    for (int i = 0; i < 2; i++) {
      if (n.son[i] != -1) {
        Node &son = T[n.son[i]];
        son.lazy = n.lazy;
        son.val = (son.e - son.s) * n.lazy;
      }
    }
    n.lazy = inf;
  }

  int query(int u, int le, int ri) {
    Node &n = T[u];
    if (n.e <= le || n.s >= ri) return 0;

    if (n.s == le && n.e == ri) return n.val;

    push_lazy(u);
    int res = query(n.son[0], le, min(T[n.son[0]].e, ri));
    res += query(n.son[1], max(T[n.son[1]].s, le), ri);
    return res;
  }
};
