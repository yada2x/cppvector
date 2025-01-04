#include <iostream>
#include "Vector.h"

int main() {
    Vector<float> v;
    v.Push_back(10);
    v.Push_back(20);
    v.Push_back(30);
    v.Push_back(10);
    v.Push_back(20);
    v.Push_back(30);
    v.Push_back(10);
    v.Push_back(20);
    v.Push_back(30);
    v.Push_back(99);
    v.Pop_back();
    v.Erase(0);

    for (int i = 0; i < v.Size(); i++) {
        std::cout << "arr[" << i << "] = " << v[i] << '\n';
    }
    std::cout << "Size = " << v.Size() << ", Capacity = " << v.Capacity() << '\n';
    return 0;
}
