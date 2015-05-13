vector<int> pset, set_size;
int disjointSetsSize;
void initSet(int N) {
  pset.assign(N, 0);
  set_size.assign(N, 1);
  disjointSetsSize = N;
  for (int i = 0; i < N; i++) pset[i] = i;
}
int findSet(int i) { return (pset[i] == i) ? i : (pset[i] = findSet(pset[i])); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
void unionSet(int i, int j) {
  if (!isSameSet(i, j)) {
    set_size[findSet(j)] += set_size[findSet(i)];
    pset[findSet(i)] = findSet(j);
    disjointSetsSize--;
  }
}
int numDisjointsSets() { return disjointSetsSize; }
int sizeOfSet(int i) { return set_size[findSet(i)]; }