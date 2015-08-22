#include <bits/stdc++.h>
using namespace std;

/*
** Generic Segment Tree with Lazy Propagation support (requires C++11)
** Sample Node Implementation for
** Query:  sum of the elements in range [a, b)
** Update: add a given value X to every element in range [a, b)
*/

struct StNode {
  using NodeType = StNode;
  using i64 = long long;
  i64 val;  // Sum of the interval
  i64 lazy; // Sumation pending to apply to children
  
  // Used, while creating the tree, to update the Node content according to
  // the value given by the ValueProvider
  void set(const NodeType& from) {
    val = from.val;
    lazy = identity().lazy;
  }
  
  // Updates the Node content to store the result of the 'merge' operation
  // applied on the children.
  // The tree will always call push_lazy() on the Node *before* using merge()
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
  void push_lazy(NodeType& le, NodeType &ri) {
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
  // Y.merge(X, identity()) for any Node X with no pending updates should
  // make Y match X exactly.
  static NodeType identity() {
    static auto tmp = (NodeType){0, 0};
    return tmp;
  }
  
  // Internal tree data. DO NOT TOUCH
  int son[2]; // Children of this node
  int s, e;   // Interval [s, e) is covered by this node
};

template<class Node>
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
    T.push_back(nd);
    
    init(0, vp);
  }
  
  void init(int u, const ValueProvider& vp) {
    Node &n = T[u];
    
    if (n.e - n.s == 1)
    {
      n.set(vp(n.s));
      return;
    }
    
    Node le(n), ri(n);
    
    le.e = (n.s + n.e) / 2;
    n.son[0] = T.size();
    T.push_back(le);
    init(n.son[0], vp);
    
    ri.s = le.e;
    n.son[1] = T.size();
    T.push_back(ri);
    init(n.son[1], vp);
    
    n.merge(T[n.son[0]], T[n.son[1]]);
  }

  void update(int u, int le, int ri, const Node& val) {
    Node &n = T[u];
    if (n.e <= le || n.s >= ri) return;

    if (n.s == le && n.e == ri) {
      n.update(val);
      return;
    }
    
    n.push_lazy(T[n.son[0]], T[n.son[1]]);
    
    if (le < T[n.son[0]].e) {
      update(n.son[0], le, min(T[n.son[0]].e, ri), val);
      update(n.son[1], max(T[n.son[1]].s, le), ri, val);
    } else {
      update(n.son[1], max(T[n.son[1]].s, le), ri, val);
    }
    
    n.merge(T[n.son[0]], T[n.son[1]]);
  }

  Node query(int u, int le, int ri) {
    Node &n = T[u];
    if (n.e <= le || n.s >= ri) return Node::identity();
    if (n.s == le && n.e == ri) return n;

    n.push_lazy(T[n.son[0]], T[n.son[1]]);
    
    Node r1 = query(n.son[0], le, min(T[n.son[0]].e, ri));
    Node r2 = query(n.son[1], max(T[n.son[1]].s, le), ri);
    
    Node r3;
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
        st.update(0, p, q, (StNode){v});
      } else {
        auto sum = st.query(0, p, q).val;
        cout << sum << '\n';
      }
    }
  }
  
  return 0;
}
