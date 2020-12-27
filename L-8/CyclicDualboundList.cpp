// Copyright 2020 Fe-Ti <btm.007@mail.ru>
// Cyclic Dualbound List
//
// Python is back!
//
#include <csignal>
#include <iostream>

template<typename T> struct CyclicListNode {
    CyclicListNode<T>* prev;
    CyclicListNode<T>* next;
    T data;
};

template<typename T>
CyclicListNode<T>*
init_node(T data)
{
    return new CyclicListNode<T>{ nullptr, nullptr, data };
}

template<typename T> struct CyclicList {
    CyclicListNode<T>* first;
    int64_t size;
};

template<typename T>
std::ostream&
operator<<(std::ostream& out, CyclicList<T>& list)
{
    // aka print (is usefull only for standard types)
    CyclicListNode<T>* node = list.first;
    for(int64_t i = 0; i < list.size; ++i) {
        std::cout << node->data << " ";
        node = node->next;
    }
    return out;
}

template<typename T>
void
constructor(CyclicList<T>& list)
{
    list.first = nullptr;
    list.size = 0;
}

template<typename T>
CyclicListNode<T>*
get_pointer(CyclicList<T>& list, int64_t index)
{
    CyclicListNode<T>* ptr = list.first;
    if(index > 0) {
        for(int64_t i = 0; i < index; ++i) {
            ptr = ptr->next;
        }
    } else if(index = 0) {
        ptr = list.first
    } else {
        for(int64_t i = 0; i > index; --i) {
            ptr = ptr->prev;
        }
    }
    return ptr;
}

template<typename T>
T
get(CyclicList<T>& list, int64_t index)
{
    return get_pointer(list, index)->data;
}

template<typename T>
void
pop_node(CyclicList<T>& list, CyclicListNode<T>* target, T& data)
{
    
}

template<typename T>
T
pop_back(CyclicList<T>& list)
{
}

template<typename T>
T
pop_forth(CyclicList<T>& list)
{
}

template<typename T>
T
extract(CyclicList<T>& list, int64_t index)
{
    T data;
    pop_node(list, get_pointer(list, index), data);
    return data;
}

template<typename T>
T
extract(CyclicList<T>& list, CyclicListNode<T>* ptr)
{
    T data;
    pop_node(list, ptr, data);
    return data;
}

template<typename T>
void
push_back(CyclicList<T>& list, T data)
{
}

template<typename T>
void
push_forth(CyclicList<T>& list, T data)
{
}

template<typename T>
void
insert(CyclicList<T>& list, T data, int64_t index)
{
}

template<typename T>
void
insert(CyclicList<T>& list, T data, CyclicListNode<T>* ptr)
{
}

template<typename T>
void
destructor(CyclicList<T>& list)
{
    while(list.size != 0) {
        pop_back(list);
    }
}

template<typename T>
int64_t
find(CyclicList<T>& list, T data)
{
    CyclicListNode<T>* ptr = list.first;
    int64_t index = 0;
    while((index <= list.size) && (ptr->data != data)) {
        ptr = ptr->next;
        ++index;
    }
    return index;
}

int
main()
{
    CyclicList<uint64_t> test;
    constructor(test);

    destructor(test);
    return 0;
}
