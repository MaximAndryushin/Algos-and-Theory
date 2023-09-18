#include <vector>
#include <queue>

using namespace std;

template <std::size_t A_SIZE, int FIRST_A>
struct Trie {
    constexpr auto NUL = -1;

    struct Node {
        int link;
        int nextTerm;
        int par;
        int symb;
        vector<int> next;
        vector<int> go;
        vector<int> term;

        Node() : link{0}, nextTerm{NUL}, par{NUL}, symb{NUL},
                 next(A_SIZE, NUL), go(A_SIZE, NUL) {}     
    };

    Trie() : trie(1), templateCounter{0} {}

    template <typename Container>
    void add(const Container& c) {
        int cur = 0;
        for (auto s: c) {
            int id = s - FIRST_A;
            if (trie[cur].next[id] == NUL) {
                trie[cur].next[id] = trie.size();
                trie.emplace_back();
                trie.back().par = cur;
                trie.back().symb = id;
            }
            cur = trie[cur].next[id];
        }
        trie[cur].term.push_back(templateCounter++);
    }

    void build() {
        queue<int> q;
        
        for (int s = 0; s < A_SIZE; ++s) {
            if (trie[0].next[s] != -1) {
                trie[0].go[s] = trie[0].next[s];
                q.emplace(trie[0].go[s]);
            } else {
                trie[0].go[s] = 0;
            }
        }

        while(!q.empty()) {
            int v = q.front();
            q.pop();

            trie[v].link = trie[v].par ? trie[trie[trie[v].par].link].go[trie[v].symb] : 0;
            trie[v].nextTerm = !trie[trie[v].link].isTerm.empty() ? trie[v].link : trie[trie[v].link].nextTerm;

            for (int s = 0; s < A_SIZE; ++s) {
                if (trie[v].next[s] != NUL) {
                    trie[v].go[s] = trie[v].next[s];
                    q.emplace(trie[v].go[s]);
                } else {
                    trie[v].go[s] = trie[trie[v].link].go[s];
                }
            } 
        }
    }

    template <typename Container>
    vector<int> calc(const Container& c) {
        int v = 0;
        vector<bool> used(trie.size(), 0);
        vector<int> found;

        for (auto s: c) {
            int id = s - FIRST_A;
            v = trie[v].go[id];

            for (int u = v; u && !used[u]; u = trie[u].nextTerm) {
                used[u] = 1;
                for (int tid: t[u].term) {
                    found.emplace_back(tid);
                }
            }
        }

        return found;
    }

private:
    int templateCounter;
    vector<Node> trie;
};