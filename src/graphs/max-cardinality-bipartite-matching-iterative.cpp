typedef vector<int> vi;
vector<vi> lst;  // adj list for left elements
vi lema, rima;   // lema = left elements match, rima = right elements match
int n, m;        // n = amount of left elements, m = amount of right elements

bool find_match(int s) {
  vi from(n, -1);
  queue<int> q;
  int where, match, next;
  bool found = false;

  q.push(s), from[s] = s;
  while (!found && !q.empty()) {
    where = q.front();
    q.pop();
    for (int i = 0; i < (int)lst[where].size(); ++i) {
      match = lst[where][i];
      next = rima[match];
      if (where != next) {
        if (next == -1) {
          found = true;
          break;
        }
        if (from[next] == -1) q.push(next), from[next] = where;
      }
    }
  }

  if (found) {
    while (from[where] != where) {
      next = lema[where];
      lema[where] = match, rima[match] = where;
      where = from[where], match = next;
    }
    lema[where] = match, rima[match] = where;
  }

  return found;
}

int maximum_matching()  // O(V*E)
{
  int ans = 0;
  lema.assign(n, -1), rima.assign(m, -1);
  for (int i = 0; i < n; ++i) ans += find_match(i);
  return ans;
}