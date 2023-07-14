#ifndef STACK_IMPL_HPP
#define STACK_IMPL_HPP

#include "stack.hpp"

#include <stdexcept> // std::underflow_error

// constructors--------------------
template <typename T, typename Container>
Stack<T, Container>::Stack(const Container& cont)
    : c_{cont}
{}

template <typename T, typename Container>
Stack<T, Container>::Stack(Container&& cont) 
    : c_{std::move(cont)}
{}

template <typename T, typename Container>
Stack<T, Container>::Stack(const Stack& other) 
    : c_{other.c_}
{}

template <typename T, typename Container>
auto Stack<T, Container>::operator=(Stack rhs) -> Stack& {
    rhs.swap(*this);
    return *this;
}

template <typename T, typename Container>
Stack<T, Container>::Stack(Stack&& other) noexcept 
    : c_{std::move(other.c_)}
{}


template <typename T, typename Container>
template <typename InputIt>
Stack<T, Container>::Stack(InputIt first, InputIt last)
    : c_{first, last}
{}


// member functions-----------------
template <typename T, typename Container>
auto Stack<T, Container>::top() -> reference {
    return const_cast<reference>(const_cast<const Stack*>(this)->c_.back()); // calls the const version of top(), then gets rid of the constness of the return value
}

template <typename T, typename Container>
auto Stack<T, Container>::top() const -> const_reference {
    return c_.back();
}

template <typename T, typename Container>
bool Stack<T, Container>::empty() const {
    return c_.empty();
}

template <typename T, typename Container>
auto Stack<T, Container>::size() const -> size_type {
    return c_.size();
} 

template <typename T, typename Container>
void Stack<T, Container>::push(const value_type& elem) {
    c_.push_back(elem);
}

template <typename T, typename Container>
void Stack<T, Container>::push(value_type&& elem) {
    c_.push_back(std::move(elem));
}

template <typename T, typename Container>
void Stack<T, Container>::pop() {
    if(c_.empty()) {
        throw std::underflow_error("[Stack] : trying to pop from an empty stack.");
    }
    c_.pop_back();
}

template <typename T, typename Container>
void Stack<T, Container>::swap(Stack& other) noexcept {
    using std::swap;
    swap(c_, other.c_);
}


// non-member functions-------------------
namespace std {
    template <typename T, typename Container>
    void swap(Stack<T, Container>& lhs, Stack<T, Container>& rhs) noexcept {
        lhs.swap(rhs);
    }
}; // namespace std

#endif // STACK_IMPL_HPP