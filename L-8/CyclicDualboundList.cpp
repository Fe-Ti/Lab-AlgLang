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
    CyclicListNode<T>* last;
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
    list.last = nullptr;
    list.size = 0;
}

template<typename T>
CyclicListNode<T>*
get_pointer(CyclicList<T>& list, int64_t index)
{
    CyclicListNode<T>* ptr = list.first;
    if(index >= 0) {
        for(int64_t i = 0; i < index; ++i) {
            ptr = ptr->next;
        }
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
    if(target == nullptr)
        return;
    CyclicListNode<T>* prev = target->prev;
    CyclicListNode<T>* next = target->next;
    data = target->data;
    --list.size;
    if(list.size != 0) {
        prev->next = next;
        next->prev = prev;
    } else {
        list.first = nullptr;
        list.last = nullptr;
    }
    delete target; // killing target node
}

template<typename T>
T
pop_back(CyclicList<T>& list)
{
    T data;
    CyclicListNode<T>* target = list.last;
    list.last = target->prev;
    pop_node(list, target, data);
    return data;
}

template<typename T>
T
pop_forth(CyclicList<T>& list)
{
    T data;
    CyclicListNode<T>* target = list.first;
    list.first = target->next;
    pop_node(list, target, data);
    return data;
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
CyclicListNode<T>*
create_node(CyclicList<T>& list, CyclicListNode<T>* target, T data)
{
    CyclicListNode<T>* new_node = init_node(data);
    if(list.size != 0) {
        CyclicListNode<T>* prev = target;
        CyclicListNode<T>* next = target->next;
        next->prev = new_node;
        new_node->next = next;
        prev->next = new_node;
        new_node->prev = prev;
    } else {
        new_node->prev = new_node;
        new_node->next = new_node;
    }
    ++list.size;
    return new_node;
}

template<typename T>
void
push_back(CyclicList<T>& list, T data)
{
    CyclicListNode<T>* new_node = create_node(list, list.last, data);
    if(list.first == nullptr)
        list.first = new_node;
    list.last = new_node;
}

template<typename T>
void
push_forth(CyclicList<T>& list, T data)
{
    CyclicListNode<T>* new_node = create_node(list, list.last, data);
    if(list.last == nullptr)
        list.last = new_node;
    list.first = new_node;
}

template<typename T>
void
insert(CyclicList<T>& list, T data, int64_t index)
{
    CyclicListNode<T>* new_node =
      create_node(list, get_pointer(list, index - 1), data);
}

template<typename T>
void
insert(CyclicList<T>& list, T data, CyclicListNode<T>* ptr)
{
    CyclicListNode<T>* new_node = create_node(list, ptr, data);
}

template<typename T>
void
destructor(CyclicList<T>& list)
{
    while(list.size != 0) {
        pop_forth(list);
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
    uint64_t i = 0;
    int64_t j = 0;
    for(i = 0; i < 10; ++i)
        push_back(test, i);
    std::cout << test << std::endl;
    for(i = 10; i < 30; ++i)
        push_forth(test, i);
    std::cout << test << std::endl;
    std::cout << std::endl;
    std::cout << get(test, 5) << std::endl;
    std::cout << get(test, -5) << std::endl;
    i = 100;
    j = 5;
    insert(test, i, j);
    std::cout << get(test, 5) << std::endl;
    std::cout << get(test, -5) << std::endl;
    std::cout << find(test, i) << " " << test.size << std::endl;
    std::cout << test << std::endl;

    extract(test, j);
    std::cout << get(test, 5) << std::endl;
    std::cout << get(test, -5) << std::endl;
    std::cout << find(test, i) << " " << test.size << std::endl;
    std::cout << test << std::endl;

    destructor(test);
    return 0;
}
