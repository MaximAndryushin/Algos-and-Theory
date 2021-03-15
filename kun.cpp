#include<bits/stdc++.h>

#define endl "\n"
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr int N = 1e6 + 5;
constexpr ll mod = 1e9 + 7;

/* раскрасска в 2 цвета <=> нет циклов нечетной длины

паросочетание - подмножество ребер, вершинно не пересекающися
макспарсоч - макс число ребер
удлинняющая цепь
если нет удлиняющих цепей, то парсоч максимален
*/

vector<int> ed[N];
int lnk[N], n, m, ans = 0;
bool used[N];

bool dfs(int v){
  if (used[v])
    return false;
  used[v] = 1;
  for (int u : ed[v])
    if (lnk[u] == -1){
      lnk[u] = v;
      return true;
    } 
  for (int u : ed[v])
    if (dfs(lnk[u]) == -1){
      lnk[u] = v;
      return true;
    }
  return false;
}

void kun(){
  memset(used, 0, sizeof used);
  memset(lnk, -1, sizeof lnk);
  for (int i = 0; i < n; i++){
    if (dfs(i)){
      memset(used, 0, sizeof used);
      ans++;
    }
  }
}

// min covering
// max independent
// MC >= MM (max matching)
// для двудольного равенство

// задача 2 sat
// 

void Solve(){
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Solve();
  return 0;
}