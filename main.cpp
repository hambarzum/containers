#include "priority_queue.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <functional>

int main() {
/*
    std::vector<int> v = {1, 13, 35, 4, 5};
    
    pq::PriorityQueue<int> pr(v.begin(), v.end());

    std::cout << pr.top() << std::endl;

    pr.push(100);

    std::cout << pr.top() << std::endl;
*/
    std::vector<int> v = {1};
    pq::PriorityQueue<int, std::vector<int>, std::less<int>> pq(std::less<int>{}, v);
    /* pq.push(100);
    pq.push(101);
    pq.push(53);

    std::cout << "size before: " << pq.size() << std::endl;
    while(!pq.empty()) {
        std::cout << pq.top() << std::endl;
        pq.pop();
    } */
    
    std::cout << pq.top() << std::endl;
    pq.pop();
    std::cout << "size after: " << pq.size() << std::endl;
    return 0;
}