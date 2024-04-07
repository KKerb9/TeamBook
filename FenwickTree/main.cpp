#include "../main-template/main.cpp"

typedef int T;
struct fenwick {
    vector<T> tree;
    int size;
    // F(i) = i - (i & -i) + 1
    // F(0) = 1, из-за этого 1-индексация
    fenwick (int n) {
        build(n);
    }

    fenwick(vector<T>& src) {
        build(src);
    }

    void build(int n) {
        size = n;
        tree.resize(n + 1, 0);
    }

    void build(const vector<T>& src) {
        build(src.size());
        vector<T> pref(size + 1, 0);
        for (int i = 1; i <= size; ++i)
            pref.at(i) = pref.at(i - 1) + src.at(i - 1);
        for (int i = 1; i <= size; ++i) {
            int f = i - (i & -i) + 1;
            tree.at(i) = pref.at(i) - pref.at(f-1);
        }
    }

    // сумма на префиксе
    T sum(int pos) {
        T res = 0;
        for(; pos > 0; pos -= pos & -pos)
            res += tree.at(pos);
        return res;
    }

    // сумма на отрезке
    T sum (int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // Поиск k-го нуля на отрезке. Если на отрезке меньше k нулей, возвращает -1
    // Для корректной работы необходимо все числа в массиве != 0 заменить на 1
    T kzero(int l, int r, int k) { 
        int left = l - 1;
        int right = r + 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if ((mid - l + 1) - sum(l, mid) >= k) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return (right <= r ? right: -1);
    }

    T get(int pos) {
        return sum(pos, pos);
    }

    void add(int pos, T val) {
        for(; pos <= size; pos += pos & -pos)
            tree.at(pos) += val;
    }
};