/*
мейн идея в том что бы 1) посортить r по /\ 2) убрать константу/лог из add && del. Так же подбирайте константу k. Эта поебота просто летает ежжи а когда не делали?!
*/

#include <bits/stdc++.h>

// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

// #define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

const int k = 1100;

struct Q {
    int ind = 0, l = 0, r = 0;
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int n; cin >> n;
    int arr[n];
    int a[n];
    map<int, int> el_num;
    int num = 1;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (el_num[arr[i]] == 0) {
            el_num[arr[i]] = num;
            a[i] = num;
            num++;
        } else {
            a[i] = el_num[arr[i]];
        }
    }
    int q; cin >> q;
    int b_cnt = n / k + 1;
    vector<vector<Q>> b(b_cnt);
    vector<ll> ans(q);
    vector<pii> asks(q);
    for (int i = 0; i < q; i++) {
        Q cur;
        cin >> cur.l >> cur.r;
        cur.l--;
        cur.r--;
        cur.ind = i;
        b[cur.l / k].push_back(cur);
        asks[i] = {cur.l, cur.r};
    }
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] ^ arr[i - 1];
    }
    for (int m = 0; m < b_cnt; m++) {
        if (m % 2 == 0) {
            sort(b[m].begin(), b[m].end(), [ & ](Q i, Q j) {
                if (i.r == j.r) return i.l < j.l;
                return i.r < j.r;
            });
        } else {
            sort(b[m].begin(), b[m].end(), [ & ](Q i, Q j) {
                if (i.r == j.r) return i.l > j.l;
                return i.r > j.r;
            });
        }
    }
    vector<int> el_cnt(1e6 + 1);
    int l = 0, r = -1;
    int res = 0;
    for (int i = 0; i < b_cnt; i++) {
        for (const Q &cur : b[i]) {
            int tl = cur.l, tr = cur.r;
            while (r < tr) {
                r++;
                if (el_cnt[a[r]] == 0) {
                    res ^= arr[r];
                }
                el_cnt[a[r]]++;
            }
            while (l > tl) {
                l--;
                if (el_cnt[a[l]] == 0) {
                    res ^= arr[l];
                }
                el_cnt[a[l]]++;
            }
            while (r > tr) {
                el_cnt[a[r]]--;
                if (el_cnt[a[r]] == 0) {
                    res ^= arr[r];
                }
                r--;
            }
            while (l < tl) {
                el_cnt[a[l]]--;
                if (el_cnt[a[l]] == 0) {
                    res ^= arr[l];
                }
                l++;
            }
            ans[cur.ind] = res;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << (pref[asks[i].second + 1] ^ pref[asks[i].first] ^ ans[i]) << '\n';
    }

    return 0;
}