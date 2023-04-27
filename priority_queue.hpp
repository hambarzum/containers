#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <functional> // std::less
#include <vector>


namespace pq{

template <typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class PriorityQueue {
public:
    using container_type = Container;
    using value_compare = Compare;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

public: // ctors
    PriorityQueue() : PriorityQueue(Compare(), Container()) {}
    explicit PriorityQueue(const Compare& compare) : PriorityQueue(compare, Container()) {}
    /// explicit PriorityQueue( const Compare& compare = Compare(), const Container& cont = Container() ); // until c++11
    PriorityQueue(const Compare& compare, const Container& cont);
    /// PriorityQueue(const Compare& compare, Container&& cont); // rvalue

    template <typename InputIt>
    PriorityQueue(InputIt first, InputIt last, const Compare& compare = Compare());	
    /// template< class InputIt >
    /// PriorityQueue( InputIt first, InputIt last, const Compare& compare = Compare(), const Container& cont = Container() ); // untill c++11
    template <typename InputIt>
    PriorityQueue(InputIt first, InputIt last, const Compare& compare, const Container& cont);
    /// template <typename InputIt>
    /// PriorityQueue(InputIt first, InputIt last, const Compare& compare, Container&& cont); // rvalue

public: // copy ctors, operator=
    PriorityQueue(const PriorityQueue& other);
    /// PriorityQueue(PriorityQueue&& other); // move ctor

    PriorityQueue& operator=(const PriorityQueue& other);	
    /// PriorityQueue& operator=(PriorityQueue&& other); // move operator=
    
public: // dtor
    ~PriorityQueue();

public: // member functions
    const_reference top() const;
    bool empty() const;
    [[nodiscard]] bool empty() const;
    size_type size() const;
    void push(const value_type& value);
    /// void push(value_type&& value); // rvalue
    /// template< class... Args >
    /// void emplace(Args&&... args); // variadic templates
    void pop();
    void swap(PriorityQueue& other) noexcept;

private:
    

private:
    Container c_;
    Compare comp_;
}; // class PriorityQueue


// won't let a private template function in a template class
template <typename RandomIt> // should be InputIt, but standard says RandomIt
void make_heap(RandomIt first, RandomIt last); /// TODO: make constexpr

template <typename RandomIt, typename Compare>
void make_heap(RandomIt first, RandomIt last, Compare comp); /// TODO: make constexpr

} // namespace pq

#include "priority_queue.impl.hpp"

#endif // PRIORITY_QUEUE_HPP