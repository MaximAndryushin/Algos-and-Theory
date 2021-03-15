#include <bits/stdc++.h>

#define endl "\n"
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr int N = 2e3 + 5;


// DFS

int n;

bool used[N];
vector<int> gr[N], order, rg[N], comp;

// topsort && component of strong connectivity

void topsort(int i) {
  used[i] = true;
  for (int j : gr[i])
    if (!used[j])
      topsort(j);
  order.push_back(i);
}

void dfs2(int i) {
  used[i] = true;
  for (int j: rg[i])
    if (!used[j])
      dfs2(j);
  comp.push_back(i);
}

void Solve1() {
  for (int i = 1; i <= n; i++)
    if (used[i])
      topsort(i);
  reverse(order.begin(), order.end());
  memset(used, 0, sizeof used);
  for (int el: order)
    if (!used[el]) {
      dfs2(el);
      //comp хранит вершины очередной компоненты
      comp.clear();
    }
} 

// undirected graphs

// мосты 

// e - мост, если при удалении этого ребра, увеличивается кол-во компонент связности

int tin[N], tup[N], t = 0;
vector<pii> bridges;

// tin - время входа, tup[u] = минимальная по всем вершинам поддерева величина tin[p], где p = второй конец ребра для вершины

// если tup[u] == tin[u] < = > ребро в предка u - мост

void dfs(int i, int p = -1) {
  tin[i] = tin[i] = ++t;
  for (int j: gr[i]) {
    if (j == p)
      continue;
    if (tin[j])
      tup[i] = min(tup[i], tin[j]);
    else {
      dfs(j, i);
      tup[i] = min(tup[j], tup[i]);
      if (tup[j] > tin[i])
        bridges.emplace_back(i, j);
    }
  }
}

//точки сочленения - такие точки, при удалении которых, увеличивается кол-во компонент сильной связности
// 1 - v - корень и из нее 1 ребро - не точка сочленения
// 2 - v - корень и хотя бы 2 ребра - точка сочленения
// 3 - v - произвольная вершина, то переберем ее детей u, если существует tup[u] >= tin[v] < = > V - точка сочленения

//реберная двусвязность - между 2 врешинами существует 2 реберно непереcекающихся пути
// аналогично для вершин


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  return 0;
}