#include "./priority_queue/priority_queue.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <functional>

int main() {

    std::vector<int> v = {1, 13, 35, 4, 5, 5};
    std::vector<int> v2 = {10, 10};
    pq::PriorityQueue<int> pr(v.begin(), v.end());


    pq::PriorityQueue<int, std::vector<int>, std::less<int>> pq(std::less<int>{}, v);
    pq.push(100);
    pq.push(101);
    pq.push(53);
    pq::PriorityQueue<int, std::vector<int>, std::greater<int>> pp(std::greater<int>{}, v);
    pp = pr;
    
    while(!pr.empty()) {
        std::cout << pr.top() << std::endl;
        pr.pop();
    }

    // std::cout << pqq.top() << std::endl;
    return 0;
}