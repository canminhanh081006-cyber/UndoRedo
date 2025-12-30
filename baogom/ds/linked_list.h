#pragma once
#include <cstddef>

template <typename T>
class LinkedList {
    struct Node { T data; Node* next; Node(const T& d): data(d), next(nullptr) {} };
    Node* head=nullptr; Node* tail=nullptr; std::size_t n=0;
public:
    LinkedList() = default;
    ~LinkedList(){ clear(); }
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    std::size_t size() const { return n; }
    void push_back(const T& x){
        Node* p=new Node(x);
        if(!tail) head=tail=p; else { tail->next=p; tail=p; }
        ++n;
    }
    void clear(){
        Node* cur=head;
        while(cur){ Node* nxt=cur->next; delete cur; cur=nxt; }
        head=tail=nullptr; n=0;
    }
    template<class F>
    void for_each(F fn) const { for(Node* cur=head; cur; cur=cur->next) fn(cur->data); }
};
