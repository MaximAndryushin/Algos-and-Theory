#include <vector>
#include <limits>
#include <queue>
#include <functional>

using namespace std;

template<typename T, typename _Compare  = less<T>>
using CompQueue = priority_queue<T, vector<T>, _Compare>;


template <typename Cap, typename Cost>
struct MFGraph {
    struct Edge {
        int to;
        int rev;
        Cap cap;
        Cost cost;
    };
 
    struct Edge2 {
        int from;
        int to;
        Cap cap;
        Cost cost;
    };
 
    MFGraph(int n) : n(n), g(n) {};
 
    // a -> b with capacity Cap
    void addEdge(int a, int b, Cap cap, Cost cost = {}) {
        int asz = g[a].size();
        int bsz = g[b].size();
        // direct
        g[a].push_back({
            .to = b,
            .rev = bsz,
            .cap = cap,
            .cost = cost
        });
        // reverse
        g[b].push_back({
            .to = a,
            .rev = asz,
            .cap = 0,
            .cost = -cost
        });
        edges.push_back({
            .from = a,
            .to = b,
            .cap = cap,
            .cost = cost
        });
    }
 
    pair<Cap, Cost> flow(int source, int target, bool has_negative_edges = false) {
        vector<Cost> pot(n, 0);
        // ford bellman
        if (has_negative_edges) {
            std::fill(pot.begin(), pot.end(), numeric_limits<Cost>::max());
            pot[source] = 0;
            for (int i = 1; i < n; ++i) {
                for (const auto& [from, to, _, cost]: edges) {
                    if (pot[from] == numeric_limits<Cost>::max())
                        continue;
                    pot[to] = min(pot[to], pot[from] + cost);
                }
            }
        }
 
        Cap f = 0;
        Cost c = 0;
 
        while(true) {
            CompQueue<pair<Cost, int>, greater<>> q;
            q.emplace(0, source);
            vector<Cost> dist(n, numeric_limits<Cost>::max());
            vector<bool> used(n, 0);
            dist[source] = 0;
            vector<pair<int, int>> par(n);
            while(!q.empty()) {
                auto [d, v] = q.top();
                q.pop();
                if (d != dist[v] || used[v])
                    continue;
                used[v] = 1;
                for (const auto& [u, u_id, cap, cost]: g[v]) {
                    if (used[u] || cap == 0)
                        continue;
                    Cost weight = pot[v] + cost - pot[u];
                    if (d + weight >= dist[u])
                        continue;
                    dist[u] = d + weight; 
                    par[u] = {v, u_id};
                    q.emplace(dist[u], u);
                }
            }
            if (!used[target])
                break;
            Cap min_f = numeric_limits<Cap>::max();
            for (int v = target; v != source;) {
                const auto& [p, id] = par[v];
                const auto& rev_e = g[v][id];
                const auto& e = g[p][rev_e.rev];
                min_f = min(e.cap, min_f);
                v = p;
            }
            for (int v = target; v != source;) {
                const auto& [p, id] = par[v];
                auto& rev_e = g[v][id];
                auto& e = g[p][rev_e.rev];
 
                e.cap -= min_f;
                rev_e.cap += min_f;
 
                v = p;
            }
 
            for (int i = 0; i < n; ++i) {
                dist[i] += pot[i] - pot[source];
            }
 
            f += min_f;
            c += min_f * dist[target];
 
            pot.swap(dist);
        }
 
        return {f, c};
    }
 
private:
    int n;
    vector<vector<Edge>> g;
    vector<Edge2> edges;
};

int main() {

}