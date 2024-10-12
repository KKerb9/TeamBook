#include "../main-template/main.cpp"

// 1-indexing
struct Fenwick {
    vector<int> t;

    Fenwick() {}

    Fenwick(int n) {
        build(n);
    }

    void build(int n) {
        t.assign(n + 1, 0);
    }

    Fenwick(const vector<int>& src) {
        build(src);
    }

    void build(const vector<int>& src) {
        t.assign(src.size() + 1, 0);
        for (int i = 1; i <= src.size(); ++i)
            t[i] = t[i - 1] + src[i - 1];
        for (int i = src.size(); i > 0; --i)
            t[i] -= t[i - (i & -i)];
    }

    int sum(int r) {
        int res = 0;
        for (int i = r; i > 0; i -= i & -i)
            res += t[i];
        return res;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int pos, int x) {
        for (int i = pos; i < t.size(); i += i & -i)
            t[i] += x;
    }

    // спуск по фенвику
    // в данном случае - поиск префикса с суммой < s 
    int lower_bound (int s) {
        int k = 0;
        int logn = ceil(log2(t.size() - 1));
        for (int l = logn; l >= 0; l--) {
            if (k + (1<<l) < t.size() && t[k + (1<<l)] < s) {
                k += (1<<l);
                s -= t[k];
            }
        }
        return k;
    }
};
