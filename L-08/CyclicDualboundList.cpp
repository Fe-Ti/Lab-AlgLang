// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
// Cyclic Dualbound List
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
init_node(T data) // "constructor" for a single node
                  // used in func-s for adding elements
{
    return new CyclicListNode<T>{ nullptr, nullptr, data };
}

template<typename T> struct CyclicList { // actual list structure

    CyclicListNode<T>* first; // pointer to the first element
                              // due to its nature cyclic list
                              // does not need to have a pointer
                              // to the last element
    int64_t size;
};

template<typename T>
void
constructor(CyclicList<T>& list) // constructor for a list
{
    list.first = nullptr;
    list.size = 0;
}

template<typename T>
CyclicListNode<T>*
get_pointer(CyclicList<T>& list, int64_t index) // indexes in lists are usefull
                                                // only for humane humans,
                                                // so we do not need them
{
    CyclicListNode<T>* ptr = list.first;
    if(index > 0) {
        for(int64_t i = 0; i < index; ++i) {
            ptr = ptr->next;
            std::cout << "Getting pointer for " << index;
            std::cout << ": iter " << i << " element " << ptr->data;
            std::cout << std::endl;
        }
    } else if(index == 0) {
        ptr = list.first;
    } else {
        for(int64_t i = 0; i > index; --i) {
            ptr = ptr->prev;
            std::cout << "Getting pointer for " << index;
            std::cout << ": iter " << i << " element " << ptr->data;
            std::cout << std::endl;
        }
    }
    std::cout << "Pointing at -> " << ptr->data << " as element #" << index
              << std::endl;
    return ptr;
}

template<typename T>
T
get(CyclicList<T>& list, int64_t index) // just getting data from a node
{
    return get_pointer(list, index)->data;
}

template<typename T>
void
pop_node(CyclicListNode<T>* target,
         T& data) // internal func
{
    target->next->prev = target->prev; // repointing
    target->prev->next = target->next;
    data = target->data;
    delete target;
}

template<typename T>
T
pop_back(CyclicList<T>& list)
{
    T data;
    if(list.size > 1) {
        pop_node(list.first->prev, data); // a simple way to get last node
        --list.size;
        std::cout << "Removed one "; // giving debug feedback
    } else if(list.size == 1) {
        data = list.first->data; // if we're trying to remove the last node
        delete list.first;       // we'll remove it
        list.first = nullptr;    // and clean pointer to the first node
        --list.size;
        std::cout << "Removed last" << std::endl;
    }            // silently ignoring if list size < 1
    return data; // some garbage will be returned if list size is 0
}

template<typename T>
T
pop_forth(CyclicList<T>& list) // the same as pop_back(CyclicList<T>& list)
                               // except for the side of popping
{
    T data;
    if(list.size > 1) {
        list.first = list.first->next;
        pop_node(list.first->prev, data);
        --list.size;
        std::cout << "Removed one";
    } else if(list.size == 1) {
        data = list.first->data;
        delete list.first;
        list.first = nullptr;
        --list.size;
        std::cout << "Removed last " << std::endl;
    } // again silently ignoring if list size < 1
    return data;
}

template<typename T>
T
extract(CyclicList<T>& list, int64_t index) // extracting by index
{
    T data;
    CyclicListNode<T>* buff_ptr;
    if(list.size > 1) {
        buff_ptr = get_pointer(list, index); // we need to store the pointer
        if(index == 0)
            list.first = list.first->next; // before changing list.first pointer
        pop_node(buff_ptr, data); // because we'll lose it after popping
        --list.size;
        std::cout << "Extracted " << data << " at " << index << std::endl;
    } else if(list.size == 1) {
        data = list.first->data; // the workaround for the last node
        delete list.first;
        list.first = nullptr;
        --list.size;
    }
    return data;
}

template<typename T>
T
extract(CyclicList<T>& list,
        CyclicListNode<T>* ptr) // overload of extract for pointers
                                // the same as for indexes,
                                // except for direct ptrs availability
{
    T data;
    if(list.size > 1) {
        if(list.first == ptr)
            list.first = list.first->next;
        pop_node(ptr, data);
        --list.size;
        std::cout << "Extracted " << data << " at " << ptr << std::endl;

    } else if(list.size == 1) {
        data = list.first->data; // the same workaround
        delete list.first;
        list.first = nullptr;
        --list.size;
    }
    return data;
}

template<typename T>
CyclicListNode<T>*
add_node(CyclicListNode<T>* target, T data) // internal func
                                            // used in pushes and inserts
{
    CyclicListNode<T>* new_node = init_node(data);
    new_node->next = target->next;
    new_node->prev = target;
    target->next->prev = new_node; // repointing stuff (inserting the node)
    target->next = new_node;
    return new_node; // returning a pointer to the new node
}

template<typename T>
void
push_back(CyclicList<T>& list, T data) // pushing back
{
    if(list.first != nullptr) { // if there are some nodes (>1 pcs)
        add_node(list.first->prev, data);
        std::cout << " Pushing b " << data;
    } else {
        list.first = init_node(data); // the workaround for null lists
        list.first->next = list.first;
        list.first->prev = list.first;
        std::cout << " Pushing b first " << data;
    }
    ++list.size; // increasing size!
}

