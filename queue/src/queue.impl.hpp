#ifndef QUEUE_IMPL_HPP
#define QUEUE_IMPL_HPP

#include "queue.hpp"

#include <stdexcept> // std::underflow_error
#include <utility> // std::move

// constructors------------------------
template <typename T, typename Container>
Queue<T, Container>::Queue(const Container& cont)
    : c_{cont}
{

}

template <typename T, typename Container>
Queue<T, Container>::Queue(Container&& cont)
    : c_{std::move(cont)}
{

}

template <typename T, typename Container>
Queue<T, Container>::Queue(const Queue& other)
    : c_{other.c_}
{

}

template <typename T, typename Container>
auto Queue<T, Container>::operator=(Queue rhs) -> Queue& {
    rhs.swap(*this);
    return *this;
}

template <typename T, typename Container>
Queue<T, Container>::Queue(Queue&& other)
    : c_{std::move(other.c_)}
{

}

template <typename T, typename Container>
template <typename InputIt>
Queue<T, Container>::Queue(InputIt first, InputIt last)
    : c_{first, last}
{

}

// member functions--------------------
template <typename T, typename Container>
auto Queue<T, Container>::front() -> reference {
    return const_cast<reference>(const_cast<const Queue*>(this)->front());
}

template <typename T, typename Container>
auto Queue<T, Container>::front() const -> const_reference {
    return c_.front();
}

template <typename T, typename Container>
auto Queue<T, Container>::back() -> reference {
    return const_cast<reference>(const_cast<const Queue*>(this)->back());
}

template <typename T, typename Container>
auto Queue<T, Container>::back() const -> const_reference {
    return c_.back();
}

template <typename T, typename Container>
bool Queue<T, Container>::empty() const {
    return c_.empty();
}

template <typename T, typename Container>
auto Queue<T, Container>::size() const -> size_type {
    return c_.size();
}

template <typename T, typename Container>
void Queue<T, Container>::push(const value_type& elem) {
    c_.push_back(elem);
}

template <typename T, typename Container>
void Queue<T, Container>::push(value_type&& elem) {
    c_.push_back(std::move(elem));
}

template <typename T, typename Container>
void Queue<T, Container>::pop() {
    if(c_.empty()) {
        throw std::underflow_error("[Queue]: trying to pop from an empty queue.");
    }
    c_.pop_front();
}

template <typename T, typename Container>
void Queue<T, Container>::swap(Queue& other) noexcept {
    using std::swap;
    swap(c_, other.c_);
}

// non-member functions--------------------
namespace std {
    template <typename T, typename Container>
    void swap(Queue<T, Container>& lhs, Queue<T, Container>& rhs) noexcept {
        lhs.swap(rhs);
    }
}; // namespace std

#endif // QUEUE_IMPL_HPP