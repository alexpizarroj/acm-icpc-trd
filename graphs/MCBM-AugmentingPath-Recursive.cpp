typedef vector<int> vi;
vector<vi> lst;    // adj list: left-nodes links
vi rima, visited;  // rima = right nodes' (left-)match
int n, m;          // n = # of left nodes, m = # of right nodes

bool find_match(int where) {
  if (where == -1) return 1;
  for (int i = 0; i < (int)lst[where].size(); i++) {
    int match = lst[where][i];
    if (!visited[match]) {
      visited[match] = 1;
      if (find_match(rima[match])) {
        rima[match] = where;
        return 1;
      }
    }
  }
  return 0;
}

int maximum_matching()  // O(V*E)
{
  int ans = 0;

  visited.resize(m), rima.assign(m, -1);
  for (int i = 0; i < n; ++i) {
    fill(visited.begin(), visited.end(), 0);
    ans += find_match(i);
  }

  return ans;
}
