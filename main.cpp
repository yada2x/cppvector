#include <iostream>
#include "Vector.h"

int main() {
    Vector<int> vec;
    vec.Push_back(1);
    vec.Push_back(2);
    vec.Push_back(5);
    vec.Push_back(7);
    vec.Push_back(11);

    std::cout << "for loop using indices" << '\n';
    for (int i = 0; i < vec.Size(); ++i) {
        std::cout << vec[i] << '\n';
    }

    std::cout << "range based for loop" << '\n';
    for (auto val : vec) {
        std::cout << val << '\n';
    }    

    std::cout << "forward iterator" << '\n';
    for (auto it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it << '\n';
    }
}
