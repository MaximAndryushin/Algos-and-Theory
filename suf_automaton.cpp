#include <map>
using namespace std;

struct Automaton {
    struct State {
        int link;
        int len;
        map<char, int> go;

        State() : link(-1), len(0) {}; 
    };

    Automaton() : last{0}, vec(1) {};

    void add(char c) {
        int n = vec.size();
        vec.emplace_back();
        vec[n].len = vec[last].len + 1;
        int p = last;
        for (; p != -1 && !vec[p].go.contains(c); p = vec[p].link) {
            vec[p].go[c] = n;
        }
        if (p == -1) {
            vec[0].go[c] = n;
            vec[n].link = 0;
        } else {
            if (vec[p].len + 1 == vec[vec[p].go[c]].len) {
                vec[n].link = vec[p].go[c];
            } else {
                int q = vec[p].go[c];
                int nq = vec.size();
                vec.emplace_back();
                vec[nq] = vec[q];
                vec[nq].len = vec[p].len + 1;
                for (; vec[p].go[c] == q; p = vec[p].link) {
                    vec[p].go[c] = nq;
                }
            }
        }
    }

private:
    int last;
    vector<State> vec;
};