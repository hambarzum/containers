#include "priority_queue.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <functional>

int main() {

    std::vector<int> v = {1, 13, 35, 4, 5, 5};
    std::vector<int> v2 = {10, 10};
    pq::PriorityQueue<int> pr(v2.begin(), v2.end());


    pq::PriorityQueue<int, std::vector<int>, std::greater<int>> pq(std::greater<int>{}, v);
    pq.push(100);
    pq.push(101);
    pq.push(53);
    pq::PriorityQueue<int, std::vector<int>, std::less<int>> pp(std::less<int>{}, v);
    pp = pr;

    // pr.swap(pq);

    std::priority_queue<int> pqq(v.begin(), v.end());
    std::priority_queue<int, std::vector<int>, std::greater<int>> pqq2(std::greater<int>{}, v2);
    
    while(!pqq.empty()) {
        std::cout << pqq.top() << std::endl;
        pqq.pop();
    }

    std::cout << pqq.top() << std::endl;
    return 0;
}