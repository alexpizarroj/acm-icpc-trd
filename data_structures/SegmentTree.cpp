struct Node {
  int s, e;       // Interval covered by this node
  int son[2];     // Children of this node
  int val, lazy;  // Node info + Data to propagate
};

struct SegmentTree {
  vector<Node> T;

  SegmentTree(int N) {
    Node n;
    n.s = 0, n.e = N;
    n.son[0] = n.son[1] = -1;
    n.val = n.lazy = 0;

    T.reserve(4 * N);
    T.push_back(n);
    Init(0);
  }

  void Init(int u) {
    Node &n = T[u];
    if (n.e - n.s == 1) return;
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
      Init(n.son[i]);
    }
  }

  void Update(int u, int le, int ri, int val) {
    Node &n = T[u];
    if (n.e <= le || n.s >= ri) return;

    if (n.s == le && n.e == ri) {
      n.lazy |= val;
      return;
    }

    if (le < T[n.son[0]].e) {
      Update(n.son[0], le, min(T[n.son[0]].e, ri), val);
      Update(n.son[1], max(T[n.son[1]].s, le), ri, val);
    } else {
      Update(n.son[1], max(T[n.son[1]].s, le), ri, val);
    }
    n.val |= val;
  }

  void PushLazy(int u) {
    Node &n = T[u];
    if (n.lazy == 0) return;

    n.val |= n.lazy;
    for (int i = 0; i < 2; i++)
      if (n.son[i] != -1) T[n.son[i]].lazy |= n.lazy;
    n.lazy = 0;
  }

  int Query(int u, int le, int ri) {
    Node &n = T[u];
    if (n.e <= le || n.s >= ri) return 0;

    PushLazy(u);
    if (n.s == le && n.e == ri) return n.val;

    int res = Query(n.son[0], le, min(T[n.son[0]].e, ri));
    res |= Query(n.son[1], max(T[n.son[1]].s, le), ri);
    return res;
  }
};