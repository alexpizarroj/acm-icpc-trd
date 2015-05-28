#include <bits/stdc++.h>
using namespace std;

template <int alphabet_size>
struct TrieNode {
  int n_words, n_prefixes;
  int child[alphabet_size] = {0};

  TrieNode() : n_words(0), n_prefixes(0) { }
};

template <int alphabet_size>
struct Trie {
  static constexpr int npos = -1;
  using TNode = TrieNode<alphabet_size>;
  vector<TNode> nodes;

  Trie() { nodes.emplace_back(); }

  /*
  ** Maps the given char to an unsigned integer
  ** inside the range [0..alphabet_size)
  */
  int char_to_child(char c) {
    int result = c - '0';
    //assert(0 <= result && result < alphabet_size);
    return result;
  }

  /*
  ** Adds the given word to the trie
  */
  void add_word(const char *s) {
    int current = 0;

    for (int i = 0; s[i]; i++) {
      nodes[current].n_prefixes += 1;

      int next_child = char_to_child(s[i]);

      int next_node = nodes[current].child[next_child];
      if (next_node == 0) {
        next_node = nodes.size();
        nodes[current].child[next_child] = next_node;
        nodes.emplace_back();
      }
      current = next_node;
    }

    nodes[current].n_prefixes += 1;
    nodes[current].n_words += 1;
  }

  /*
  ** Traverses the trie, following the content of string 's'.
  ** Returns the node ID where the traversal stopped, or
  ** Trie::npos if it couldn't follow the whole string.
  */
  int traverse(const char *s) {
    int current = 0;

    for (int i = 0; s[i]; i++) {
      int next_child = char_to_child(s[i]);

      int next_node = nodes[current].child[next_child];
      if (next_node == 0) {
        return Trie::npos;
      }

      current = next_node;
    }

    return current;
  }

  int count_prefixes(const char *s) {
    int node = traverse(s);
    int result = (node == Trie::npos ? 0 : nodes[node].n_prefixes);
    return result;
  }

  int count_words(const char *s) {
    int node = traverse(s);
    int result = (node == Trie::npos ? 0 : nodes[node].n_words);
    return result;
  }
};
