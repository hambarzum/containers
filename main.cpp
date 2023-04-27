#include "priority_queue.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

int main() {
    std::vector<int> v = {1, 13, 35, 4, 5};
    
    pq::PriorityQueue<int> pr(v.begin(), v.end());

    std::cout << pr.top() << std::endl;

    //pr.push(100);

    std::cout << pr.top() << std::endl;

    return 0;
}