#ifndef PRIORITY_QUEUE_IMPL_HPP
#define PRIORITY_QUEUE_IMPL_HPP

#include "priority_queue.hpp"

#include <algorithm> // std::make_heap 
#include <iterator> // std::distance, std::make_reverse_iterator

template <typename T, typename Container, typename Compare>
pq::PriorityQueue<T, Container, Compare>::PriorityQueue(const Compare& compare, const Container& cont) 
    : c_{cont}, comp_{compare}
{ 
    std::make_heap(std::begin(c_), std::end(c_), comp_); 
} 

template <typename T, typename Container, typename Compare>
template <typename InputIt>
pq::PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare = Compare())
    : c_{first, last}, comp_{compare}
{
    std::make_heap(std::begin(c_), std::end(c_), comp_);
}

template <typename T, typename Container, typename Compare>
template <typename InputIt>
pq::PriorityQueue<T, Container, Compare>::PriorityQueue(InputIt first, InputIt last, const Compare& compare, const Container& cont)
    : c_{first, last}, comp_{compare}
{
    c_.insert(std::end(c_), std::begin(cont), std::end(cont));
    std::make_heap(std::begin(c_), std::end(c_), comp_);
} // what's the semantics of this??

template <typename T, typename Container, typename Compare>
pq::PriorityQueue<T, Container, Compare>::const_reference pq::PriorityQueue<T, Container, Compare>::top() const {
    return c_[0];
}

template <typename T, typename Container, typename Compare>
bool pq::PriorityQueue<T, Container, Compare>::empty() const {
    return c_.empty();
}

template <typename T, typename Container, typename Compare>
[[nodiscard]] bool pq::PriorityQueue<T, Container, Compare>::empty() const {
    return c_.empty();
}

template <typename T, typename Container, typename Compare>
pq::PriorityQueue<T, Container, Compare>::size_type pq::PriorityQueue<T, Container, Compare>::size() const {
    return c_.size();
}

template <typename T, typename Container, typename Compare>
void pq::PriorityQueue<T, Container, Compare>::push(const pq::PriorityQueue<T, Container, Compare>::value_type& value) {

}

template <typename RandomIt>
void pq::make_heap(RandomIt first, RandomIt last) {
    using namespace std;

    auto size = distance(first, last);
    RandomIt midIter = next(first, size / 2); 
    RandomIt revMidIter = prev(make_reverse_iter(midIter));
    RandomIt revFirstIter = make_reverse_iterator(first);
    for(; revMidIter != revFirstIter; ++revMidIter) {
        pq::heapify();
    }
}

// [0 1 2 3 4 5 6 7 8]
#endif // PRIORITY_QUEUE_IMPL_HPP
