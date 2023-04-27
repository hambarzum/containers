#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <functional> // std::less
#include <iterator> // std::iterator_traits
#include <vector>


namespace pq {

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
    [[nodiscard]] bool empty() const;
    size_type size() const;
    void push(const value_type& value);
    /// void push(value_type&& value); // rvalue
    /// template< class... Args >
    /// void emplace(Args&&... args); // variadic templates
    void pop();
    void swap(PriorityQueue& other) noexcept;

private:
    template <typename RandomIt> // should be InputIt, but standard says RandomIt => slicing
    void makeHeap(RandomIt first, RandomIt last); /// TODO: make constexpr
    template <typename RandomIt>
    void makeHeap(RandomIt first, RandomIt last, Compare comp); /// TODO: make constexpr
    template <typename RandomIt>
    void heapify(RandomIt first, RandomIt last, RandomIt target, Compare comp);
    /// size_t parent(size_t index);
    template <typename RandIt>
    RandIt getLeftChild(RandIt first, RandIt last, RandIt parent);
    template <typename RandIt>
    RandIt getRightChild(RandIt first, RandIt last, RandIt parent);
    template <typename RandIt>
    RandIt getChild(RandIt first, RandIt last, RandIt parent, typename std::iterator_traits<RandIt>::difference_type childId);

private:
    Container c_;
    Compare comp_;
}; // class PriorityQueue

} // namespace pq

#include "priority_queue.impl.hpp"

#endif // PRIORITY_QUEUE_HPP