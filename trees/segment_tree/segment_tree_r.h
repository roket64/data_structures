#ifndef DATA_STRUCTURES_SEGMENT_TREE_R_H
#define DATA_STRUCTURES_SEGMENT_TREE_R_H

#include <vector>

template<class NodeType, class Functor>
class RecursiveSegTree {
    typedef NodeType T;
public:
    RecursiveSegTree(std::vector <T> &a, T e)
            : sz_(a.size()), e_(e) {
        tree_.assign(4 * sz_, e_);
        build(a, 1, e_, sz_ - 1);
    }

    T update(int pos, T val) {
        return update(1, 0, sz_ - 1, --pos, val);
    }

    T get(int l, int r) {
        return get(1, 0, sz_ - 1, --l, --r);
    }

private:
    T build(std::vector <T> &a, int n, int s, int e) {
        if (s == e) return tree_[n] = a[s];
        int mid = (s + e) >> 1;

        T lhs = build(a, (n << 1), s, mid);
        T rhs = build(a, n << 1 | 1, mid + 1, e);

        return tree_[n] = functor_(lhs, rhs);
    }

    T get(int n, int s, int e, int l, int r) {
        if (r < s || e < l) return e_;
        if (l <= s && e <= r) return tree_[n];

        int mid = (s + e) >> 1;
        T lhs = get((n << 1), s, mid, l, r);
        T rhs = get(n << 1 | 1, mid + 1, e, l, r);

        return functor_(lhs, rhs);
    }

    T update(int n, int s, int e, int pos, T val) {
        if (pos < s || e < pos) return tree_[n];
        if (s == e) return tree_[n] = val;

        int mid = (s + e) >> 1;
        T lhs = update((n << 1), s, mid, pos, val);
        T rhs = update(n << 1 | 1, mid + 1, e, pos, val);

        return tree_[n] = functor_(lhs, rhs);
    }

    Functor functor_;
    const size_t sz_;
    const NodeType e_;
    std::vector<T> tree_;
};

#endif //DATA_STRUCTURES_SEGMENT_TREE_R_H
