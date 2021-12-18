#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> map_to_vector(unordered_map<int, int>& m) {
    vector<pair<int, int>> v;

    v.reserve(m.size());

    for (auto p : m) {
        v.push_back(p);
    }

    return v;
}

unordered_map<int, int> vector_to_map(vector<pair<int, int>>& v) {
    unordered_map<int, int> m;

    m.reserve(v.size());

    for (auto p : v) {
        m.insert(p);
    }

    return m;
}

int main() {
    unordered_map<int, int> m;
    vector<pair<int, int>> v;

    for (int i = 0; i < 10000; i++) {
        auto p = make_pair(i, i);
        v.push_back(p);
        m.insert(p);
    }

    vector<pair<int, int>> mv = map_to_vector(m);
    sort(mv.begin(), mv.end(), [](auto l, auto r) {
        return l.first < r.first;
    });

    assert(v == mv);

    unordered_map<int, int> vm = vector_to_map(v);

    for (auto p : m) {
        assert(vm.find(p.first) != vm.end());
    }

    /*
    for a sufficiently large dataset, converting from m->v->m->v will have a faster runtime than
    v->m->v->m. This is because map insertions are an *ammortized* O(1) provided there are sufficient
    buckets. For a very large dataset, the map insertion will have a slower runtime than a true O(1) insertion for a vector
    with pre-allocated space. Since there are 2 map insertions in v->m->v->m and only 1 in m->v->m->v, m->v->m->v will have
    a faster runtime.
    */
}