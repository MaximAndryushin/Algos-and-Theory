#include<bits/stdc++.h>
 
#define endl "\n"
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
 
constexpr int N = 5e5 + 5;
 
/*
  SQRT - декомпозиция
  операции с массивом:
  add(i, x);
  set(i, x);
  add(l, r, x);
  insert(i, x);
  reverse(l, r);
  sum(l, r);

  sqrt 

  разделим массив на B отрезков
  на каждом Блоке есть ответ на задачу и сам отрезок
  на каждом отрезке отвечаем за О(В) 
  O(B + N / B) - > O(max(B, N/B)) -> O(sqrt(N))

  добавление на отрезке


  список блоков 

  делаем перестройку каждые sqrt(N) раз

  алгоритм Мо
  
*/
 
void Solve(){
  
}
 
int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Solve();
  return 0;
}