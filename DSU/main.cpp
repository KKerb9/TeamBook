#include "C:\Code\Repos\TeamBook\main-template\main.cpp"

using namespace std;

struct DSU {
    int n; 
    vector<int> p;
    vector<int> sz;

    DSU (int n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        sz.resize(n, 1);
    }

    int getRoot (int v) {
        if (p[v] == v) return v;
        return p[v] = getRoot(p[v]);
    }

    bool unite (int a, int b) {
        a = getRoot(a);
        b = getRoot(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};