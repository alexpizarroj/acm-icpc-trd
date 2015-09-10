struct MfEdge {
  int v, cap;
  int backid; // id to the back edge
};

struct MaxFlow {
  vector<vector<int>> g;  // integers represent edges' ids
  vector<MfEdge> edges;   // edges.size() should always be even
  int n, s, t;            // n = # vertices, s = src vertex, t = sink vertex

  int find_path() {
    const int inf = int(1e9 + 7);
    vector<int> from(n, -1), used_edge(n, -1);
    
    vector<int> visited(n, -1); queue<int> q;
    q.push(s); visited[s] = true;
    while (!visited[t] && !q.empty()) {
      int u = q.front();
      q.pop();
      for (int eid : g[u]) {
        int v = edges[eid].v;
        if (edges[eid].cap > 0 && !visited[v]) {
          from[v] = u, used_edge[v] = eid;
          q.push(v); visited[v] = true;
          if (v == t) break;
        }
      }
    }

    int f = inf;
    if (from[t] != -1) {
      for (int v = t; from[v] > -1; v = from[v]) {
        f = min(edges[used_edge[v]].cap, f);
      }
      for (int v = t; from[v] > -1; v = from[v]) {
        int backid = edges[used_edge[v]].backid;
        edges[used_edge[v]].cap -= f;
        edges[backid].cap += f;
      }
    }
    return (f == inf ? 0 : f);
  }

  int get() {
    int mf = 0, d;
    while ((d = find_path())) mf += d;
    return mf;
  }
};
