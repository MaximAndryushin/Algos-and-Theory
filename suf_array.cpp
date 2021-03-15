#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

void count_sort(vector<int>& v, vector<int>& c) {
  int n = v.size();
  vector<int> cnt(n, 0);
  for (int val: c)
    if (val + 1 < n)
      cnt[val + 1]++;
  for (int i = 1; i < n; i++)
    cnt[i] += cnt[i - 1];
  vector<int> nv(n);
  for (int val: v) {
    nv[cnt[c[val]]] = val;
    cnt[c[val]]++;
  }
  swap(v, nv);
}

void suf_arr(string& s, vector<int>& v, vector<int>& lcp) {
  s += '$';
  int n = s.size();
  vector<int> c(n, 0);
  vector<int> nc(n, 0);
  v.assign(n, 0);
  iota(v.begin(), v.end(), 0);
  sort(v.begin(), v.end(), [&](int a, int b) {
    if (s[a] != s[b])
      return s[a] < s[b];
    return a < b;
  });
  int cur = 0;
  for (int i = 1; i < n; i++) {
    if (s[v[i]] != s[v[i - 1]])
      cur++;
    c[v[i]] = cur;
  }
  for (int i = 0; (1 << i) < n && cur < n; i++) {
    for (int j = 0; j < n; j++)
      v[j] = (v[j] - (1 << i) + n) % n;
    count_sort(v, c);
    cur = 0;
    nc[v[0]] = 0;
    for (int j = 1; j < n; j++) {
      if (pii(c[v[j - 1]], c[(v[j - 1] + (1 << i)) % n]) < pii(c[v[j]], c[(v[j] + (1 << i)) % n]))
        cur++;
      nc[v[j]] = cur;
    }
    swap(c, nc);
  }
  lcp.resize(n);
  int k = 0;
  for (int i = 0; i < n - 1; i++) {
    int j = v[c[i] - 1]; 
    while(s[i + k] == s[j + k])
      k++;
    lcp[c[i]] = k;
    k = max(0, k - 1);
  }
}

int main() {
  return 0;
}