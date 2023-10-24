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

// Общие сведения о представлении множеств масками

// Простые операции: AND, OR, XOR, SHL, SHR
// Установка бита, проверка бита
// Количество бит в маске https://en.cppreference.com/w/cpp/numeric/popcount

inline int popcount(int x){
    int count = 0;
    __asm__ volatile("POPCNT %1, %0;"
        :"=r"(count)
        :"r"(x)
        :
    );
    return count;
}



// Пример задачи:

// Сколько подмножеств элементов имеют сумму не меньше X. Решение за O(2^n \cdot n).



// Гамильтонов цикл/путь. Задача коммивояжера.


// Определение.


// Общий подход O(2^{|V|} \cdot |E|):
// dp[mask][v] - ответ для пути из стартовой вершины (практически 0) в вершину v, с посещенными вершинами отмеченными в mask. Вершина v не учитывается в mask.


// Оптимизация для гамильтонова цикла/пути.


// dp[mask] - маска текущих вершин, которые могут быть последними в пути из стартовой вершины.
// Переход: dp[new_mask] |= adj[v] & inv(new_mask)

// Асимптотика: O(2^{|V|} \cdot |V|)




// Восстановление пути


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