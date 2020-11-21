// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Linear Not Dualbound List
//

#include <iostream>

template<typename T> struct ListNode {
    T data;
};

template<typename T, unsigned int S> struct LinearList {
    ListNode<T>* nodes[S];
    unsigned long int size; // current size
};

template<typename T, unsigned int S>
void
constructor(LinearList<T, S>& list)
{
    list.size = 0;
    for(unsigned int i = 0; i < S; ++i)
        list.nodes[i] = nullptr;
}

template<typename T, unsigned int S>
int
append(LinearList<T, S>& list, T data)
{
    if(list.size < S) {
        ListNode<T>* new_node = new ListNode<T>{ data };
        list.nodes[list.size] = new_node;
        ++list.size;
        return 0;
    } else {
        return 1;
    }
}

template<typename T, unsigned int S>
int
insert(LinearList<T, S>& list, T data, unsigned int index)
{
    if(list.size < S) {
        ListNode<T>* new_node = new ListNode<T>{ data };
        for(unsigned int i = list.size; i > index; --i)
            list.nodes[i] = list.nodes[i - 1];
        list.nodes[index] = new_node;
        ++list.size;
        return 0;
    } else {
        return 1;
    }
}

template<typename T, unsigned int S>
T
pop(LinearList<T, S>& list, unsigned int index)
{
    T data = list.nodes[index]->data;
    delete list.nodes[index];
    list.nodes[index] = nullptr;
    for(unsigned int i = index; i < list.size - 1; ++i) {
        list.nodes[i] = list.nodes[i + 1];
    }
    list.nodes[list.size - 1] = nullptr;
    --list.size;
    return data;
}

template<typename T, unsigned int S>
T
pop_back(LinearList<T, S>& list)
{
    return pop(list, list.size - 1);
}

template<typename T, unsigned int S>
T
pop_forth(LinearList<T, S>& list)
{
    return pop(list, 0);
}

template<typename T, unsigned int S>
T
get(LinearList<T, S>& list, unsigned int index)
{
    return list.nodes[index]->data;
}

template<typename T, unsigned int S>
unsigned int
find(LinearList<T, S>& list, T data)
{
    for(unsigned int i = 0; i < list.size; ++i)
        if(list.nodes[i]->data == data)
            return i;
    return list.size;
}

template<typename T, unsigned int S>
void
print(LinearList<T, S>& list)
{
    for(unsigned int i = 0; i < list.size; ++i)
        std::cout << list.nodes[i]->data << " ";
    std::cout << std::endl;
}

template<typename T, unsigned int S>
void
destructor(LinearList<T, S>& list)
{
    while(list.size != 0) {
        std::cout << pop_back(list) << " ";
    }
}

int
main()
{
    LinearList<int, 10> test;
    constructor(test);
    print(test);
    append(test, 1);
    print(test);
    append(test, 2);
    print(test);
    append(test, 3);
    print(test);
    append(test, 4);
    print(test);
    std::cout << find(test, 0) << std::endl;
    insert(test, 0, static_cast<unsigned int>(0));
    print(test);
    std::cout << find(test, 0) << std::endl;
    destructor(test);
    print(test);
    return 0;
}
