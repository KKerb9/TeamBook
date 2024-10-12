#include "../main-template/main.cpp"

// взято из https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp> // Общий файл. 
#include <ext/pb_ds/tree_policy.hpp> // Содержит класс tree_order_statistics_node_update
// либо #include <ext/pb_ds/detail/standard_policies.hpp> вместо двух предыдущих

using namespace __gnu_pbds;

// все операции из std::set + find_by_order() и order_of_key()
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
