// #include "priority_queue.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

int main() {

    std::stack<int> st;
    std::vector<int> v = {1, 13, 35, 4, 5};
    std::vector<int> v2 = {10, 20, 30};
    std::priority_queue<int> pq(v2.begin(), v2.end(), std::less<int>{}, v);
    while(!pq.empty()) {
        st.push(pq.top());
        pq.pop();
    }

    while(!st.empty()) {
        std::cout << st.top() << std::endl;
        st.pop();
    }

    std::cout << std::endl;

    return 0;
}