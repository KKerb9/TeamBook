#include "../main-template/main.cpp"

vector<int> nfunc(string s) {
    int n = s.length();
    vector<int> nf(n); nf[0] = n;
    int l = 0, r = 1;
    for (int i = 1; i < n; i++) {
        if (i < r) nf[i] = min(nf[i - l], r - i);
        while (i + nf[i] < n && s[nf[i]] == s[i + nf[i]]) nf[i]++;
        if (i + nf[i] > r) {
            l = i;
            r = i + nf[i];
        }
    }
    return nf;
}
