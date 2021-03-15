#include<bits/stdc++.h>

#define endl "\n"
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr int N = 2e1 + 1;
constexpr ll mod = 1e9;

ll t[N];

/*

дерево Фенвика

сумма на подотрезках и изменение по индексу 

N - до памяти

для каждой позиции определим функцию от позиции t[pos] = sum([f(pos), pos]);


pos |= pos + 1

заменяет самый правый(первый с младшего разряда) 0 на 1

работает за log, так как каждый раз новая единица в двоичной записи

(pos & (pos + 1)) - 1

убивает первую единицу после нолей с конца и делает - 1

каждый раз кол-во единиц в младших разрядах увеличавается, поэтому log



встречный фенвик 

[pos, f(pos))

меняем местами операции - > сумма на суффиксах

EX:

1) НВП фенвиком

2) макс на отрезке изменение в точке

запрос [l, r]
идем влево, пока можем (обычный фенвик)
теперь встречным фенвиком придем точно в r

3) любую функцию от множества мы должны пересчитывать без какого-то эл-та + еще эл-нт


Использование фенвика

Двумерный фенвик

втупую делаем


операции на отрезке:
s[pos] = prefsum(a[pos]) * pos + presum(b[pos]), 

a[l] += x;
a[r + 1] -= x;
b[l] -= (l - 1) * x
b[r] += (l - 1) * x + (r - l + 1) * x;

*/

void change(int pos, int x){
  for (; pos < N; pos |= pos + 1)
    t[pos] += x;
}

ll get(int pos){
  ll ans = 0;
  for (; pos >= 0; pos = (pos & (pos + 1)) - 1)
    ans += t[pos];
  return ans;
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