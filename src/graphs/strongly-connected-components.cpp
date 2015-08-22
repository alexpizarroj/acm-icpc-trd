vector<vector<int> > g, gt;
stack<int> S;
int n;
vi scc;

void scc_dfs(const vector<vector<int> > &g, int u, bool addToStack = false) {
  for (int i = 0; i < (int)g[u].size(); ++i) {
    int v = g[u][i];
    if (scc[v] == inf) {
      scc[v] = scc[u];
      scc_dfs(g, v, addToStack);
    }
  }
  if (addToStack) S.push(u);
}

int kosaraju() {
  const int inf = int(1e9 + 7);
  int ans = 0;

  scc.assign(n, inf);
  for (int u = 0; u < n; ++u) {
    if (scc[u] != inf) continue;
    scc[u] = true;
    scc_dfs(g, u, true);
  }
  scc.assign(n, inf);
  while (!S.empty()) {
    int u = S.top();
    S.pop();
    if (scc[u] != inf) continue;
    scc[u] = ans++;
    scc_dfs(gt, u);
  }

  return ans;
}