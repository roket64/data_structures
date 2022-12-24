#ifndef DATA_STRUCTURES_SEGMENT_TREE_H
#define DATA_STRUCTURES_SEGMENT_TREE_H

#include <vector>
#include <functional>

template<class NodeType = long long, class Functor = std::plus<>>
class SegmentTree {
public:
    SegmentTree(int sz, const NodeType &e)
            : sz_(1 << Log2(sz)), e_(e) {
        tree_.assign(sz_ << 1, e_);
    }

    void set(int pos, const NodeType &val) {
        tree_[--pos | sz_] = val;
    }

    void build() {
        for (int i = sz_ - 1; i; --i) {
            tree_[i] = functor_(tree_[i << 1], tree_[i << 1 | 1]);
        }
    }

    void update(int pos, const NodeType &val) {
        tree_[--pos |= sz_] = val;
        while (pos >>= 1) {
            tree_[pos] = functor_(tree_[pos << 1], tree_[pos << 1 | 1]);
        }
    }

    NodeType get(int pos) const {
        return tree_[--pos | sz_];
    }

    NodeType get(int l, int r) const {
        NodeType lhs = e_;
        NodeType rhs = e_;
        for (--l |= sz_, --r |= sz_; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) lhs = functor_(lhs, tree_[l++]);
            if (~r & 1) rhs = functor_(tree_[r--], rhs);
        }
        return functor_(lhs, rhs);
    }

private:
    static int Log2(unsigned int n) {
        int ret = 0;
        while (n > 1 << ret) ret++;
        return ret;
    }

    std::vector<NodeType> tree_;
    const size_t sz_;
    const NodeType e_;
    Functor functor_;
};

#endif //DATA_STRUCTURES_SEGMENT_TREE_H
