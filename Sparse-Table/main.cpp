#include "..\main-template\main.cpp"

using namespace std;

const int MAXN = 1e5;

int table [30][MAXN];

int get(int l, int r) { // [l, r)
    l--;
    if (r < l) swap(l, r);
    int k = __lg(r - l);
    return min(table[k][l], table[k][r - (1 << k)]);
}

void build(vector<int> &a, int n) {
    for (int i = 0; i < n; i++) {
        table[0][i] = a[i];
    }
    for (int l = 1; l <= 29; l++) {
        for (int i = 0; i + (1 << l) <= n; i++) {
            table[l][i] = min(table[l - 1][i], table[l - 1][i + (1 << (l - 1))]);
        }
    }
}