/*
основной смысл Мо в том, что бы отсортить запросы для минимизации действий в программе, пусть у нас есть q запросов вида узнаьт что-то на отрезке с l по r,
тогда первым делом разобьем из на k блоков по левой границе, а потом посортим каждый из блоков внутри себя по правой границе (тут уже можно сортить по-разному,
и от этого будет различаться оптимальность алга, ниже приведен пример с простой сортировной по возрастанию). Далее мы перебираем блоки, и в каждом из них перебираем
запросы, мейн идея как раз в том, что бы минимизировать кол-во пересчетов (в нашем случае это add и del).
Вот задача, под которую писался этот код: https://codeforces.com/problemset/problem/86/D?locale=ru
Kerb9_
*/

#include "../main-template/main.cpp"

using namespace std;

const int k = 500;
vector<int> a(2e5);

struct Qu {
    int ind, l, r;
};

vector<int> cnt(1e6 + 1);
int res = 0;

void add (int i) {
    res -= a[i] * cnt[a[i]] * cnt[a[i]];
    cnt[a[i]]++;
    res += a[i] * cnt[a[i]] * cnt[a[i]];
}

void del (int i) {
    res -= a[i] * cnt[a[i]] * cnt[a[i]];
    cnt[a[i]]--;
    res += a[i] * cnt[a[i]] * cnt[a[i]];
}

void solve () {
    int n, tt; cin >> n >> tt;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int sz = n / k + 1;
    vector<vector<Qu>> b(sz);
    vector<int> answ(tt);
    for (int i = 0; i < tt; i++) {
        Qu q;
        cin >> q.l >> q.r; q.l--; q.r--;
        q.ind = i;
        b[q.l / k].push_back(q);
    }
    for (int i = 0; i < sz; i++) {
        sort(b[i].begin(), b[i].end(), [ & ](Qu i, Qu j) {
            if (i.r == j.r) return i.l < j.l;
            return i.r < j.r;
        });
    }
    for (int i = 0; i < sz; i++) {
        int l = i * sz, r = i * sz;
        for (Qu q : b[i]) {
            int tl = q.l, tr = q.r;
            while (r <= tr) {
                add(r);
                r++;
            }
            while (l < tl) {
                del(l);
                l++;
            }
            while (l > tl) {
                l--;
                add(l);
            }
            answ[q.ind] = res;
        }
        cnt.assign(1e6 + 1, 0);
        res = 0;
    }
    for (auto el : answ) cout << el << '\n';
}