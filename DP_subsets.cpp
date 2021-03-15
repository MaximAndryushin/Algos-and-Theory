#include<bits/stdc++.h>

#define endl "\n"
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr int N = 2e1 + 5;
constexpr ll mod = 1e9 + 7;


// dp on subsets

//(V, E) найти наибольшую клику(между каждой парой вершин есть ребро)

bool isaccept[(1 << N)];
int ed[N]; // с петлями, чтобы проще считать
int n;

bool getbit(int mask, int i){
  return (mask & (1 << i)); 
}

void getans(){
  isaccept[0] = 1;
  for (int i = 1; i < (1 << n); i++){
    isaccept[i] = ((i & isaccept[i]) == i);
  }
}

// Гамильтонов путь(путь проходящий по всем вершинам, содержащий каждую врешину только 1 раз)

bool dp[N][1 << N];
int ed[1 << N];

void findpath(){
  for (int i = 1; i < (1 << n); i++){
    for (int v = 0, ver; v < n; v++){
      if (!getbit(i, v))
        continue;
      if (cnt[i] == 1) // cnt - num of bits where 1
        dp[v][i] = 1;
      ver = (ed[v] & i);
      for (int j = 0; j < n; j++){
        if (getbit(ver, j)){
          if (dp[j][ver]){
            dp[v][i] = 1;
            break;
          }
        }
      }
    }
  }
}

//идея O(n * 2 ^ n)
// храним множество, на котором может заканчиваться данный путь


//dp по профилю

//кол-во способов покрыть доску с выколотыми клетками доминошками

//строим граф переходов 2^n x 2^n и просто возводим в степень кол-ва столбцов


//изломанный профиль

void Solve(){
  
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Solve();
  return 0;
}