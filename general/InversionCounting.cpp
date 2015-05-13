int v[MAX], sortedV[MAX];

// Merge sort with inversion counting
long long mergeSort(int *V, int lo, int hi) {
  if (lo >= hi) {
    return 0;
  } else {
    int m1 = (lo + hi) / 2, m2 = m1 + 1;
    long long r = 0, rA, rB;
    int i = lo, j = m2, k = 0;

    rA = mergeSort(V, lo, m1);
    rB = mergeSort(V, m2, hi);

    while (i <= m1 && j <= hi) {
      if (V[j] < V[i]) {
        r += (m1 - i + 1);
        sortedV[k++] = V[j++];
      } else {
        sortedV[k++] = V[i++];
      }
    }

    if (i > m1) {
      i = j;
      j = hi;
    } else {
      j = m1;
    }

    while (i <= j) {
      sortedV[k++] = V[i++];
    }

    memcpy(V + lo, sortedV, (hi - lo + 1) * sizeof(int));

    return r + rA + rB;
  }
}