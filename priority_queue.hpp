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
    void makeHeap(RandomIt first, RandomIt last);
    template <typename RandomIt>
    void makeHeap(RandomIt first, RandomIt last, const Compare& comp);
    template <typename RandomIt>
    void heapify(RandomIt first, RandomIt last, RandomIt target, const Compare& comp);
    template <typename RandomIt>
    RandomIt getLeftChild(RandomIt first, RandomIt last, RandomIt parent);
    template <typename RandomIt>
    RandomIt getRightChild(RandomIt first, RandomIt last, RandomIt parent);
    template <typename RandomIt>
    RandomIt getChild(RandomIt first, RandomIt last, RandomIt parent, typename std::iterator_traits<RandomIt>::difference_type childId);
    template <typename RandomIt>
    void increaseKey(RandomIt first, RandomIt target);
    template <typename RandomIt>
    RandomIt getParent(RandomIt first, RandomIt child);

private:
    Container c_;
    Compare comp_;
    size_type size_;
}; // class PriorityQueue

} // namespace pq

#include "priority_queue.impl.hpp"

#endif // PRIORITY_QUEUE_HPP