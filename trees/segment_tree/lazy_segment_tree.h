#ifndef DATA_STRUCTURES_LAZY_SEGMENT_TREE_H
#define DATA_STRUCTURES_LAZY_SEGMENT_TREE_H

#include <vector>
#include <functional>

template<class NodeType = long long,
        class LazyType = long long,
        class Functor = std::plus<>,
        class UpdateFunctor = std::plus<>,
        class LazyFunctor = std::plus<>>
class LazySegmentTree {
    typedef NodeType T;
    typedef LazyType L;
public:
    LazySegmentTree(std::vector<T> &a, T e, L id)
            : sz_(a.size()), e_(e), id_(id) {
        tree_.assign(4 * sz_, e_);
        lazy_.assign(4 * sz_, id_);
        build(a, 1, 0, sz_ - 1);
    }

    /* not sure this is valid operation
    T update(int pos, T val) {
        return update(1, 0, sz_ - 1, --pos, val);
    }
    /**/

    T update(int l, int r, T diff) {
        return update(1, 0, sz_ - 1, --l, --r, diff);
    }

    T get(int l, int r) {
        return get(1, 0, sz_ - 1, --l, --r);
    }

private:
    T build(std::vector<T> &a, int n, int s, int e) {
        if (s == e) return tree_[n] = a[s];
    }

    void propagate(int n, int s, int e) {
        if (lazy_[n] == 0) return;
        tree_[n] += (e - s + 1) * lazy_[n];
        if (s != e) {
            lazy_[n << 1] += lazy_[n];
            lazy_[n << 1 | 1] += lazy_[n];
        }
        lazy_[n] = 0;
    }

    /* implementation of function update(pos, val);
    T update(int n, int s, int e, int pos, T val) {
        if (pos < s || e < pos) return tree_[n];
        if (s == e) return tree_[n] = val;

        int mid = (s + e) >> 1;
        T lhs = update((n << 1), s, mid, pos, val);
        T rhs = update(n << 1 | 1, mid + 1, e, pos, val);

        return tree_[n] = functor_(lhs, rhs);
    }
    /**/

    T update(int n, int s, int e, int l, int r, T diff) {
        propagate(n, s, e);

        if (r < s || e < l) return tree_[n];
        if (l <= s && e <= r) {
            tree_[n] += (e - s + 1) * diff;
            if (s != e) {
                lazy_[n << 1] += diff;
                lazy_[n << 1 | 1] += diff;
            }
            return tree_[n];
        }

        int mid = (s + e) >> 1;
        T lhs = update(n << 1, s, mid, l, r, diff);
        T rhs = update(n << 1 | 1, mid + 1, e, l, r, diff);

        return tree_[n] = functor_(lhs, rhs);
    }

    T get(int n, int s, int e, int l, int r) {
        propagate(n, s, e);

        if (r < s || e < l) return e_;
        if (l <= s && e <= r) return tree_[n];

        int mid = (s + e) >> 1;
        T lhs = get(n << 1, s, mid, l, r);
        T rhs = get(n << 1 | 1, mid + 1, e, l, r);

        return functor_(lhs, rhs);
    }

    Functor functor_;
    const size_t sz_;
    const T e_;
    const L id_;
    std::vector<T> tree_;
    std::vector<T> lazy_;
};

#endif //DATA_STRUCTURES_LAZY_SEGMENT_TREE_H
