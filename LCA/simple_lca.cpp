#include "../main-template/main.cpp"

using namespace std;

vector<set<int>> g;
vector<vector<int>> up; // up[v][l]
int tt = 0;
vector<int> tin, tout;
const int LOGN = 21;

void dfs(int v, int p = 0) {
    for (int l = 1; l < LOGN; l++) {
        up[v][l] = up[up[v][l - 1]][l - 1];
    }
    tin[v] = tt++;
    for (auto u : g[v]) {
        if (u != p) {
            up[u][0] = v;
            dfs(u, v);
        }
    }
    tout[v] = tt;
}

bool is_pred(int a, int b) { // a -- предок b
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (is_pred(a, b)) return a;
    if (is_pred(b, a)) return b;
    
    for (int l = LOGN - 1; l >= 0; l--) {
        if (!is_pred(up[a][l], b)) {
            a = up[a][l];
        }
    }
    return up[a][0];
}