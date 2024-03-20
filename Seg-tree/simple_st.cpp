/*
это до на максимум с изменением в точке, нумерация с 0, на полуинтервалах
инструкция:
пример использования:
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    Node node;
    SegTree<Node, int> st(a, n);
    st.build(0, 0, n);
    int q; cin >> q; 
    // cout << st.st[0].x << ' ' << st.st[1].x << ' ' << st.st[2].x << ' ' << st.st[5].x << ' ' << st.st[6].x << '\n';
    while (q--) {
        char t; cin >> t;
        if (t == '!') {
            int i, x; cin >> i >> x;
            st.update(i - 1, x, 0, 0, n);
        } else {
            int l, r; cin >> l >> r;
            cout << st.get(l - 1, r, 0, 0, n).x << '\n';
        }
    }
*/

#include "..\main-template\main.cpp"

template<typename Node, typename T>
struct SegTree {
    Node node;
    int MAXN;
    vector<Node> st;
    vector<T> arr;

    SegTree() {};
    SegTree(vector<T>& _arr, int n) {
        arr = _arr;
        st.resize(4 * n);
        MAXN = n;
    }
    
    void build(int v, int l, int r) {
        if (r - l == 1) {
            st[v] = Node(arr[l]);
            return;
        }
        int mid = (r + l) / 2;
        build(2 * v + 1, l, mid);
        build(2 * v + 2, mid, r);
        st[v] = node.merge(st[2 * v + 1], st[2 * v + 2]);
    }

    void update(int i, T& x, int v, int l, int r) {
        if (r - l == 1) {
            st[v] = Node(x);
            return;
        }
        int mid = (r + l) / 2;
        if (i < mid) update(i, x, 2 * v + 1, l, mid);
        else update(i, x, 2 * v + 2, mid, r);
        st[v] = node.merge(st[2 * v + 1], st[2 * v + 2]);
    }

    Node get(int ql, int qr, int v, int l, int r) {
        if (qr <= l || r <= ql) return node.empty_node();
        if (ql <= l && r <= qr) return st[v];
        int mid = (r + l) / 2;
        return node.merge(get(ql, qr, 2 * v + 1, l, mid), get(ql, qr, 2 * v + 2, mid, r));
    }
};

struct Node {
    int x; 

    Node() {};
    Node(int _x) : x(_x) {};  // можно настроить этот коструктор как удобно для билда

    Node empty_node() {
        return Node(0);
    }

    Node merge(const Node& l, const Node& r, bool flag = 0) {
        Node res;
        if (l.x < r.x) res.x = r.x;
        else res.x = l.x;
        return res;
    }
};
