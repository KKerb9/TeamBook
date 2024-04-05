#include "../main-template/main.cpp"

using namespace std;

struct Hash { // предполгаются символы от 'a' до 'z'
    ll P;
    ll x_;
    vector<ll> h;
    vector<ll> x;
    Hash (const string& s, ll p = 998244353, ll xi = 31) : P(p), x_(xi) {
        int len = s.length();
        h.resize(len + 1);
        x.resize(len + 1);
        h[0] = 0;
        x[0] = 1;
        for(int i = 0; i < len; ++i){
            h[i + 1] = (h[i] * x_ + s[i] - ('a' - 1)) % P;
            x[i + 1] = (x[i] * x_) % P;
        }
    }

    bool equal(int start1, int start2, int l) {
        return (h[start1 + l] + h[start2] * x[l]) % P == (h[start2 + l] + h[start1] * x[l]) % P;
    }
};

signed main() {
    
}