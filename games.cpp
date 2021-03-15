#include<bits/stdc++.h>

#define endl "\n"
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr int N = 1e2 + 1;
constexpr ll mod = 1e9 + 7;

/*
оптимальная игра - при ответе С, у первого игрока есть стратегия на результат не меньше С независимо от игры второго,
и у второго есть стратегия отдать не больше С независимо от первого


двигать фишку пот ребрам(ПОМНИ)

*/

enum Estatus{
  E_unknown,
  E_win,
  E_lose,
  E_tie
};

vector<int> rg[N];
int deg[N], n, m;
vector<Estatus> ans;

void getans(){
  ans.assign(n, E_unknown);
  queue<int> q;
  for (int i = 0; i < n; i++){
    if (deg[i] == 0)
      q.push(i), ans[i] = E_lose;
  }
  while(q.size()){
    int cur = q.front();
    Estatus st = ans[cur];
    q.pop();
    for (int j: rg[cur]){
      if (ans[j] == E_unknown){
        if (st == E_lose)
          ans[j] = E_win, q.push(j);
        else {
          deg[j]--;
          if (deg[j] == 0) {
            ans[j] = E_lose;
            q.push(j);
          }
        }
      }
    }
    for (auto& e : ans)
      e = (e == E_unknown ? E_tie : e);
  }
}


void Solve(){
  
} 

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Solve();
  return 0;
}