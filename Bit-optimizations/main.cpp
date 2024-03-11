#include "C:\Code\Repos\TeamBook\main-template\main.cpp"

using namespace std;

signed main() {
    int a, b; cin >> a >> b;

    // проверить принадлежность бита маске a
    if (a | (1 << b) != a) {
        // не пренадлежит
    }

    
}