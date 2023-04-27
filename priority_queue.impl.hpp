#ifndef PRIORITY_QUEUE_IMPL_HPP
#define PRIORITY_QUEUE_IMPL_HPP

#include "priority_queue.hpp"

#include <algorithm> // std::make_heap 
#include <iterator> // std::distance, std::make_reverse_iterator, std::iterator_traits

namespace pq {

// constructors -----------------------------
template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare& compare, const Container& cont) 
    : c_{cont}, comp_{compare}
{ 
    std::make_heap(std::begin(c_), std::end(c_), comp_); /// TODO: implement make_heap
} 

template <typename T, typename Container, typename Compare>
template <typename InputIt>
PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare)
    : c_{first, last}, comp_{compare}
{
    makeHeap(std::begin(c_), std::end(c_), comp_);
}

template <typename T, typename Container, typename Compare>
template <typename InputIt>
PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare, const Container& cont)
    : c_{first, last}, comp_{compare}
{
    c_.insert(std::end(c_), std::begin(cont), std::end(cont));
    std::make_heap(std::begin(c_), std::end(c_), comp_);
} // what's the semantics of this??

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::~PriorityQueue() {

}

// member functions ----------------------------
template <typename T, typename Container, typename Compare>
typename PriorityQueue<T, Container, Compare>::const_reference PriorityQueue<T, Container, Compare>::top() const {
    return c_[0];
}

template <typename T, typename Container, typename Compare>
[[nodiscard]] bool PriorityQueue<T, Container, Compare>::empty() const {
    return c_.empty();
}

template <typename T, typename Container, typename Compare>
typename PriorityQueue<T, Container, Compare>::size_type PriorityQueue<T, Container, Compare>::size() const {
    return c_.size();
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::push(const typename PriorityQueue<T, Container, Compare>::value_type& value) {
    c_.push_back(value);
    std::push_heap(c_.begin(), c_.end()); /// TODO: implement push_heap
}

template <typename T, typename Container, typename Compare>
template <typename RandomIt>
void PriorityQueue<T, Container, Compare>::makeHeap(RandomIt first, RandomIt last) {
    makeHeap(first, last, Compare());
}

template <typename T, typename Container, typename Compare>
template <typename RandomIt>
void PriorityQueue<T, Container, Compare>::makeHeap(RandomIt first, RandomIt last, Compare comp) { // maybe const Compare& comp??
    const auto size = std::distance(first, last);
    const auto firstNonLeaf = size / 2 - 1;

    for (auto i = firstNonLeaf + 1; i >= 1; --i) {
        heapify(first, last, std::next(first, i), comp); // maybe i-1??
    }
}

template <typename T, typename Container, typename Compare>
template <typename RandomIt>
void PriorityQueue<T, Container, Compare>::heapify(RandomIt first, RandomIt last, RandomIt target, Compare comp) { // maybe const Compare& comp??
    auto largest = target;
    if(const auto l = getLeftChild(first, last, target); l != last &&  *l > *largest) {
        largest = l;
    }
    if (const auto r = getRightChild(first, last, target); r != last && *r > *largest) {
        largest = r;
    }
    if (largest != target) {
        std::swap(*largest, *target);
        heapify(first, last, largest, comp);
    }
}

template <typename T, typename Container, typename Compare>
template <typename RandIt>
RandIt PriorityQueue<T, Container, Compare>::getLeftChild(RandIt first, RandIt last, RandIt parent) {
    return getChild(first, last, parent, 1);
}

template <typename T, typename Container, typename Compare>
template <typename RandIt>
RandIt PriorityQueue<T, Container, Compare>::getRightChild(RandIt first, RandIt last, RandIt parent) {
    return getChild(first, last, parent, 1);
}

template <typename T, typename Container, typename Compare>
template <typename RandIt>
RandIt PriorityQueue<T, Container, Compare>::getChild(RandIt first, RandIt last, RandIt parent, typename std::iterator_traits<RandIt>::difference_type childId) {
    const auto index = std::distance(first, parent);
    const auto childIndex = 2 * index + childId;
    return childIndex >= std::distance(first, last) ? last : std::next(first, childIndex);
}

/* template <typename T, typename Container, typename Compare>
size_t PriorityQueue<T, Container, Compare>::parent(size_t index) {
    return (index - 1) / 2;
} */



} // namespace pq


#endif // PRIORITY_QUEUE_IMPL_HPP