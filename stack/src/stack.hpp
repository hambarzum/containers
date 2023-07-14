#ifndef STACK_HPP
#define STACK_HPP

#include <deque>

template <typename T, typename Container = std::deque<T>>
class Stack {
public:
    using container_type = Container;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

    Stack() : Stack(Container()) {}
    explicit Stack(const Container& cont);
    explicit Stack(Container&& cont);

    template <typename InputIt>
    Stack(InputIt first, InputIt last);

    Stack(const Stack& other);
    Stack& operator=(Stack rhs); // copy-and-swap idiom
    // move operator= omitted due to the operator= implemented via copy-and-swap
    Stack(Stack&& other) noexcept;

    ~Stack() {}

public:
    reference top();
    const_reference top() const;
    bool empty() const;
    size_type size() const;
    void push(const value_type& elem);
    void push(value_type&& elem);
    /// TODO: implement emplace() with variadic templates
    void pop();
    void swap(Stack& other) noexcept; 

private:
    Container c_;
}; // class Stack

namespace std {
    template <typename T, typename Container>
    void swap(Stack<T, Container>& lhs, Stack<T, Container>& rhs) noexcept;
}; // namespace std

/// TODO: research and implement non-member comparison functions for Stack

#include "stack.impl.hpp"

#endif // STACK_HPP