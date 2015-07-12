// Max Value Segment Tree + Range Update with Lazy Propagation

struct Node {
  int s, e;       // Interval covered by this node
  int son[2];     // Children of this node
  int val, lazy;  // Node info + Data to propagate
};

struct SegmentTree {
  vector<Node> T;

  SegmentTree(const vector<int>& vec) {
    const int N = vec.size();
    
    Node n;
    n.s = 0, n.e = N;
    n.son[0] = n.son[1] = -1;
    n.val = n.lazy = 0;

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
    
    n.val = max(T[n.son[0]].val, T[n.son[1]].val);
  }

  void update(int u, int le, int ri, int val) {
    Node &n = T[u];
    if (n.e <= le || n.s >= ri) return;

    if (n.s == le && n.e == ri) {
      n.lazy = max(n.lazy, val);
      return;
    }

    if (le < T[n.son[0]].e) {
      update(n.son[0], le, min(T[n.son[0]].e, ri), val);
      update(n.son[1], max(T[n.son[1]].s, le), ri, val);
    } else {
      update(n.son[1], max(T[n.son[1]].s, le), ri, val);
    }
    n.val = max(n.val, val);
  }

  void push_lazy(int u) {
    Node &n = T[u];
    if (n.lazy == 0) return;

    n.val = max(n.val, n.lazy);
    for (int i = 0; i < 2; i++) {
      if (n.son[i] != -1) {
        T[n.son[i]].lazy = max(T[n.son[i]].lazy, n.lazy);
      }
    }
    n.lazy = 0;
  }

  int query(int u, int le, int ri) {
    Node &n = T[u];
    if (n.e <= le || n.s >= ri) return 0;

    push_lazy(u);
    if (n.s == le && n.e == ri) return n.val;

    int res = query(n.son[0], le, min(T[n.son[0]].e, ri));
    res = max(res, query(n.son[1], max(T[n.son[1]].s, le), ri));
    return res;
  }
};
