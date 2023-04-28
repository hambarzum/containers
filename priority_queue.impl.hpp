#ifndef PRIORITY_QUEUE_IMPL_HPP
#define PRIORITY_QUEUE_IMPL_HPP

#include "priority_queue.hpp"

// #include <algorithm> 
#include <stdexcept> // std::underflow_error
#include <iterator> // std::distance, std::iterator_traits

namespace pq {

// constructors -----------------------------
template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare& compare, const Container& cont) 
    : c_{cont}, comp_{compare}, size_{c_.size()}
{ 
    makeHeap(std::begin(c_), std::end(c_), comp_);
} 

template <typename T, typename Container, typename Compare>
template <typename InputIt>
PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare)
    : c_{first, last}, comp_{compare}, size_{c_.size()}
{
    makeHeap(std::begin(c_), std::end(c_), comp_);
}

template <typename T, typename Container, typename Compare>
template <typename InputIt>
PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare, const Container& cont)
    : c_{first, last}, comp_{compare}
{
    c_.insert(std::end(c_), std::begin(cont), std::end(cont));
    makeHeap(std::begin(c_), std::end(c_), comp_);
    size_ = c_.size();
} // what's the semantics of this??

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(const PriorityQueue<T, Container, Compare>& other) 
    : size_{other.size_}
    , comp_{other.comp_}
    , c_{other.c_}
{

}

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>& PriorityQueue<T, Container, Compare>::operator=(const PriorityQueue<T, Container, Compare>& other) {
    if(this == &other) {
        return *this;
    }
    c_ = other.c_;
    size_ = other.size_;
    comp_ = other.comp_;

    return *this;
} // any exceptions expected??

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::~PriorityQueue() {
// anything??
}

// member functions ----------------------------
template <typename T, typename Container, typename Compare>
typename PriorityQueue<T, Container, Compare>::const_reference PriorityQueue<T, Container, Compare>::top() const {
    return c_[0];
}

template <typename T, typename Container, typename Compare>
[[nodiscard]] bool PriorityQueue<T, Container, Compare>::empty() const {
    return size_ == 0;
}

template <typename T, typename Container, typename Compare>
typename PriorityQueue<T, Container, Compare>::size_type PriorityQueue<T, Container, Compare>::size() const {
    return size_;
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::push(const typename PriorityQueue<T, Container, Compare>::value_type& value) {
    c_.push_back(value);
    ++size_;
    increaseKey(std::begin(c_), std::next(std::begin(c_), size_ - 1));
}

template <typename T, typename Container, typename Compare>
template <typename RandomIt>
void PriorityQueue<T, Container, Compare>::increaseKey(RandomIt first, RandomIt target) {
    while(std::distance(first, target) > 0 && comp_(*getParent(first, target), *target)) {
        std::swap(*getParent(first, target), *target);
        target = getParent(first, target);
    }
}

template <typename T, typename Container, typename Compare>
template <typename RandomIt>
RandomIt PriorityQueue<T, Container, Compare>::getParent(RandomIt first, RandomIt child) {
    auto childIndex = std::distance(first, child);
    auto parentIdx = (childIndex - 1) / 2; // out of bounds checking??
    return std::next(first, parentIdx);
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::pop() {
    if(c_.empty()) {
        throw std::underflow_error("[underflow] : priority_queue is already empty");
    }
    c_[0] = c_[size_ - 1];
    c_.pop_back();
    --size_;
    heapify(std::begin(c_), std::end(c_), std::begin(c_), comp_);
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::swap(PriorityQueue<T, Container, Compare>& other) noexcept {
    std::swap(c_, other.c_);
    std::swap(comp_, other.comp_); // maybe unnecessary?? doesnt let swap with different comparators anyway
    std::swap(size_, other.size_);
} // anything else for noexcept??

template <typename T, typename Container, typename Compare>
template <typename RandomIt>
void PriorityQueue<T, Container, Compare>::makeHeap(RandomIt first, RandomIt last) {
    makeHeap(first, last, Compare());
}

template <typename T, typename Container, typename Compare>
template <typename RandomIt>
void PriorityQueue<T, Container, Compare>::makeHeap(RandomIt first, RandomIt last, const Compare& comp) {
    const auto size = std::distance(first, last);
    const auto firstNonLeaf = size / 2 - 1;

    for (auto i = firstNonLeaf + 1; i >= 1; --i) {
        heapify(first, last, std::next(first, i - 1), comp);
    }
}

template <typename T, typename Container, typename Compare>
template <typename RandomIt>
void PriorityQueue<T, Container, Compare>::heapify(RandomIt first, RandomIt last, RandomIt target, const Compare& comp) {
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

template <typename T, typename Container, typename Compare>
template <typename RandomIt>
RandomIt PriorityQueue<T, Container, Compare>::getLeftChild(RandomIt first, RandomIt last, RandomIt parent) {
    return getChild(first, last, parent, 1);
}

template <typename T, typename Container, typename Compare>
template <typename RandomIt>
RandomIt PriorityQueue<T, Container, Compare>::getRightChild(RandomIt first, RandomIt last, RandomIt parent) {
    return getChild(first, last, parent, 2);
}

template <typename T, typename Container, typename Compare>
template <typename RandomIt>
RandomIt PriorityQueue<T, Container, Compare>::getChild(RandomIt first, RandomIt last, RandomIt parent, typename std::iterator_traits<RandomIt>::difference_type childId) {
    const auto parentIndex = std::distance(first, parent);
    const auto childIndex = 2 * parentIndex + childId;
    return childIndex >= std::distance(first, last) ? last : std::next(first, childIndex);
}

/* template <typename T, typename Container, typename Compare>
size_t PriorityQueue<T, Container, Compare>::parent(size_t index) {
    return (index - 1) / 2;
} */



} // namespace pq


#endif // PRIORITY_QUEUE_IMPL_HPP