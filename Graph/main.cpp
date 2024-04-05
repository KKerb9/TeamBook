#include "../main-template/main.cpp"

using namespace std;

vector<vector<int>> g;  // граф
vector<int> used, h, up;  // посещ. верш, высота вершины v, мин высота на которую можно подняться из v через вершины ниже неё 

// поиск мостов, без кр ребер и прочего говна

void dfs(int v, int p = -1) {
    used[v] = true;
    up[v] = h[v];
    for (auto u : g[v]) {
        if (u == p) continue;
        if (used[v]) up[v] = min(up[v], h[u]);
        else {
            h[u] = h[v] + 1;
            dfs(u, v);
            up[v] = min(up[v], up[u]);
            if (up[u] > h[v]) {
                // ААА МОСТ
            }
        }
    }
}

// поис ct_pt тоже граф без говна

void dfs(int v, int p = -1) {
    used[v] = true;
    up[v] = h[v];
    int cnt = 0;
    for (auto u : g[v]) {
        if (u == p) continue;
        if (used[v]) up[v] = min(up[v], h[u]);
        else {
            h[u] = h[v] + 1;
            dfs(u, v);
            up[v] = min(up[v], up[u]);
            cnt++;
            if (v != -1 && up[u] >= h[v]) {
                // ААА cut_pt
            }
        }
    }
    if (v == -1 && cnt > 1) {
        // ААА ct_pt 
    }
}

// разбиение на компоненты верш. двусвязанности, предположительно h и up посчитаны

vector<int> colors;
int col = 0;  // макс цвет

void find_comps(int v, int c, int p = -1) {
    colors[v] = c;
    used[v] = true;
    for (auto u : g[v]) {
        if (u == p) continue;
        if (used[u] && h[u] < h[v]) {
            colors[u] = c;
        } else if (!used[u]) {
            if (up[u] > h[v]) {
                int nc = ++col;
                colors[u] = nc;
                find_comps(u, nc, v);
            } else {
                colors[u] = c;
                find_comps(u, c, v);
            }
        }
    }
}

// BFS

vector<int> BFS(vector<vector<int>> &g, set<int> &sv, int n) {
    vector<int> dist(n, INF);
    queue<int> q;
    for (auto v : sv) {
        dist[v] = 0;
        q.push(v);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto u : g[v]) {
            if (dist[u] > dist[v] + 1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    return dist;
}

// dijkstra

vector<int> p;  // если надо восстановить путь

int dijkstra(vector<vector<pii>> &g, int s, int f, int n) {
    vector<int> dist(n, INF);
    dist[s] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> notVis;
    // for (int v = 0; v < n; v++) {
    //     notVis.emplace(dist[v], v);
    // }
    notVis.emplace(0, s);
    while(!notVis.empty()) {
        auto [d1, v] = notVis.top();
        notVis.pop();
        if (v == f) break;
        if (d1 > dist[v]) continue;
        for (const auto& [u, d2] : g[v]) {
            if (dist[u] > d2 + d1) {
                dist[u] = d1 + d2;
                notVis.emplace(d1 + d2, u);
                p[u] = v;
            }
        }
    }
    return dist[f];
}
