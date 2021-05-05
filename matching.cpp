#include <bits/stdc++.h>

#define endl "\n" 
using namespace std;

using pii = pair<int, int>;

constexpr int N = 2e5 + 5;

// graph doesnt have cycles with odd length
namespace kuhn {
  vector<vector<int>> gr;
  vector<int> mt;
  vector<int> mark;
  int cur = 1;

  bool dfs(int v) {
    if (mark[v] == cur)
      return false;
    mark[v] = cur;
    for (int u: gr[v]) {
      if (mt[u] == -1 || dfs(mt[u])) {
        mt[u] = v;
        return true;
      }
    }
    return false;
  };

  int kuhn() {
    int n = gr.size();
    mark.resize(n);
    mt.assign(n, -1);
    for (int i = 0; i < n; i++) {
      if (dfs(i)) 
        cur++;
    }
  }
}

int main() {
  
}