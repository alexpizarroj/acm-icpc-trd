#include <bits/stdc++.h>
using namespace std;

template <size_t alphabet_size>
struct TrieNode {
  size_t n_words, n_prefixes;
  size_t child[alphabet_size];

  TrieNode() : n_words(0), n_prefixes(0) { memset(child, 0, sizeof child); }
};

template <size_t alphabet_size>
struct Trie {
  static constexpr size_t npos = -1;
  using TNode = TrieNode<alphabet_size>;
  vector<TNode> nodes;

  Trie() { nodes.emplace_back(); }

  /*
  ** Maps the given char to an unsigned integer
  ** inside the range [0..alphabet_size)
  */
  size_t char_to_child(char c) {
    size_t result = c - '0';

    assert(0 <= result && result < alphabet_size);
    return result;
  }

  /*
  ** Adds the given word to the trie
  */
  void add_word(const char *s) {
    size_t current = 0;

    for (int i = 0; s[i]; i++) {
      nodes[current].n_prefixes += 1;

      size_t next_child = char_to_child(s[i]);
      assert(next_child >= 0);

      size_t next_node = nodes[current].child[next_child];
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
  size_t traverse(const char *s) {
    size_t current = 0;

    for (int i = 0; s[i]; i++) {
      size_t next_child = char_to_child(s[i]);

      size_t next_node = nodes[current].child[next_child];
      if (next_node == 0) {
        return Trie::npos;
      }

      current = next_node;
    }

    return current;
  }

  size_t count_prefixes(const char *s) {
    size_t node = traverse(s);
    size_t result = (node == Trie::npos ? 0 : nodes[node].n_prefixes);
    return result;
  }

  size_t count_words(const char *s) {
    size_t node = traverse(s);
    size_t result = (node == Trie::npos ? 0 : nodes[node].n_words);
    return result;
  }
};
