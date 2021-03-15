#include<bits/stdc++.h>

#define endl "\n"
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr int N = 1e3 + 5;

//Treap декартово дерево

/* treap's operations 
-1) split
0) merge
1) insert
2) erase
3) search
4) kthorderstatistics
5) number of elemnts that less than x
*/

//правильная скобочная посл-сть <=> двоичное дерево поиска (leftchild)rightchild

// вершина ключ - приоритет

//если посорчено по ключам можно охуенно строить
/*идем слева направо по ключ/приориитетам
 идем с крайнего правого эл-та дерева(макс элемент) и находим элемент с меньшим приоритетом, переподвешиваем
*/
template<typename T>
struct Node {
  T key;
  int pr;
  size_t sz;
  Node<T> *l, *r;
  Node<T>() = default;
};

template<typename T>
Node<T>* make(T val) {
  return new Node<T>(val, rand(), 1, nullptr, nullptr);
}

template<typename T>
size_t get(Node<T>* tr) {
  return tr == nullptr ? 0 : tr->sz;
}

template<typename T>
void recalc(Node<T>* tr) {
  tr->sz = get(tr->l) + get(tr->r) + 1;
}

template<typename T>
pair<Node<T>*, Node<T>*> split(Node<T>* tr, T val) {
  if (!tr)
    return {nullptr, nullptr};
  if (tr->key <= val){
    pair<Node<T>*, Node<T>*> p = split(tr->r, val);
    tr->r = p.first;
    recalc(tr);
    return {tr, p.second};
  }
  else {
    pair<Node<T>*, Node<T>*> p = split(tr->l, val);
    tr->l = p.second;
    recalc(tr);
    return {p.first, tr};
  }
}

template<typename T>
Node<T>* merge(Node<T>* l, Node<T>* r) {
  if (l == nullptr)
    return r;
  else if (r == nullptr)
    return l;
  if (l->pr < r->pr){
    l -> r = merge(l->r, r);
    recalc(l);
    return l;
  }
  else {
    r -> l = merge(l, r->l);
    recalc(r);
    return r;
  }
}

template<typename T>
Node<T>* insert(Node<T> tr, T val) {
  pair<Node<T>*, Node<T>*> p = split(tr, val);
  Node<T>* nv = make(val);
  return merge(p.first, merge(nv, p.second));
}

template<typename T>
Node<T>* erase(Node<T>* tr, T val) {
  pair<Node<T>*, Node<T>*> p = split(tr, val);
  auto p2 = split(p.first, val - 1);
  delete p2.second;
  return merge(p2.first, p.second);
}


template<typename T>
T findkth(Node<T>* tr, int k) {
  if (get(tr->l) >= k)
    return findkth(tr->l, k);
  else if (get(tr->l) + 1 == k)
    return tr->key;
  else
    return findkth(tr->r, k - get(tr->l) - 1);
}


void Solve() {
 
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  Solve();
  return 0;
}