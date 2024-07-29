#include "../main-template/main.cpp"

using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// не забыть нормализовать числа: 
/*
int d = gcd(a, b);
if (c % d != 0) {
    cout << "Impossible";
    return 0;
}
auto[x, y] = smart_gcd(a / d, b / d);
x *= c / d;
y *= c / d;
*/

pii smart_gcd(int a, int b) {
    if (b == 0) {
        return {a, b};
    }
    pii xy = smart_gcd(b, a % b);
    return {xy.second, xy.first - xy.second * (a / b)};
}

vector<bool> resheto(int n) {
    vector<bool> prime(n + 1, true);
    prime[0] = 0;
    prime[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (prime[i]) {
            for (int j = 2 * i; j <= n; j += i) {
                prime[j] = false;
            }
        }
    }
    return prime;
}

vector<int> fast_resheto(int n) {
    vector<int> r(n + 1, -1);
    for (int i = 2; i * i <= n; i++) {
        if (r[i] == -1) 
            for (int j = 2 * i; j <= n; j += i) 
                if(r[j] == -1) r[j] = i;
    }
    return r;
}

int binpow(int a, int n, int p) {
    int res = 1;
    a %= p;
    while (n) {
        if (n & 1) {
            res = (res * a) % p;
        }
        n >>= 1;
        a = (a * a) % p;
    }
    return res;
}
