#ifndef UTILS_HEAP_IMPL_HPP
#define UTILS_HEAP_IMPL_HPP

#include "heap.hpp"

namespace heap {

template <typename RandomIt>
void increaseKey(RandomIt first, RandomIt target) {
    while(std::distance(first, target) > 0 && comp_(*getParent(first, target), *target)) {
        std::swap(*getParent(first, target), *target);
        target = getParent(first, target);
    }
}

template <typename RandomIt>
void makeHeap(RandomIt first, RandomIt last) {
    makeHeap(first, last, Compare());
}

template <typename RandomIt, typename Compare>
void makeHeap(RandomIt first, RandomIt last, const Compare& comp) {
    const auto size = std::distance(first, last);
    const auto firstNonLeaf = size / 2 - 1;

    for (auto i = firstNonLeaf + 1; i >= 1; --i) {
        heapify(first, last, std::next(first, i - 1), comp);
    }
}


template <typename RandomIt, typename Compare>
void heapify(RandomIt first, RandomIt last, RandomIt target, const Compare& comp) {
    auto largest = target;
    if(const auto l = getLeftChild(first, last, target); l != last &&  comp(*largest, *l)) {
        largest = l;
    }
    if (const auto r = getRightChild(first, last, target); r != last && comp(*largest, *r)) {
        largest = r;
    }
    if (largest != target) {
        std::swap(*largest, *target);
        heapify(first, last, largest, comp);
    }
}

template <typename RandomIt>
RandomIt getLeftChild(RandomIt first, RandomIt last, RandomIt parent) {
    return getChild(first, last, parent, 1);
}

template <typename RandomIt>
RandomIt getRightChild(RandomIt first, RandomIt last, RandomIt parent) {
    return getChild(first, last, parent, 2);
}

template <typename RandomIt>
RandomIt getChild(RandomIt first, RandomIt last, RandomIt parent, typename std::iterator_traits<RandomIt>::difference_type childId) {
    const auto parentIndex = std::distance(first, parent);
    const auto childIndex = 2 * parentIndex + childId;
    return childIndex >= std::distance(first, last) ? last : std::next(first, childIndex);
}

template <typename RandomIt>
RandomIt getParent(RandomIt first, RandomIt child) {
    auto childIndex = std::distance(first, child);
    auto parentIdx = (childIndex - 1) / 2; // out of bounds checking??
    return std::next(first, parentIdx);
}

} // namespace heap

#endif // UTILS_HEAP_IMPL_HPP