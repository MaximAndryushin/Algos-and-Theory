#include <vector>
#include <string>
#include <map>
#include <limits>

using namespace std;

struct SuffTree {
    static constexpr auto INF = std::numeric_limits<int>::max() >> 2;

    struct Node {
        int l, r; // ребро, ведущее в эту вершину из родителя (соответствует подстроке s[l:r])
        int link; // суффиксная ссылка (ведет в вершину дерева, которая соответствует той же строке, что и эта вершина, только без первой буквы)
        int par; // индекс родителя вершины
        map<char, int> next; // переходы из вершины (легко заменить на массив)
        Node(int l = 0, int r = 0, int link = -1, int par = 0) : l(l), r(r), link(link), par(par), next{} {}

        int& get(char c) {
            if (next.contains(c - 'a'))
                return next[c - 'a'];
            return next[c - 'a'] = -1;
        }

        int len() const {
            return r - l;
        }
    };
    
    // sz - кол-во верщин в дереве
    SuffTree(int sz = 100) : s{}, cur{}, tree(1) {
        tree.reserve(sz);
        tree[0].link = 0;
    }

    // Локация в дереве (может быть вершиной и позицией на ребре)
    struct State {
        int v; // вершина
        int pos; // позиция от начала ребра ведущего в 'v'

        // заметим:
        // 1) pos == 0 соотвествует родителю вершины 'v' (tree[v].par)
        // 2) pos == tree[v].len() соответствует вершине 'v'
        // 3) остальные 0 < pos < tree[v].len() соответствуют локации на ребре 

        State(int v = 0, int pos = 0) : v(v), pos(pos) {};
    };

    // переход из локации 'cur' по строке s[l:r]
    State go(State st, int l, int r) {
        while(l < r) {
            // если дошли до конца ребра, пробуем сделать переход
            if (st.pos == tree[st.v].len()) {
                st = State(tree[st.v].get(s[l]), 0);
                // если перехода нет, возвращаем "несуществующую" локацию
                if (st.v == -1)
                    return st;
                // иначе продолжаем двигать локацию

                // здесь l не меняется, так как мы выставляем cur.pos = 0, то есть по ребру мы не двигаемся
            } else {
                // если на ребре нет нужной буквы возвращаем "несуществующую" локацию
                if (s[tree[st.v].l + st.pos] != s[l]) {
                    return State(-1, -1);
                }
                // переходим до конца ребра или пока не дойдем до позиции r
                int d = min(tree[st.v].len() - st.pos, r - l);
                l += d;
                st.pos += d;
            }
        }
        return st;
    }

    // по локации расщепляет ребро, если нужно
    int split(State st) {
        // если позиция 0, возвращаем родителя
        if (st.pos == 0) {
            return tree[st.v].par;
        }
        // если позиция равна концу ребра, возвращаем саму вершину
        if (st.pos == tree[st.v].len()) {
            return st.v;
        }
        // иначе расщепляем ребро 
        // хотим получить такое: (parent) ---(s[l : l + pos])---> (new) ---(s[l + pos : r])---> (v)
        // создаем вершину для куска до st.pos
        tree.emplace_back(tree[st.v].l, tree[st.v].l + st.pos, -1, tree[st.v].par);
        // обновляем переход из родителя
        tree[tree[st.v].par].get(s[tree[st.v].l]) = tree.size() - 1;
        // делаем переход в оставшийся кусок
        tree.back().get(s[tree[st.v].l + st.pos]) = st.v;
        // двигаем "начало" ребра у оставшегося куска
        tree[st.v].l += st.pos;
        // меняем родителя оставшегося куска
        tree[st.v].par = tree.size() - 1;
        // возвращаем созданную вершину
        return tree.size() - 1;
    }

    int getLink(int v) {
        // если линка уже посчитана, возврашаем
        if (tree[v].link != -1) 
            return tree[v].link;
        // если дошли до корня возвращаем корень
        if (v == 0) 
            return tree[v].link = 0;

        // иначе насчитаем линку рекурсивно
        int p = tree[v].par;
        // для этого посчитаем линку родителя
        int l = getLink(p);
        // поставим локацию в конец ребра
        auto loc = State(l, tree[l].len());
        // перейдем из новой локации по куску строки от родителя до текущей вершины 
        int le = tree[v].l;
        // если родитель - корень, то нужно убрать 1 букву сначала, чтобы перейти к след суффиксу
        if (p == 0) {
            ++le;
        }
        int ri = tree[v].r;
        auto nex = go(loc, le, ri);
        // разделим ребро если нужно
        return tree[v].link = split(nex);
    }

    void add(char c) {
        s.push_back(c);
        // есть 3 типа локаций:
        // 1) листья
        // 2) внутренние локации, у которых нет перехода по букве 'c'
        // 3) внутренние локации, у которых есть переход по 'c'
        while(true) {
            // пытаемся сделать переход
            auto newState = go(cur, s.size() - 1, s.size());

            // если переход успешный, значит "новых" суффиксов больше не появится с буквой 'c'
            if (newState.v != -1) {
                cur = newState;
                break;
            }

            // для простоты кода можно не пропускать листья,
            // а действовать так же, как и с внутренними локациями
            // на асимптотику это не влияет

            // иначе добавляем вершину (лист)
            int mid = split(cur);
            // так как это лист, пусть правая граница будет бесконечностью
            tree.emplace_back(s.size() - 1, INF, -1, mid);
            // добавляем переход по букве c
            tree[mid].get(c) = tree.size() - 1;
            
            // если дошли до корня, выходим
            if (mid == 0) {
                break;
            }

            // переходим по линке в следующую интересную локацию
            cur.v = getLink(mid);
            cur.pos = tree[cur.v].len();
        }
    }

private:
    string s;
    State cur;
    vector<Node> tree;
};