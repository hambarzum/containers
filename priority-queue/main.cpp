#include "./src/pq/priority_queue.hpp"

#include <iostream>
#include <vector>
#include <queue>


// tests
int main() {

    std::vector<int> v = {1, 13, 35, 4, 5, 5, -6};

    PriorityQueue<int> p1(v.begin(), v.end());
    p1.push(100);
    p1.push(101);
    p1.push(53);
    
    PriorityQueue<int> p2(v.begin(), v.end());
    swap(p1, p2);

    PriorityQueue<int> p3;
    p3 = p2;
    while(!p3.empty()) {
        std::cout << p3.top() << std::endl;
        p3.pop();
    }

    std::cout << "--------------" << std::endl;
    p3.swap(p2);

    while(!p2.empty()) {
        std::cout << p2.top() << std::endl;
        p2.pop();
    }

    std::cout << "--------------" << std::endl;

    PriorityQueue<int> pq{PriorityQueue<int>{v.begin(), v.end()}};
    while(!pq.empty()) {
        std::cout << pq.top() << std::endl;
        pq.pop();
    }

    // std::cout << pqq.top() << std::endl;
    return 0;
}