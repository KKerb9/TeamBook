/*
я еще не проверял нормально, это порсто наброски, буду доделывать, заодно Ляховца помочь попрошу
*/

#include "..\main-template\main.cpp"

using namespace std;

mt19937 rng(42);

struct Pivo {
    int key, pr;
    Pivo *l = nullptr, *r = nullptr;
    Pivo (int _key) : key(_key) {
        pr = rng();
    }
};

Pivo *root = nullptr;

Pivo* merge(Pivo *v, Pivo *u) {
    if (!v) return u;
    if (!u) return v;
    if (v->pr >= u->pr) {
        v->r = merge(v->r, u);
        return v;
    } else {
        u->l = merge(v, u->l);
        return u;
    }
}

// void split(Pivo *t, Pivo *&v, Pivo *&u, int key) {
//     if (!t) {
//         v = nullptr;
//         u = nullptr;
//         return;
//     }
//     if (t->key < key) {
//         split(t->r, t->r, u, key);
//         v = t;
//     } else {
//         split(t->l, v, t->l, key);
//         v = t;
//     }
// }

pair<Pivo*, Pivo*> split(Pivo *t, int key) {
    if (!t) {
        return {nullptr, nullptr};
    }
    if (t->key < key) {
        auto [t1, t2] = split(t->r, key);
        t->r = t1;
        return {t1, t2};
    } else {
        auto [t1, t2] = split(t->l, key);
        t->l = t2;
        return {t1, t2};
    }
}

void insert(int key) {
    auto [t1, t2] = split(root, key);
    Pivo *t = new Pivo(key);
    root = merge(t1, merge(t, t2));
}

void erase(int key) {
    auto [t1, t2] = split(root, key);
    auto [t1m, t2m] = split(t1, key - 1);
    delete t2m;
    root = merge(t1m, t2);
}
