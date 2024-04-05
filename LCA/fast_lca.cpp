#include "../main-template/main.cpp"

using namespace std;

vector<set<int>> g;
vector<int> tin, tout;
vector<pii> order;
int tt = 0;
const int LOGN = 30;
const int MAXN = 1e6 + 1;

pii table[LOGN][MAXN];

pii get_min(int l, int r) { // [l, r)
    if (r < l) swap(l, r);
    r++;
    int k = __lg(r - l);
    return min(table[k][l], table[k][r - (1 << k)]);
}

void dfs (int v, int h, int p = -1) {
    tin[v] = order.size();
    order.emplace_back(h, v);
    for (auto u : g[v]) {
        if (u == p) continue;
        dfs(u, h + 1, v);
        order.emplace_back(h, v);
    }
    tout[v] = order.size() - 1;
}

int lca (int a, int b) {
    int l = min(tin[a], tin[b]);
    int r = max(tout[a], tout[b]);
    return get_min(l, r).second;
}