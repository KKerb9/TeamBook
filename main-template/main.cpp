// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("sse4.2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

// #define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

// #include <ext/pb_ds/assoc_container.hpp>

// using namespace __gnu_pbds;

// using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
template<typename T1, typename T2>
using pr = pair<T1, T2>;
using pii = pair<int, int>;
const int MOD = 1e9 + 7;
const int INF = 1e9;
int t = 1;

template<typename T>
inline void print (vector<T> &arr) {
    for (auto el : arr) cout << el << ' ';
    cout << '\n';
}

////////////////////////////////////////////////////////////////////////////////////

void solve () {
    
}

////////////////////////////////////////////////////////////////////////////////////

signed main () {

#ifdef LOCAL
    freopen("input.txt", "r", stdin)
    freopen("output.txt", "w", stdout)
    cin >> t
#endif

    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 0; i < t; i++) {
#ifdef LOCAL 
        cout << "Test case #" << i + 1 << " ================" << '\n';
#endif
        solve();
#ifdef LOCAL
        cout << "End Test ====================\n\n";
#endif
    }

    return 0;
}