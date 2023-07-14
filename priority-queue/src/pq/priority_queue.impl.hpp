#ifndef PRIORITY_QUEUE_PRIORITY_QUEUE_IMPL_HPP
#define PRIORITY_QUEUE_PRIORITY_QUEUE_IMPL_HPP

#include "../heap/heap.hpp"
#include "priority_queue.hpp"

#include <iterator> // std::distance, std::iterator_traits
#include <stdexcept> // std::underflow_error


// constructors -----------------------------
template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare& compare, const Container& cont) 
    : c_{cont}, comp_{compare}, size_{c_.size()}
{ 
    heap::makeHeap(std::begin(c_), std::end(c_), comp_);
} 

template <typename T, typename Container, typename Compare>
template <typename InputIt>
PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare)
    : c_{first, last}, comp_{compare}, size_{c_.size()}
{
    heap::makeHeap(std::begin(c_), std::end(c_), comp_);
}

template <typename T, typename Container, typename Compare>
template <typename InputIt>
PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare, const Container& cont)
    : c_{cont}, comp_{compare}
{
    c_.insert(c_.end(), first, last);
    heap::makeHeap(std::begin(c_), std::end(c_), comp_);
    size_ = c_.size();
}

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(const PriorityQueue<T, Container, Compare>& other) 
    : size_{other.size_}
    , comp_{other.comp_}
    , c_{other.c_}
{

}

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>& PriorityQueue<T, Container, Compare>::operator=(PriorityQueue<T, Container, Compare> other) {
    swap(other);
    return *this;
}

template <typename T, typename Container, typename Compare>
PriorityQueue<T, Container, Compare>::PriorityQueue(PriorityQueue<T, Container, Compare>&& other) 
    : size_{other.size_}
    , c_{std::move(other.c_)}
    , comp_{std::move(other.comp_)}
{

}

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
    return size_ == 0;
}

template <typename T, typename Container, typename Compare>
typename PriorityQueue<T, Container, Compare>::size_type PriorityQueue<T, Container, Compare>::size() const {
    return size_;
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::push(const typename PriorityQueue<T, Container, Compare>::value_type& value) {
    c_.push_back(value);
    heap::increaseKey(std::begin(c_), std::next(std::begin(c_), size_ - 1), comp_);
    ++size_;
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::pop() {
    if(c_.empty()) {
        throw std::underflow_error("[PriorityQueue] : priority_queue is already empty");
    }
    c_[0] = c_[size_ - 1];
    c_.pop_back();
    heap::heapify(std::begin(c_), std::end(c_), std::begin(c_), comp_);
    --size_;
}

template <typename T, typename Container, typename Compare>
void PriorityQueue<T, Container, Compare>::swap(PriorityQueue<T, Container, Compare>& other) noexcept {
    using std::swap;
    swap(c_, other.c_);
    swap(comp_, other.comp_);
    swap(size_, other.size_);
}

// non-member functions--------------
template <typename T, typename Container = std::vector<T>, typename Compare>
void swap(PriorityQueue<T, Container, Compare>& lhs, PriorityQueue<T, Container, Compare>& rhs) {
    lhs.swap(rhs);
}

#endif // PRIORITY_QUEUE_PRIORITY_QUEUE_IMPL_HPP