template<typename T>
void
push_forth(CyclicList<T>& list, T data) // the same as pushing back, but forth
{
    if(list.first != nullptr) {
        add_node(list.first->prev, data);
        list.first = list.first->prev;
        std::cout << " Pushing f " << data;
    } else {
        list.first = init_node(data);
        list.first->next = list.first;
        list.first->prev = list.first;
        std::cout << " Pushing f first " << data;
    }
    ++list.size;
}

template<typename T>
void
insert(CyclicList<T>& list, T data, int64_t index) // the most painful function
                                                   // here is its 4th version
{
    if(std::abs(index) < list.size) { // checking if abs.value of index
                                      // is lesser than list size
        if(list.first != nullptr) {
            if(index >= 0) {
                CyclicListNode<T>* new_node_ptr =
                  add_node(get_pointer(list, index - 1), data);
                if(index == 0)
                    list.first = new_node_ptr;
            } else {
                add_node(get_pointer(list, index), data);
            }
            std::cout << "Inserted " << data << " at " << index << std::endl;
        } else {
            list.first = init_node(data);
            list.first->next = list.first;
            list.first->prev = list.first;
        }
        ++list.size;
    } // silently ignoring other indxes
}

template<typename T>
void
insert(CyclicList<T>& list, T data, CyclicListNode<T>* ptr) // insert after
                                                            // pointer's node
{
    if(ptr != nullptr) {
        add_node(ptr, data); // The Most Epic Function Ever
        std::cout << "Inserted " << data << " after " << ptr->data << std::endl;
        ++list.size;
    }
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
find(CyclicList<T>& list, T data) // find func just looks though the list
{
    CyclicListNode<T>* ptr = list.first;
    int64_t index = 0;
    while((index <= list.size) && (ptr->data != data)) {
        ptr = ptr->next;
        ++index;
    }
    return index;
}

template<typename T>
int64_t
size(CyclicList<T>& list)
{
    return list.size; // VERY useful function )
}

template<typename T>
void
print(CyclicList<T>& list)
{
    CyclicListNode<T>* ptr = list.first;
    for(int64_t i = 0; i < list.size; ++i) {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
}

////////////////////////////////////////////////////////////
struct dummy {
    uint64_t ismth0[2];
    uint64_t ismth1[2];
    uint64_t ismth2[20];
    uint64_t ismth3[12];
    uint64_t ismth4[11];
    double fsmth0[12];
};

std::ostream&
operator<<(std::ostream& out, dummy& obj)
{
    out << obj.ismth0[0];
    return out;
}
////////////////////////////////////////////////////////////

int
main()
{ /*
     // user's type demo
     CyclicList<dummy> test;
     constructor(test);

     dummy heavy_data;
     for(int i = 0; i < 100; ++i)
         push_back(test, heavy_data); // testing push back
     print(test);
     for(int i = 0; i < 100; ++i)
         push_forth(test, heavy_data); // testing push forth
     print(test);
     for(int i = 0; i < 100; ++i)
         pop_back(test); // testing pop back
     print(test);
     for(int i = 0; i < 100; ++i)
         pop_forth(test); // testing pop forth
     destructor(test);
 */
    // std type demo
    CyclicList<int32_t> test_int;
    constructor(test_int);

    std::cout << "Performing: push_back" << std::endl;
    for(int i = 0; i < 5; ++i) {
        push_back(test_int, i);
        print(test_int);
    }

    std::cout << std::endl;
    print(test_int); // should be 0 1 2 3 4

    std::cout << "Performing: push_forth" << std::endl;
    for(int i = 0; i < 5; ++i) {
        push_forth(test_int, i + 10);
        print(test_int);
    }

    std::cout << std::endl;
    print(test_int); // should be 14 13 12 11 10 0 1 2 3 4

    std::cout << "Performing: insert by index" << std::endl;
    for(int i = -1; i < 3; ++i) {
        insert(test_int, i + 20, i);
        print(test_int);
    }

    std::cout << std::endl;
    print(test_int); // should be 20 21 22 14 13 12 11 10 0 1 2 3 4 19

    std::cout << "Performing: insert by ptr" << std::endl;
    for(int i = 0; i < 5; ++i) {
        insert(test_int, i + 100, get_pointer(test_int, i - 4));
        print(test_int);
    }

    std::cout << "14 is #" << find(test_int, 14) << std::endl; // should be 4
    std::cout << "Current size is " << size(test_int) << std::endl;
    // should be 19 (maybe not, I'm not precise)

    std::cout << std::endl;
    print(test_int); // should be
                     // 20 104 21 22 14 13 12 11 10 0 1 2 100 3 101 4 102 19 103

    std::cout << "Performing: extract by index" << std::endl;
    for(int i = 0; i < 5; ++i) {
        extract(test_int, i * 2);
        print(test_int);
    }

    std::cout << std::endl;
    print(test_int); // should be 104 21 14 13 11 10 1 2 3 101 4 102 19 103

    std::cout << "Performing: extract by ptr" << std::endl;
    for(int i = -2; i < 5; ++i) {
        extract(test_int, get_pointer(test_int, i + 2));
        print(test_int);
    }

    std::cout << std::endl;
    print(test_int); // should be 21 13 10 2 101 102 103

    destructor(test_int);
    return 0;
}
