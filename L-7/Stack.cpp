#include <iostream>

struct Node {
    Node* next_address;  // address of the next item
    long int value;  // item value
};

struct Stack {
    Node* enaddress;  // stack end
    unsigned long int stack_size;  // stack size
};

void constructor(Stack& stk)
{
    stk.enaddress = nullptr;  // initializing?
    stk.stack_size = 0;
}


int new_pop(Stack& stk)
{
    long int value = stk.enaddress->value;
    Node* poped_node = stk.enaddress;
    stk.enaddress = poped_node->next_address;
    delete poped_node;
    --stk.stack_size;
    return value;
}

void new_push(Stack& stk, long int value)
{
    Node* pushed_node;
    Node* addr = stk.enaddress;
    pushed_node = new Node {addr, value};
    stk.enaddress = pushed_node;
    ++stk.stack_size;
}

long int new_size(const Stack& stk)
{
    return stk.stack_size;
}

void destructor(Stack& stk)
{
    while (stk.enaddress != nullptr) {
        new_pop(stk);
    };
}

int main()
{
    std::cout << "|Declaring queue...|" << std::endl;
    Stack test;

    std::cout << "|Constructing...|" << std::endl;
    constructor(test);

    std::cout << "|Pushing!|" << std::endl;
    for ( int i = 0; i < 10; ++i) {
        new_push(test,i);
        std::cout << "stack size is " << new_size(test);
        std::cout << std::endl;
    }

    std::cout << "|Popping!|" << std::endl;
    for ( int i = 0; i < 5; ++i) {
        std::cout << new_pop(test) << std::endl;
        std::cout << "stack size is " << new_size(test);
        std::cout << std::endl;
    }

    std::cout << "|Destructing...|" << std::endl;
    destructor(test);
    return 0;
}
