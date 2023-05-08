#include "./priority_queue/priority_queue.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <functional>

int main() {

    std::vector<int> v = {1, 13, 35, 4, 5, 5, -6};

    pq::PriorityQueue<int> p1(v.begin(), v.end());
    p1.push(100);
    p1.push(101);
    p1.push(53);
    
    pq::PriorityQueue<int> p2(v.begin(), v.end());
    p1.swap(p2);

    while(!p1.empty()) {
        std::cout << p1.top() << " -> size: " << p1.size() << std::endl;
        p1.pop();
    }

    // std::cout << pqq.top() << std::endl;
    return 0;
}