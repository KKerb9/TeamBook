#include "../main-template/main.cpp"

struct Node {
    int mx = 0;
    int cnt = 0;

    Node() {
        mx = 0;
        cnt = 0;
    }

    Node(int _mx, int _cnt) : mx(_mx), cnt(_cnt) {
    }
};

Node merge(const Node& l, const Node& r) {
    Node res;
    if (l.mx > r.mx) {
        res = l;
    } else if (l.mx == r.mx) {
        res = Node(l.mx, l.cnt + r.cnt);
    } else {
        res = r;
    }
    return res;
}

struct DST {
    int LOG;
    int n;
    vector<vector<Node>> st;

    DST(){
    }

    DST(vector<int> &a, int _n, int _LOG) : n(_n), LOG(_LOG) {
        st.resize(LOG, vector<Node>(n + 1));
        int h = 31 - __builtin_clz(n) + 1;

        for (int lvl = 0; lvl < h; lvl++) {
            int len = (1 << lvl);
            for (int mid = len; mid < n + len; mid += 2 * len) {
                // cerr << mid << ' ' << lvl << ' ' << len << '\n';
                // st[lvl][mid] = Node(a[mid], 1);
                // st[lvl][mid - 1] = Node(a[mid - 1], 1);
                Node pref(0, 0);
                for (int i = mid; i < mid + len && i <= n; i++) {
                    if (i != n) 
                        // st[lvl][i] = merge(st[lvl][i - 1], Node(a[i], 1));
                        st[lvl][i + 1] = merge(st[lvl][i], Node(a[i], 1));
                }
                for (int i = min(mid - 1, n - 1); i >= mid - len; i--) {
                    st[lvl][i] = merge(st[lvl][i + 1], Node(a[i], 1));
                }
            }
        }
    }

    Node get(int l, int r) {  // [left, right)
        int fbit = 31 - __builtin_clz(l ^ r);
        return merge(st[fbit][l], st[fbit][r]);
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int q, x, y, z, t; cin >> q >> x >> y >> z >> t;
    int lst = 0;
    int ans = 1;
    DST aboba(a, n, 30);
    for (int i = 0; i < q; i++) {
        int l = (lst * x + y) % n, r = (lst * z + t) % n;
        if (r < l) swap(r, l);
        Node res = aboba.get(min(l, r + 1), max(l, r + 1));
        // cout << l << ' ' << r + 1 << ' ' << res.mx << ' ' << res.cnt << '\n';
        lst = res.cnt;
        ans = (ans * res.cnt + MOD) % MOD;
    }
    cout << ((ans > 0) ? ans : ans + MOD) << '\n';
}