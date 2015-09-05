#include <bits/stdc++.h>
using namespace std;

/*
** Generic segment tree with lazy propagation (requires C++11)
** Sample node implementation that supports
** Query:  sum of the elements in range [a, b)
** Update: add a given value X to every element in range [a, b)
*/

struct StNode {
  using NodeType = StNode;
  using i64 = long long;
  i64 val;   // Sum of the interval
  i64 lazy;  // Sumation pending to apply to children

  // Used, while creating the tree, to update the Node content according to
  // the value given by the ValueProvider
  void set(const NodeType& from) {
    val = from.val;
    lazy = identity().lazy;
  }

  // Updates the Node content to store the result of the 'merge' operation
  // applied on the children.
  // The tree will always call push_lazy() on the Node *before* calling merge()
  void merge(const NodeType& le, const NodeType& ri) {
    val = le.val + ri.val;
    lazy = identity().lazy;
  }

  // Used to update the Node content in a tree update command
  void update(const NodeType& from) {
    auto new_value = from.val;
    val += (e - s) * new_value;
    lazy += new_value;
  }

  // Pushes any pending lazy updates to children
  void push_lazy(NodeType& le, NodeType& ri) {
    if (lazy == identity().lazy) {
      return;
    }

    le.lazy += lazy;
    le.val += (le.e - le.s) * lazy;

    ri.lazy += lazy;
    ri.val += (ri.e - ri.s) * lazy;

    lazy = identity().lazy;
  }

  // This function should return a NodeType instance such that calling
  // Y.merge(X, identity()) or Y.merge(identity(), X) for any Node X with no
  // pending updates should make Y match X exactly.
  static NodeType identity() {
    static auto tmp = (NodeType){0, 0};
    return tmp;
  }

  // Internal tree data
  int son[2];  // Children of this node
  int s, e;    // Interval [s, e), covered by this node
};

template <class Node>
struct SegmentTree {
  using ValueProvider = function<Node(int)>;
  vector<Node> T;

  SegmentTree(int n, const ValueProvider& vp = [](int pos) {
    return Node::identity();
  }) {
    Node nd;
    nd.son[0] = nd.son[1] = -1;
    nd.s = 0, nd.e = n;

    T.reserve(4 * n);
    T.emplace_back(std::move(nd));

    init(vp, 0);
  }

  void init(const ValueProvider& vp, int u) {
    Node& n = T[u];

    if (n.e - n.s == 1) {
      n.set(vp(n.s));
      return;
    }

    Node le(n), ri(n);

    le.e = (n.s + n.e) / 2;
    n.son[0] = T.size();
    T.emplace_back(std::move(le));
    init(vp, n.son[0]);

    ri.s = le.e;
    n.son[1] = T.size();
    T.emplace_back(std::move(ri));
    init(vp, n.son[1]);

    n.merge(T[n.son[0]], T[n.son[1]]);
  }

  void update(int le, int ri, const Node& val, int u = 0) {
    Node& n = T[u];
    if (le >= n.e || n.s >= ri) return;

    if (n.s == le && n.e == ri) {
      n.update(val);
      return;
    }

    n.push_lazy(T[n.son[0]], T[n.son[1]]);

    update(le, min(T[n.son[0]].e, ri), val, n.son[0]);
    update(max(T[n.son[1]].s, le), ri, val, n.son[1]);
    n.merge(T[n.son[0]], T[n.son[1]]);
  }

  Node query(int le, int ri, int u = 0) {
    Node& n = T[u];
    if (n.e <= le || n.s >= ri) return Node::identity();
    if (n.s == le && n.e == ri) return n;

    n.push_lazy(T[n.son[0]], T[n.son[1]]);

    Node r1, r2, r3;
    r1 = query(le, min(T[n.son[0]].e, ri), n.son[0]);
    r2 = query(max(T[n.son[1]].s, le), ri, n.son[1]);
    r3.merge(r1, r2);
    return r3;
  }
};

/*
** USAGE SAMPLE
** http://www.spoj.com/problems/HORRIBLE/
*/
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int tc;
  cin >> tc;

  for (int cas = 1; cas <= tc; ++cas) {
    int n, c;
    cin >> n >> c;

    SegmentTree<StNode> st(n);

    for (int i = 0; i < c; ++i) {
      int k, p, q;
      cin >> k >> p >> q;
      p -= 1;

      if (k == 0) {
        int v;
        cin >> v;
        st.update(p, q, (StNode){v});
      } else {
        auto sum = st.query(p, q).val;
        cout << sum << '\n';
      }
    }
  }

  return 0;
}
