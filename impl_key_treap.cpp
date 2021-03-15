#include<bits/stdc++.h>

#define endl "\n"
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr int N = (1 << 10);

//Декартовы деревья по неявному ключу
//неявные ключи - kth порядковая статистика(номер ключа при обходе от меньшего к большему)
//храним в вершине кол-во вершин в поддереве
//split на два правильных дерева left and right, так чтобы size был


//сумма на подотрезке

struct Node{
  bool isassigned;
  bool isrev;
  int pri;
  int sz;
  ll val;
  ll sum;
  ll assigned; //seqment assignment
  Node *l, *r;
  explicit Node(ll v) :
    pri(rand()<<16 + rand()),
    val(v), sum(v), sz(1),
    isrev(0),
    isassigned(0), assigned(0),
    l(nullptr), r(nullptr){};
};
using pN = Node*;
using pNN = pair<Node*, Node*>;

int getsz(Node* v){
  return v == nullptr ? 0 : v->sz;
}

void recalcsz(Node *v){
  if (v == nullptr)
    assert(false);
  v->sz = getsz(v->l) + getsz(v->r) + 1; 
}

ll getsum(Node* v){
  return v == nullptr ? 0 : v->sum;
}

void recalcsum(pN v){
  if (v == nullptr)
    assert(false);
  v->sum = getsum(v->l) + getsum(v->r) + v->val; 
}

void recalc(pN v){
  recalcsz(v);
  recalcsum(v);
}

pNN split(pN v, int k){
  if (k == 0)
    return {nullptr, v};
  push(v);
  if (getsz(v->l) >= k){
    pNN p = split(v->l, k);
    v->l = p.second;
    recalc(v);
    return {p.first, v};
  }
  else{
    pNN p = split(v->r, k - getsz(v->l) - 1);
    v->r = p.first;
    recalc(v);
    return {v, p.second};
  }
}

pN merge(pN l, pN r){
  if (l == nullptr)
    return r;
  if (r == nullptr)
    return l;
  if (l->pri < r->pri){
    push(l);
    l->r = merge(l->r, r);
    recalc(l);
    return l;
  }
  else{
    push(r);
    r->l = merge(l, r->l);
    recalc(r);
    return r;
  }
}

ll findsum(pN &v, int l, int r){
  pNN p = split(v->l, l - 1);
  pNN p2 = split(p.second, r - l + 1);
  ll s = getsum(p2.first);
  v = merge(merge(p.first, p2.first), p2.second);
  return s;
}

pN rotate(pN v, int k){
  pNN p = split(v, k);
  return merge(p.second, p.first);
}

void assignOnTree(pN v, ll val){
  if (v == nullptr)
    return;
  v->isassigned = 1;
  v->assigned = val;
  v->val = val;
  v->sum = v->sz * val;
}

void reverseOnTree(pN v){
  if (v == nullptr)
    return;
  v->isrev ^= 1;
  swap(v->l, v->r);
} 

void push(pN v){
  if (v == nullptr)
    return;
  if (v->isassigned){
    assignOnTree(v->l, v->assigned);
    assignOnTree(v->r, v->assigned);
    v->isassigned = 0;
  }
  if (v->isrev){
    reverseOnTree(v->l);
    reverseOnTree(v->r);
    v->isrev = 0;
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