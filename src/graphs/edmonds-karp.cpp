const int MAX = 400;
vector<vector<int> > adjlist;
int res[MAX][MAX], n, s, t;

int find_path() {
  const int inf = int(1e9 + 7);
  vector<int> visited(n, 0), from(n, -1);
  queue<int> q;
  int u, v, f;

  q.push(s);
  visited[s] = true;
  while (!visited[t] && !q.empty()) {
    u = q.front();
    q.pop();
    for (int i = 0; i < (int)adjlist[u].size(); ++i) {
      v = adjlist[u][i];
      if (res[u][v] > 0 && !visited[v]) {
        from[v] = u;
        q.push(v);
        visited[v] = true;
        if (v == t) {
          break;
        }
      }
    }
  }

  f = inf;
  if (visited[t]) {
    for (v = t; from[v] > -1; v = from[v]) f = min(res[from[v]][v], f);
    for (v = t; from[v] > -1; v = from[v])
      u = from[v], res[u][v] -= f, res[v][u] += f;
  }

  return (f == inf ? 0 : f);
}

int maxflow() {
  int mf = 0, d;
  while ((d = find_path())) mf += d;
  return mf;
}
