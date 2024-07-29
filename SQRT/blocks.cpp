#include "../main-template/main.cpp"

struct Block {
    int mdfc = 0;
    vector<int> cur;
    vector<int> cur_not_sorted;
};

struct Qu {
    int l, r, x;
};

const int k = 550;

void solve() {
    int n, m; cin >> n >> m;
    int b_cnt = n / k + 1;
    vector<Block> bls(b_cnt);
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        bls[i / k].cur.push_back(a);
        bls[i / k].cur_not_sorted.push_back(a);
    }
    for (int i = 0; i < b_cnt; i++) {
        sort(all(bls[i].cur));
    }
    vector<Qu> tmp;
    for (int j = 0; j < m; j++) {
        Qu cur;
        char c; cin >> c;
        if (c == '+') {
            cin >> cur.l >> cur.r >> cur.x; cur.l--; cur.r--;
            tmp.push_back(cur);
            if (tmp.size() >= k) {
                for (auto qq : tmp) {
                    int l_block = qq.l / k, l_pos = qq.l % k;
                    int r_block = qq.r / k, r_pos = qq.r % k;
                    if (l_block == r_block) {
                        for (int i = l_pos; i <= r_pos; i++) {
                            bls[l_block].cur_not_sorted[i] += qq.x;
                        }
                        bls[l_block].cur = bls[l_block].cur_not_sorted;
                        sort(all(bls[l_block].cur));
                    } else {
                        for (int i = l_pos; i < k; i++) {
                            bls[l_block].cur_not_sorted[i] += qq.x;
                        }
                        bls[l_block].cur = bls[l_block].cur_not_sorted;
                        sort(all(bls[l_block].cur));
                        l_block++;
                        while (l_block < r_block) {
                            bls[l_block].mdfc += qq.x;
                            l_block++;
                        }
                        for (int i = 0; i <= r_pos; i++) {
                            bls[r_block].cur_not_sorted[i] += qq.x;
                        }
                        bls[r_block].cur = bls[r_block].cur_not_sorted;
                        sort(all(bls[r_block].cur));
                    }
                }
                tmp.clear();
            }
        } else {
            for (auto qq : tmp) {
                int l_block = qq.l / k, l_pos = qq.l % k;
                int r_block = qq.r / k, r_pos = qq.r % k;
                if (l_block == r_block) {
                    for (int i = l_pos; i <= r_pos; i++) {
                        bls[l_block].cur_not_sorted[i] += qq.x;
                    }
                    bls[l_block].cur = bls[l_block].cur_not_sorted;
                    sort(all(bls[l_block].cur));
                } else {
                    for (int i = l_pos; i < k; i++) {
                        bls[l_block].cur_not_sorted[i] += qq.x;
                    }
                    bls[l_block].cur = bls[l_block].cur_not_sorted;
                    sort(all(bls[l_block].cur));
                    l_block++;
                    while (l_block < r_block) {
                        bls[l_block].mdfc += qq.x;
                        l_block++;
                    }
                    for (int i = 0; i <= r_pos; i++) {
                        bls[r_block].cur_not_sorted[i] += qq.x;
                    }
                    bls[r_block].cur = bls[r_block].cur_not_sorted;
                    sort(all(bls[r_block].cur));
                }
            }
            tmp.clear();
            int l, r, x; cin >> l >> r >> x; l--; r--;
            int l_block = l / k, l_pos = l % k;
            int r_block = r / k, r_pos = r % k;
            bool flag = false;
            if (l_block == r_block) {
                for (int i = l_pos; i <= r_pos; i++) {
                    if (bls[l_block].cur_not_sorted[i] == x - bls[l_block].mdfc) { flag = true; break; }
                }
            } else {
                for (int i = l_pos; i < k; i++) {
                    if (bls[l_block].cur_not_sorted[i] == x - bls[l_block].mdfc) { flag = true; break; }
                }
                if (!flag) {
                    for (int i = 0; i <= r_pos; i++) {
                        if (bls[r_block].cur_not_sorted[i] == x - bls[r_block].mdfc) { flag = true; break; }
                    }
                }
                if (!flag) {
                    for (int i = l_block + 1; i < r_block; i++) {
                        int ind = lower_bound(all(bls[i].cur), x - bls[i].mdfc) - bls[i].cur.begin();
                        if (ind < k && bls[i].cur[ind] == x - bls[i].mdfc) {
                            flag = true;
                            break;
                        }
                    }
                }
            }
            if (flag) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}
