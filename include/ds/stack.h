#pragma once
#include <stdexcept>

template <typename T>
class Stack {
    T* a;
    int cap;
    int topIdx;
public:
    Stack(int capacity = 1000) : cap(capacity), topIdx(-1) {
        a = new T[cap];
    }
    ~Stack() { delete[] a; }

    bool empty() const { return topIdx < 0; }
    void clear() { topIdx = -1; }

    void push(const T& x) {
        if (topIdx + 1 >= cap) throw std::runtime_error("Stack overflow");
        a[++topIdx] = x;
    }

    T pop() {
        if (empty()) throw std::runtime_error("Stack underflow");
        return a[topIdx--];
    }
};
