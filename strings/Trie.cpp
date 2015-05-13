const int kAlphaSize = 26;

struct TrieNode {
  int cnt, child[kAlphaSize];
};

class Trie {
 public:
  vector<TrieNode> T;

  Trie(int nodes_guess = 0) {
    if (nodes_guess > 0) T.reserve(nodes_guess);
    T.push_back(TrieNode());
  }

  void AddWord(const char *s) {
    int cur = 0;
    for (int i = -1; i == -1 || s[i]; i++) {
      T[cur].cnt += 1;
      if (s[i + 1]) {
        const int next = int(s[i + 1] - 'a');
        if (T[cur].child[next] == 0) {
          T[cur].child[next] = T.size();
          T.push_back(TrieNode());
        }
        cur = T[cur].child[next];
      }
    }
  }

  int GetTypingLen(const char *s) {
    int res = 1, cur = T[0].child[int(s[0] - 'a')];
    for (int i = 0; true; i++) {
      if (T[cur].cnt == 1 || s[i + 1] == 0) break;

      cur = T[cur].child[int(s[i + 1] - 'a')];
      res += 1;
    }
    return res;
  }
};
