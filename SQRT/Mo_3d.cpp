#include "../main-template/main.cpp"

struct Qu {
    int type, l, r, ind, p, x, t, lst;  // t -- сколько запросов изменения до get-а
};

const int K = 1000;

int getCoord(vector<int>& nums, int x) {
    return lower_bound(all(nums), x) - nums.begin();
}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int sz = n / K + 1;
    vector<int> nums;
    for (auto el : a) nums.push_back(el);
    vector<vector<vector<Qu>>> bls(sz, vector<vector<Qu>>(sz));
    vector<Qu> upds;
    int cnt = 0;
    vector<int> neww = a;
    for (int i = 0; i < q; i++) {
        int type; cin >> type;
        if (type == 1) {
            int l, r; cin >> l >> r; l--;
            Qu cur; cur.ind = i; cur.type = type; cur.l = l; cur.r = r; cur.t = cnt;
            bls[l / K][r / K].push_back(cur);
        } else {
            int p, x; cin >> p >> x; p--;
            nums.push_back(x);
            Qu cur; cur.ind = i; cur.p = p; cur.x = x; cur.type = type; cur.t = cnt, cur.lst = neww[p];
            neww[p] = x;
            upds.push_back(cur);
            cnt++;
        }
    }
    sort(all(nums));
    nums.resize(unique(all(nums)) - nums.begin());
    vector<int> el_ind(n + q);
    for (int i = 0; i < n; i++) {
        el_ind[i] = getCoord(nums, a[i]);
    }
    for (int i = 0; i < (int)upds.size(); i++) {
        el_ind[i + n] = getCoord(nums, upds[i].x);
    }
    for (auto &el : upds) {
        el.lst = getCoord(nums, el.lst);
    }
    for (int i = 0; i < sz; i++) {
        if (i % 2) reverse(all(bls[i]));
        for (int j = 0; j < sz; j++) {
            if (j % 2) { 
                sort(all(bls[i][j]), [ & ](Qu l, Qu r){
                    return l.t > r.t;
                });
            } else {
                sort(all(bls[i][j]), [ & ](Qu l, Qu r){
                    return l.t < r.t;
                });
            }
        }
    }
    int l = 0, r = 0, t = 0;
    vector<int> cnt1(n + q);
    vector<int> cnt2(sqrt(2 * n) + 1);
    vector<int> ans(q, -1);
    for (int k = 0; k < sz; k++) {
        for (int kk = 0; kk < sz; kk++) {
            for (auto e : bls[k][kk]) {
                int tl = e.l, tr = e.r, tt = e.t;
                while (l > tl) {
                    l--;
                    int ind = el_ind[l];
                    if (cnt1[ind] < sqrt(2 * n) + 1)
                        cnt2[cnt1[ind]]--;
                    cnt1[ind]++;
                    if (cnt1[ind] < sqrt(2 * n) + 1)
                        cnt2[cnt1[ind]]++;
                }
                while (r < tr) {
                    int ind = el_ind[r];
                    if (cnt1[ind] < sqrt(2 * n) + 1)
                        cnt2[cnt1[ind]]--;
                    cnt1[ind]++;
                    if (cnt1[ind] < sqrt(2 * n) + 1)
                        cnt2[cnt1[ind]]++;
                    r++;
                }
                while (l < tl) {
                    int ind = el_ind[l];
                    if (cnt1[ind] < sqrt(2 * n) + 1)
                        cnt2[cnt1[ind]]--;
                    cnt1[ind]--;
                    if (cnt1[ind] < sqrt(2 * n) + 1)
                        cnt2[cnt1[ind]]++;
                    l++;
                }
                while (r > tr) {
                    r--;
                    int ind = el_ind[r];
                    if (cnt1[ind] < sqrt(2 * n) + 1)
                        cnt2[cnt1[ind]]--;
                    cnt1[ind]--;
                    if (cnt1[ind] < sqrt(2 * n) + 1)
                        cnt2[cnt1[ind]]++;
                }
                while (tt < t) {
                    t--;
                    if (upds[t].p >= l && upds[t].p < r) {
                        int ind = el_ind[n + t];
                        int lst = upds[t].lst;
                        if (cnt1[lst] < sqrt(2 * n) + 1)
                            cnt2[cnt1[lst]]--;
                        cnt1[lst]++;
                        if (cnt1[lst] < sqrt(2 * n) + 1)
                            cnt2[cnt1[lst]]++;
                        
                        if (cnt1[ind] < sqrt(2 * n) + 1)
                            cnt2[cnt1[ind]]--;
                        cnt1[ind]--;
                        if (cnt1[ind] < sqrt(2 * n) + 1)
                            cnt2[cnt1[ind]]++;
                    }
                    el_ind[upds[t].p] = upds[t].lst;
                }
                while (tt > t) {
                    if (upds[t].p >= l && upds[t].p < r) {
                        int ind = el_ind[n + t];
                        int lst = upds[t].lst;
                        if (cnt1[ind] < sqrt(2 * n) + 1)
                            cnt2[cnt1[ind]]--;
                        cnt1[ind]++;
                        if (cnt1[ind] < sqrt(2 * n) + 1)
                            cnt2[cnt1[ind]]++;

                        if (cnt1[lst] < sqrt(2 * n) + 1)
                            cnt2[cnt1[lst]]--;
                        cnt1[lst]--;
                        if (cnt1[lst] < sqrt(2 * n) + 1)
                            cnt2[cnt1[lst]]++;
                    }
                    el_ind[upds[t].p] = el_ind[n + t];
                    t++;
                }
                int curans = cnt2.size();
                for (int i = 1; i < (int)cnt2.size(); i++) {
                    if (!cnt2[i]) {
                        curans = i;
                        break;
                    }
                }
                ans[e.ind] = curans;
            }
        }
    }
    for (auto el : ans) if (el != -1) cout << el << '\n';
}