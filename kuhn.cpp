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

struct kuhn {
    kuhn(const vector<vector<int>>& ed, int n) : ans{0}, n{n}, ed(ed), lnk(n, -1), used(ed.size(), -1) {}

    pii build() {
        for (int i = 0; i < ed.size(); i++){
            if (dfs(i)){
                ans++;
            }
        }
        int ma = 0;
        for (int i = 0; i < n; ++i) {
            if (lnk[i] != -1) {
                ma = max(ma, lnk[i]);
            }
        }
        return {ans, ma};
    }

private:
    bool dfs(int v){
        if (used[v] == ans)
            return false;
        used[v] = ans;
        for (int u : ed[v])
            if (lnk[u] == -1){
                lnk[u] = v;
                return true;
            } 
        for (int u : ed[v])
            if (dfs(lnk[u])) {
                lnk[u] = v;
                return true;
            }
        return false;
    }

private:
    int ans;
    int n;
    const vector<vector<int>>& ed;
    vector<int> lnk;
    vector<int> used;
};

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