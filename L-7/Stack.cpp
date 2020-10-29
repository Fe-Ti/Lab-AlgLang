#include <iostream>

struct Node {
    Node* next_adress;
    long int value;
};

struct Stack {
    Node* enadress;
};

void constructor(Stack& stk)
{
    stk.enadress = nullptr;
}


int new_pop(Stack& stk)
{
    long int value = stk.enadress->value;
    Node* poped_node = stk.enadress;

    stk.enadress = poped_node->next_adress;

    delete poped_node;

    return value;
}

void new_push(Stack& stk, long int value)
{
    Node* pushed_node;
    Node* addr = stk.enadress;
    pushed_node = new Node {addr, value};
    stk.enadress = pushed_node;
}


void destructor(Stack& stk)
{
    while (stk.enadress != nullptr) {
        new_pop(stk);
    };
}

int main()
{
    char a;
    std::cin >> a;

    Stack test;
    constructor(test);
    for (long int i = 0; i < 10000000; ++i)
        new_push(test,i);
    std::cout << "POPPING" << std::endl;

    std::cin >> a;
    destructor(test);
    std::cin >> a;
    return 0;
}
