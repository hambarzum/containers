#ifndef PRIORITY_QUEUE_PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_PRIORITY_QUEUE_HPP

#include <functional> // std::less
#include <vector>


template <typename T, typename Container = std::vector<T>, 
                    typename Compare = std::greater<typename Container::value_type>>
class PriorityQueue {
public: // associated types
    using container_type = Container;
    using value_compare = Compare;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

public: // ctors, dtor
    PriorityQueue() : PriorityQueue(Compare(), Container()) {}
    explicit PriorityQueue(const Compare& compare) : PriorityQueue(compare, Container()) {}
    PriorityQueue(const Compare& compare, const Container& cont);

    template <typename InputIt>
    PriorityQueue(InputIt first, InputIt last, const Compare& compare = Compare());	
    template <typename InputIt>
    PriorityQueue(InputIt first, InputIt last, const Compare& compare, const Container& cont);

    PriorityQueue(const PriorityQueue& other);
    PriorityQueue& operator=(PriorityQueue other); // copy-and-swap idiom
    // move operator= omitted due to the operator= implemented via copy-and-swap
    PriorityQueue(PriorityQueue&& other);
    
    ~PriorityQueue();

public: // member functions
    const_reference top() const;
    [[nodiscard]] bool empty() const;
    size_type size() const;
    void push(const value_type& value);
    /// TODO: implement emplace() with variadic templates
    void pop();
    void swap(PriorityQueue& other) noexcept;

private:
    Container c_;
    Compare comp_;
    size_type size_;
}; // class PriorityQueue

namespace std {
    template <typename T, typename Container = std::vector<T>, 
                    typename Compare = std::greater<typename Container::value_type>>
    void swap(PriorityQueue<T, Container, Compare>& lhs, PriorityQueue<T, Container, Compare>& rhs) noexcept;
}; // namespace std


#include "priority_queue.impl.hpp"

#endif // PRIORITY_QUEUE_PRIORITY_QUEUE_HPP