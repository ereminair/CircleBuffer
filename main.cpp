#include <iostream>
#include <algorithm>
#include "CircularBuffer.h"

int main() {
    CircularBuffer::CircularBuffer<int>a(5);
    a.PushFront(5);
    a.PushFront(6);
    a.PushBack(4);
    a.PushFront(7);
//    //654
//    std::cout << a[0] << ' ' << a[1] << ' ' << a[2] << '\n';
//    std::cout << *(a.begin()) << ' ' << *(a.begin() + 1) << ' ' << *(a.begin() + 2) << *(a.begin() + 3);
    for(auto i : a) std::cout << i << ' ';

    //std::sort(a.begin(), a.end());
    //std::cout << a.GetIter(a.begin());
}