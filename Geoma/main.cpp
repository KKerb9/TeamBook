#include "../main-template/main.cpp"

using namespace std;

const int EPS = 1e-8;

int sgn(ld a) {
    if (a > EPS) {
        return 1;
    } else if (a < -EPS) {
        return -1;
    } else {
        return 0;
    }
}

bool eq(ld a, ld b) {
    return abs(a - b) <= EPS;
}

bool sml(ld a, ld b) {
    return a + EPS < b;
}

bool grt(ld a, ld b) {
    return a - EPS > b;
}

bool smleq(ld a, ld b) {
    return a - EPS <= b;
}

bool grteq(ld a, ld b) {
    return a + EPS >= b;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

struct pt {
    ld x = 0;
    ld y = 0;
    pt() = default;
    explicit pt(ld x, ld y) : x(x), y(y) {
    }
    explicit pt(const pt& from, const pt& to) {
        x = to.x - from.x;
        y = to.y - from.y;
    }

    pt perp() const {
        return pt(-y, x);
    }
    ld lenlen() const {
        return x * x + y * y;
    }
    ld len() const {
        return sqrt(x * x + y * y);
    }
    pt operator+ (const pt& other) const {
        return pt(x + other.x, y + other.y);
    }
    pt operator- (const pt& other) const {
        return pt(x - other.x, y - other.y);
    }
    ld operator^ (const pt& other) const {  // скалярное
        return x * other.x + y * other.y;
    }
    ld operator% (const pt& other) const {  // векторное
        return x * other.y - y * other.x;
    }
    pt operator* (ld d) const {
        return pt(x * d, y * d);
    }

    bool operator== (const pt& other) const {
        return eq(x, other.x) && eq(y, other.y);
    }

    bool operator< (const pt& other) const {
        return sml(x, other.x) || sml(y, other.y);
    }
};

//#define ve pt;
using ve = pt;

istream& operator>> (istream& in, pt& x) {
    in >> x.x >> x.y;
    return in;
}

ostream& operator<< (ostream& out, pt& x) {
    out << x.x << ' ' << x.y;
    return out;
}

ld angle (pt& a, pt& b) {
    return atan2(a % b, a ^ b);
}

bool is_pt_on_seg(const pt & a, const pt & b, const pt & p) {
    if (a == b) {
        return a == p;
    }
    ve ab(a, b), ap(a, p), ba(b, a), bp(b, p);
    if (sgn(ab % ap) != 0) {
        return false;
    }
    if (sgn(ap ^ ab) >= 0 && sgn(ba ^ bp) >= 0) {
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct line {
    ld a = 0;
    ld b = 0;
    ld c = 0;
    line() = default;
    line(ld a, ld b, ld c): a(a), b(b), c(c) {}
    line(pt p1, pt p2): a(p1.y - p2.y), b(p2.x - p1.x), c(-1 * p1.x * a - b * p1.y) {
        normalize();
    }

    void normalize() {
        ld n = sqrt(a * a + b * b);
        assert(sgn(n) == 1);
        a /= n;
        b /= n;
        c /= n;
    }

    bool operator == (const line & other) const {
        return eq(a * other.b, b * other.a) && eq(a * other.c, other.a * c) && eq(b * other.c, c * other.b);
    }
};

bool are_parallel(line f1, line f2) {
    return sgn(f1.a * f2.b - f1.b * f2.a) == 0;
}

pr<int, pt> are_intersect(line f1, line f2) {
    if (are_parallel(f1, f2)) {
        if (f1 == f2) return {2, pt()};
        return {0, pt()};
    }
    ld d = f2.a * f1.b - f1.a * f2.b;
    ld x = f2.b * f1.c - f2.c * f1.b;
    ld y = f2.c * f1.a - f1.c * f2.a;
    return {1, pt(x / d, y / d)};
}


ld pt_to_line(const line& f, const pt& p) {
    return abs(f.a * p.x + f.b * p.y + f.c) / sqrt(f.a * f.a + f.b * f.b);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pt symmetrical_pt(const line& f, const pt& p) { // проверить
    ld d = 2 * (f.a * p.x + f.b * p.y + f.c) / (f.a * f.a + f.b * f.b);
    ld x = p.x - d * f.a;
    ld y = p.y - d * f.b;
    return pt(x, y);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ld pt_to_line();

ld pt_to_seg();

ld pt_to_ray();

ld seg_to_seg();

ld seg_to_ray();

ld seg_to_line();

ld ray_to_ray();

ld ray_to_line();

ld line_to_line();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool are_segs_intersect(const pt & a, const pt & b, const pt & c, const pt & d) {
    ve ab(a, b), ac(a, c), ad(a, d);
    ve db(d, b), da(d, a), dc(d, c);
    if (is_pt_on_seg(a, b, c) ||
        is_pt_on_seg(a, b, d) ||
        is_pt_on_seg(c, d, a) ||
        is_pt_on_seg(c, d, b)) {
        return true;
    }
    if (sgn(ab % ac) == sgn(ab % ad) || sgn(dc % da) == sgn(dc % db)) {
        return false;
    } else {
        return true;
    }
}

ld pt_to_line(const line & f, const pt & p) {
    return abs(f.a * p.x + f.b * p.y + f.c) / sqrt(f.a * f.a + f.b * f.b);
}

ld pt_to_seg(const pt & a, const pt & b, const pt & p) {
    if (a == b) return (a - p).len();
    if (is_pt_on_seg(a, b, p)) {
        return 0;
    }
    ve ab(a, b), ap(a, p), ba(b, a), bp(b, p);
    if (sgn(ab ^ ap) >= 0 && sgn(ba ^ bp) >= 0) {
        line f(a, b);
        return pt_to_line(f, p);
    } else {
        return min((a - p).len(), (b - p).len());
    }
}

ld pt_to_ray(const pt & a, const pt & b, const pt & p) {
    ve ab(a, b), ap(a, p);
    if (sgn(ab ^ ap) >= 0) {
        line f(a, b);
        return pt_to_line(f, p);
    } else {
        return (a - p).len();
    }
}

ld seg_to_seg(const pt & a, const pt & b, const pt & c, const pt & d) {
    if (are_segs_intersect(a, b, c, d)) {
        return 0;
    } else {
        return min(min(pt_to_seg(a, b, c), pt_to_seg(a, b, d)), min(pt_to_seg(c, d, a), pt_to_seg(c, d, b)));
    }
}

ld seg_to_ray(const pt & a, const pt & b, const pt & c, const pt & d) {
    line f1(a, b), f2(c, d);
    auto tmp = are_intersect(f1, f2);
    if (tmp.first == 1) {
        if (eq(pt_to_seg(a, b, tmp.second), 0) && eq(pt_to_ray(c, d, tmp.second), 0)) {
            return 0;
        } else {
            return min(min(pt_to_ray(c, d, a), pt_to_ray(c, d, b)), pt_to_seg(a, b, c));
        }
    } else {
        return min(min(pt_to_ray(c, d, a), pt_to_ray(c, d, b)), pt_to_seg(a, b, c));
    }
}

ld seg_to_line(const pt & a, const pt & b, const line & f) {
    line f1(a, b);
    auto tmp = are_intersect(f, f1);
    if (tmp.first == 1) {
        if (is_pt_on_seg(a, b, tmp.second)) {
            return 0;
        } else {
            return min(pt_to_line(f, a), pt_to_line(f, b));
        }
    } else if (tmp.first == 0) {
        return min(pt_to_line(f, a), pt_to_line(f, b));
    } else {
        return 0;
    }
}

ld ray_to_ray(const pt& a, const pt& b, const pt& c, const pt& d) {
    line f1(a, b), f2(c, d);
    auto tmp = are_intersect(f1, f2);
    if (tmp.first == 1) {
        if (eq(pt_to_ray(a, b, tmp.second), 0) && eq(pt_to_ray(c, d, tmp.second), 0)) {
            return 0;
        } else {
            return min(min(min(pt_to_ray(c, d, a), pt_to_ray(c, d, b)), pt_to_ray(a, b, c)), pt_to_ray(a, b, d));
        }
    } else {
        return min(min(min(pt_to_ray(c, d, a), pt_to_ray(c, d, b)), pt_to_ray(a, b, c)), pt_to_ray(a, b, d));
    }
}

ld ray_to_line(const line & f, const pt & a, const pt & b) {
    line f1(a, b);
    auto tmp = are_intersect(f, f1);
    if (tmp.first == 1) {
        if (eq(pt_to_ray(a, b, tmp.second), 0)) {
            return 0;
        } else {
            return pt_to_line(f, a);
        }
    } else if (tmp.first == 2) {
        return 0;
    } else {
        return pt_to_line(f, a);
    }
}

ld line_to_line(const line & f1, const pt & a, const pt & b) {
    line f2(a, b);
    auto tmp = are_intersect(f1, f2);
    if (tmp.first == 1) {
        return 0;
    } else if (tmp.first == 2) {
        return 0;
    } else {
        return pt_to_line(f1, a);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool is_pt_in_angle(const pt& aa, const pt& oa, const pt& ba, const pt& pa) {
    pt a = aa - oa;
    pt b = ba - oa;
    pt p = pa - oa;
    if (sml(angle(a, b), 0)) swap(a, b);
    if (grteq(a % p, 0) && grteq(0, b % p)) return true;
    else return false;
}

vector<pt> graham(vector<pt>& pts) {
    auto it = min_element(all(pts), [ & ](const pt&i, const pt& j) {
        return tie(i.y, i.x) < tie(j.y, j.x);
    });
    swap(*it, pts.front());
    pt s = pts[0];
    sort(all(pts), [ & ](ve i, ve j){
        if ((i - s) % (j - s) == 0) return (i - s).lenlen() < (j - s).lenlen();
        return ((i - s) % (j - s)) > 0;
    });
    vector<pt> res;
    int sz = 0;
    for (auto p : pts) {
        while (sz > 1) {
            if ((res[sz - 1] - res[sz - 2]) % (p - res[sz - 1]) <= 0) {
                sz--;
                res.pop_back();
            } else break;
        }
        sz++;
        res.push_back(p);
    }
    return res;
}

vector<pt> jarvis(vector<pt>& pts) {
    int s = 0;
    for (int i = 0; i < (int)pts.size(); i++) {
        if (pts[i].x == pts[s].x) {
            if (pts[i].y < pts[s].y) s = i;
        } else if (pts[i].x < pts[s].x) s = i;
    }
    vector<pt> res;
    res.push_back(pts[s]);
    int now = s;
    vector<int>used(pts.size());
    used[s] = 1;
    while (true) {
        int next = -1;
        for (int i = 0; i < (int)pts.size(); i++) {
            if (!used[i] || ((i == s && now != s))) {
                if (next == -1) { next = i; }
                else {
                    ve v1 = pts[i] - pts[now];
                    ve v2 = pts[next] - pts[now];
                    if (v1 % v2 == 0) {
                        if (v1.lenlen() < v2.lenlen()) { next = i; }
                    } else if (v1 % v2 > 0) { next = i; }
                }
            }
        }
        if(next == -1) break;
        now = next;
        used[next] = 1;
        if (now == s) {
            break;
        } else {
            res.push_back(pts[now]);
        }
    }
    return res;
}