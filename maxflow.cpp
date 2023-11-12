
#include <algorithm>
#include <queue>
#include <vector>


using namespace std;

template <typename Cap>
struct MFGraph {
    struct Edge {
        int to;
        int rev;
        Cap cap;
    };

    MFGraph(int n) : n(n), g(n) {};

    // a -> b with capacity Cap
    void addEdge(int a, int b, Cap cap) {
        int asz = g[a].size();
        int bsz = g[b].size();
        // direct
        g[a].push_back({
            .to = b,
            .rev = bsz,
            .cap = cap
        });
        // reverse
        g[b].push_back({
            .to = a,
            .rev = asz,
            .cap = 0
        });
    }

    Cap flow(int source, int target) {
        // индекс ребра в вершине, которое еще не заполнено
        vector<int> iter(n, 0);
        // глубина вершины
        vector<int> level(n, -1);

        const auto bfs = [&](int v) {
            queue<int> q;
            q.emplace(v);
            level[v] = 0;
            
            while(!q.empty()) {
                int v = q.front();
                q.pop();
                for (auto& e: g[v]) {
                    if (level[e.to] == -1 && e.cap > 0) {
                        level[e.to] = level[v] + 1;
                        q.emplace(e.to);
                    }
                }
            }
        };

        const auto dfs = [&](int v, Cap up, const auto& self) {
            if (v == target)
                return up;
            Cap result{};
            // здесь используем массив iter
            // чтобы не проходить несколько раз по ребрам с нулевым capacity
            // каждый спуск до target "удаляет" (делает capacity равным 0)
            // как минимум у одного ребра, всего ребер m
            // спуск до target занимаем O(n)
            // таким образом этот dfs работает за O(n * m)
            for (int& i = iter[v]; i < g[v].size(); ++i) {
                auto& e = g[v][i];
                // если по ребру нельзя пройти или ребро не из графа полученного bfs
                if (e.cap == 0 || level[e.to] <= level[v])
                    continue;

                auto& rev_e = g[e.to][e.rev];
                // пытаемся пустить поток размера min(up - result, e.cap)
                // потому что result уже протолкнули,
                // а больше up(это ограничение на поток, которое получилось выше) пустить не можем
                auto d = self(e.to, min(up - result, e.cap), self);
                if (d <= 0) 
                    continue;
                
                e.cap -= d;
                rev_e.cap += d;

                result += d;
            }

            return result;
        };

        Cap result = {};
        while(true) {
            bfs(source);
            if (level[target] == -1)
                break;
            result += dfs(source, numeric_limits<Cap>::max(), dfs);
            fill(level.begin(), level.end(), -1);
            fill(iter.begin(), iter.end(), 0);
        }

        return result;
    }

private:
    int n;
    vector<vector<Edge>> g;
};


int main() {

}
