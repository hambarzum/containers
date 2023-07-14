#ifndef UTILS_HEAP_HPP
#define UTILS_HEAP_HPP

#include <iterator> // std::iterator_traits

namespace heap {

template <typename RandomIt, typename Compare>
void increaseKey(RandomIt first, RandomIt target, const Compare& comp);

template <typename RandomIt, typename Compare>
void makeHeap(RandomIt first, RandomIt last, const Compare& comp);

template <typename RandomIt, typename Compare>
void heapify(RandomIt first, RandomIt last, RandomIt target, const Compare& comp);

template <typename RandomIt>
RandomIt getChild(RandomIt first, RandomIt last, RandomIt parent, typename std::iterator_traits<RandomIt>::difference_type childId);

template <typename RandomIt>
RandomIt getLeftChild(RandomIt first, RandomIt last, RandomIt parent);

template <typename RandomIt>
RandomIt getRightChild(RandomIt first, RandomIt last, RandomIt parent);

template <typename RandomIt>
RandomIt getParent(RandomIt first, RandomIt child);
} // namespace heap

#include "heap.impl.hpp"

#endif // UTILS_HEAP_HPP