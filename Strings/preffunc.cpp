#include "../main-template/main.cpp"

vector<int> preffunc(string s) {
    vector<int> p(s.size(), 0);
    for (int i = 1; i < s.size(); ++i) {
        int j = p[i - 1];
        for (; j > 0 && s[i] != s[j]; j = p[j - 1]) {}
        if (s[i] == s[j]) {
            p[i] = j + 1;
        }
    }
    return p;
}
