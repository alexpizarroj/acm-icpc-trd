struct McMaxFlow {
  struct MfEdge { int v, cap, cpu, backid; };
  struct FlowResult { int flow, cost; };
  vector<vector<int>> g;  // integers represent edges' ids
  vector<MfEdge> edges;   // edges.size() should always be even
  int n, s, t;            // n = # vertices, s = src vertex, t = sink vertex
  
  // Directed Edge u - > v with capacity 'cap' and cost per unit 'cpu'
  void add_edge(int u, int v, int cap, int cpu) {
    int eid = edges.size();
    g[u].push_back(eid);
    g[v].push_back(eid + 1);
    edges.push_back((MfEdge){v, cap, cpu, eid + 1});
    edges.push_back((MfEdge){u, 0, -cpu, eid});
  }

  FlowResult find_path() {
    const int inf = int(1e9 + 7);
    vector<int> from(n, -1), used_edge(n, -1);
    
    vector<int> dist(n, inf);
    queue<int> q; vector<bool> queued(n, false);
    dist[s] = 0; q.push(s); queued[s] = true;
    
    while (!q.empty()) {
      const int u = q.front(); q.pop();
      queued[u] = false;
      
      for (int eid : g[u]) {
        int v = edges[eid].v;
        int cand_dist = dist[u] + edges[eid].cpu;
        if (edges[eid].cap > 0 && cand_dist < dist[v]) {
          dist[v] = cand_dist;
          from[v] = u; used_edge[v] = eid;
          if (!queued[v]) { q.push(v); queued[v] = true; }
        }
      }
    }
    
    int f = 0, fcost = 0;
    if (from[t] != -1) {
      f = inf;
      for (int v = t; from[v] > -1; v = from[v]) {
        f = min(edges[used_edge[v]].cap, f);
        fcost += edges[used_edge[v]].cpu;
      }
      for (int v = t; from[v] > -1; v = from[v]) {
        int backid = edges[used_edge[v]].backid;
        edges[used_edge[v]].cap -= f;
        edges[backid].cap += f;
      }
      fcost *= f;
    }
    
    return (FlowResult){f, fcost};
  }

  FlowResult get() {
    FlowResult res = {0, 0};
    while (true) {
      FlowResult fr = find_path();
      if (fr.flow == 0) break;
      res.flow += fr.flow;
      res.cost += fr.cost;
    }
    return res;
  }
};
