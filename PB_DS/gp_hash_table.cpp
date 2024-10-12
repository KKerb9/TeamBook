#include "../main-template/main.cpp"

// взято из https://codeforces.com/blog/entry/60737
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/HashMap.h
#include <bits/extc++.h>
struct chash { // large odd number for C
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};

// если есть возможность взлома посылки, использовать этот вариант
// const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
// struct chash {
//     int operator()(int x) const { return x ^ RANDOM; }
// };

// кажется, не поддерживает итерацию по всему контейнеру, но оно и не нужно, как правило
gp_hash_table<int, int, chash> table({},{},{},{}, {1 << 16});
