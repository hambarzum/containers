#include "./src/queue.hpp"

#include <deque>
#include <iostream>

// tests
int main() {
    std::deque<int> d = {1, 2, 3, 4, 5};

    Queue<int> q;
    Queue<int> q2 = q;
    Queue<int> q3{Queue<int>{d}};
    Queue<int> q4{std::deque<int>{10, 20, 30}};
    Queue<int> q5{d.begin(), d.end()};

    std::swap(q4, q5);

    while(!q5.empty()) {
        std::cout << q5.front() << " size -> " << q5.size() << std::endl;
        q5.pop();
    }

    std::cout << "--------------" << std::endl;

    while(!q4.empty()) {
        std::cout << q4.front() << " size -> " << q4.size() << std::endl;
        q4.pop();
    }
}