#include <bits/stdc++.h>

#define endl "\n"
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr int N = 5e4 + 5;

// Динамическое прогармирование на подотрезках

// дана строка найти кол-во подстрок, которые являются палиндромами

bool dps[N][N]; // dps[l][r] - палиндром
string s;

// проверить равен ли s[l] == s[r] && dp[l - 1][r - 1]

void calcdps()
{
  for (int i = 0; i < s.size(); i++)
  {
    dps[i][i] = 1;
    if (i != s.size() - 1 && s[i] == s[i + 1])
      dps[i][i + 1] = 1;
  } 
  for (int len = 3; len <= s.size(); len++)
    for (int r = len - 1; r < s.size(); r++)
      dps[r - len][len] = (s[r -  len] == s[r] && dps[r - len + 1][r - 1]);
}

int dp2[N][N]; // тоже самое, только неизвестное состояние равно -1

int rec(int l, int r)
{
  if (dp2[l][r] != -1)
    return dp2[l][r];
  if (l == r)
    dp2[l][r] = 1;
  else if (l + 1 == r)
    dp2[l][r] = (s[l] == s[r]);
  else
  {
    if (s[l] == s[r] && rec(l - 1, r - 1))
      dp2[l][r] = 1;
    else dp2[l][r] = 0;
  }
  return dp2[l][r];
}



// есть массив и 2 игрока. ходят по очереди, удаляют самое левое или самое правое за 1 ход
// победа если сумма удаленных игроком больше суммы другого

int dp3[N][N], a[N], // dp3[l][r] - текущий счет игры (разность первого и второго игрока)
lnk[N][N]; // какой ход нужно делать из текущей позиции
bool used[N][N];

int rec2(int l, int r)
{
  if (used[l][r])
    return dp3[l][r];
  used[l][r] = 1;
  if (l == r)
    return dp3[l][r] = a[l];
  //return max(a[l] - rec(l + 1, r), a[r] - rec(l, r - 1)); // если текущий игрок берет левый или парвый элемент
  if (a[l] - rec(l + 1, r) > a[r] - rec(l, r - 1))
  {
    dp3[l][r] = a[l] - rec(l + 1, r);
    lnk[l][r] = l;
  }  
  else
  {
    dp3[l][r] = a[r] - rec(l + 1, r);
    lnk[l][r] = r;
  }
  return dp3[l][r];
}


//дана строка, найти кол-во подпоследовательностей - палиндромов

int dp4[N][N]; // dp[l][r] - кол-во подполседовательностей палиндромов на отрезке [l, r];

void calc2()
{
  for (int l = 0; l < s.size(); l++)
  {
    dp4[l][l] = 1;
    if (l != s.size() - 1)
      dp4[l][l + 1] = 2 + (s[l] == s[l + 1]);
  } 
  for (int len = 3; len <= s.size(); len++)
    for (int r = len - 1; r < s.size(); r++)
      dp4[r - len][r] = dp4[r - len + 1][r] + dp4[r - len][r - 1] + (s[r] == s[r - len] ? 1 : -dp4[r - len + 1][r - 1]);
}



//НВП

int dp5[N][N];
// dp[pos][last] - находимся в позиции pos и последний взятый элемент имеет индекс last, ответ на суффиксе(идем справа налево)


// O(NlogN)

int dp6[N]; // dp[length] храним минимально возвожное последнее длины length

// переходы 
// при очередном просмотре элемента нас интересует только та последовательность, в которую мы можем добавить элемент.
// находим последний элемент строго меньший нашего и пытаемся добавить



// есть массив. удаляем не крайний элемент, заплатив штраф a[i] * (a[i + 1]  + a[i - 1]), удалить все эл-ты с наим штрафом
// посмотрим на задачу с конца, мы знаем штраф за последний элемент => задача разделилась на 2: от начал массива до полседнего эл-та и от него до конца
int dp[N][N]; // dp[l][r] = min(удалить k - ый элемент + решить задачу для 2 кусков) dp[l][l] = 0, dp[l][l + 1] = 0;

void Solve()
{
  
} 

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Solve();
  return 0;
}