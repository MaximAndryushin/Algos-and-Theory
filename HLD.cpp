//Team : SoZo

#include<bits/stdc++.h>
 
#define endl "\n"
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr int N = 1e5 + 5;

vector<int> gr[N];
int sz[N], p[N];
int way[N]; // по вершине путь
int tin[N], tout[N];
int vert[N]; // по времени вершину
int st[N], fn[N]; // время начала и конца пути по номеру пути
int t = 0, cur_way = 0;

void add_edge(int a, int b) {
  gr[a].push_back(b);
  gr[b].push_back(a);
}

auto cmp = [&](const int& a, const int& b) {
  return sz[a] > sz[b];
};

int dfscentroid(int i, int p = -1) {
  sz[i] = 0;
  int sum = 1;
  for (int j: gr[i]) {
    if (j != p)
      sum += dfs(j, i);
  }
  sort(gr[i].begin(), gr[i].end(), cmp);
  return sz[i] = sum;
}

void centroid(int v) {
  dfscentroid(v);
  if (sz[v] == 1)
    return;
  int u = v;
  while(sz[gr[u].front()] > sz[v] / 2) {
    u = gr[u].front();
  }
  for (int j: gr[u]) {
    if (gr[j].back() != u) 
      swap(gr[j].front(), gr[j].back());
    gr[j].pop_back();
  }
  for (int j: gr[u])
   centroid(j);
  return;
}

int dfs(int i = 1, int par = -1) {
  sz[i] = 1;
  p[i] = par;
  for (int j = 0; j < gr[i].size(); j++) {
    int u = gr[i][j];
    if (u == par) {
      swap(gr[i][j], gr[i].back());
      gr[i].pop_back();
      i--;
      continue;
    }
    sz[i] += dfs(u, i);
  }
  sort(gr[i].begin(), gr[i].end(), cmp);
  return sz[i];
}

void build(int v) {
  t++;
  tin[v] = t;
  vert[t] = v;
  way[v] = cur_way;
  fn[cur_way]++;
  if (gr[v].size()) 
    build(gr[v].front());
  for (int i = 1; i < gr[v].size(); i++) {
    cur_way++;
    st[cur_way] = t + 1;
    fn[cur_way] = t;
    build(gr[v][i]);
  }
}

int get_sum_root(int v) {
  int s = 0;
  while(s != -1) {
    int l = st[way[v]];
    s += sum(l, tin[v]);
    v = p[vert[l]];
  }
  return s;
}

void Solve() {
 
}
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  //auto start = chrono::high_resolution_clock::now();
  Solve();
  //auto end = chrono::high_resolution_clock::now();
  //cout << (chrono::duration_cast<chrono::duration<double>>(end - start)).count();
  return 0;
}