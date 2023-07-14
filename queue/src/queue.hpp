#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <deque>

template <typename T, typename Container = std::deque<T>>
class Queue {
public: // associated types
    using container_type = Container;
    using value_type  = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

public: // ctors, dtor
    Queue() : Queue(Container()) {}
    explicit Queue(const Container& cont);
    explicit Queue(Container&& cont);
    Queue(const Queue& other);
    Queue& operator=(Queue rhs); // copy-and-swap idiom
    // move operator= omitted due to the operator= implemented via copy-and-swap
    Queue(Queue&& other);

    template <typename InputIt>
    Queue(InputIt first, InputIt last);

    ~Queue() {}

public: // member functions
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    bool empty() const;
    size_type size() const;
    void push(const value_type& elem); 
    void push(value_type&& elem);
    /// TODO: implement emplace() using variadic templates
    void pop();
    void swap(Queue& other) noexcept;

private:
    Container c_;
}; // class Queue

namespace std {
    template <typename T, typename Container>
    void swap(Queue<T, Container>& lhs, Queue<T, Container>& rhs) noexcept;
}; // namespace std

/// TODO: research and implement non-member comparison functions for Queue

#include "queue.impl.hpp"

#endif // QUEUE_HPP