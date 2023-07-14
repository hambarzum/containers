#include "./src/stack.hpp"

#include <deque>
#include <iostream>
#include <vector>

// tests
int main() {
    std::deque<int> d = {1, 2, 3, 4, 5};
    Stack<int> s(d);

    std::cout << std::endl;
    std::vector<int> v = {100, 200, 300, 400};
    s = Stack<int>(d);

    Stack<int> s2{v.begin(), v.end()};
    std::cout << "s2 top: " << s2.top()++ << std::endl;
    std::cout << "s1 top: " << s.top() << std::endl;

    swap(s, s2);

    std::cout << "s2 top: " << s2.top()++ << std::endl;
    std::cout << "s1 top: " << s.top() << std::endl;
    s = s2;

    while(!s.empty()) {
        s.pop();
    }

    s.pop();
}