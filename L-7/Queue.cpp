#include <iostream>

struct Node {
    Node* next_address;
    int value;
};

struct Queue {
    Node* bnaddress;
    Node* enaddress;
};

void constructor(Queue& que)
{
    que.bnaddress = nullptr;
    que.enaddress = nullptr;

}

int new_pop(Queue& que)
{
    int value = que.bnaddress->value;
    Node* poped_node = que.bnaddress;
    std::cout << "next address is " << poped_node->next_address << std::endl;
    que.bnaddress = poped_node->next_address;

    delete poped_node;

    return value;
}

void new_push(Queue& que, int value)
{
    Node* pushed_node;
    Node* addr = nullptr;
    pushed_node = new Node {addr, value};
    if (que.enaddress != nullptr) {
        que.enaddress->next_address = pushed_node;
        std::cout << "set que.enaddress->next_address = " << pushed_node << std::endl;
    }
    que.enaddress = pushed_node;
    if (que.bnaddress == nullptr) {
        que.bnaddress = que.enaddress;
        std::cout << std::endl;
    }
}

void destructor(Queue& que)
{
    while (que.bnaddress != nullptr) {
        std::cout << new_pop(que) << std::endl;
    };
}


int main()
{
    std::cout << "|Declaring queue...|" << std::endl;
    Queue test;
    std::cout << "|Constructing...|" << std::endl;
    constructor(test);

    std::cout << "|Pushing!|" << std::endl;
    for ( int i = 0; i < 100; ++i) {
        ;
        new_push(test,i);
    }

    std::cout << "|Popping!|" << std::endl;
    for ( int i = 0; i < 5; ++i) {
        new_pop(test);
    }

    std::cout << "|Destructing...|" << std::endl;
    destructor(test);
    return 0;
}
