// Copyright 2021 Fe-Ti <btm.007@mail.ru>
// License WTFPL

#include <exception>
#include <iostream>
#include <vector>

#include "vector.hpp"

class some_exception : public std::exception
{
  public:
    char _what[27];

    some_exception(const char st[])
    {
        for(int i = 0; i < 27; ++i) {
            _what[i] = st[i];
        }
    }
    ~some_exception() override
    {
        std::cout << "Oh, no!" << std::endl;
    }
};

struct some_data {
    char data;
    some_data(char ch)
    {
        data = ch;
    }
};

void
some_function(some_data c)
{
    if(c.data == 'k') {
        throw some_exception("Some exception is awesome!");
    }
}

class Foo
{
  public:
    virtual ~Foo()
    {
    }
};

class Bar
{
  public:
    virtual ~Bar()
    {
    }
};

int
main(int argc, char** argv)
{
    bool running_with_valgrind;
    if(argc > 1) {
        running_with_valgrind = *argv[1] - 48;
    } else {
        std::cout << "Are we running with valgrind? 0 - false  or 1 - true)"
                  << std::endl;
        std::cin >> running_with_valgrind;
    }
    if(!running_with_valgrind) {
        std::cout << "Part I 'Standard exceptions and a custom one'"
                  << std::endl;
        std::vector<uint8_t> v = { 'a', 'b', 'c', 'd', 'e' };
        std::cout << "    //````\\\\    " << std::endl;
        try {
            std::cout << "Trying get vec[vec.size()]" << std::endl;
            v.at(v.size());
        } catch(const std::out_of_range& error) {
            std::cout << "ERROR out_of_range: " << error.what() << std::endl;
        }
        std::cout << "    \\\\____//    " << std::endl;
        std::cout << std::endl;

        std::cout << "    //````\\\\    " << std::endl;
        try {
            std::cout << "Trying to resize the vector to size_t(-1)"
                      << std::endl;
            v.resize(-1);
        } catch(const std::length_error& error) {
            std::cout << "ERROR length_error: " << error.what() << std::endl;
        }
        std::cout << "    \\\\____//    " << std::endl;
        std::cout << std::endl;

        std::cout << "    //````\\\\    " << std::endl;
        try {
            std::cout << "Trying to get int from 'LOL' " << std::endl;
            std::stoi("LOL");
        } catch(const std::invalid_argument& error) {
            std::cout << "ERROR invalid_argument: " << error.what()
                      << std::endl;
        }
        std::cout << "    \\\\____//    " << std::endl;
        std::cout << std::endl;

        std::cout << "    //````\\\\    " << std::endl;
        try {
            Foo foo;
            std::cout << "Trying to make Bar from Foo " << std::endl;
            dynamic_cast<Bar&>(foo);
        } catch(const std::bad_cast& error) {
            std::cout << "ERROR bad_cast: " << error.what() << std::endl;
        }
        std::cout << "    \\\\____//    " << std::endl;
        std::cout << std::endl;

        std::cout << "    //````\\\\    " << std::endl;
        try {
            std::cout << "Trying to allocate too much memory" << std::endl;
            uint32_t sz = -1;
            new uint64_t[sz];
        } catch(const std::bad_alloc& error) {
            std::cout << "ERROR: " << error.what() << std::endl;
        }
        std::cout << "    \\\\____//    " << std::endl;
        std::cout << std::endl;

        std::cout << "    //````\\\\    " << std::endl;
        try {
            some_data smth('k');
            std::cout << "Trying to  " << std::endl;
            some_function(smth);
        } catch(const some_exception& error) {
            std::cout << "ERROR: " << error._what << std::endl;
        }
        std::cout << "    \\\\____//    " << std::endl;
        std::cout << std::endl;

    } else {
        std::cout << "Part II 'Non-RAII and RAII programming techniques'"
                  << std::endl;
        std::cout << "  ////******////  " << std::endl;
        try {
            std::cout << "We have int* some_pointer" << std::endl;
            int* some_pointer = nullptr;
            std::cout << "Allocating some memory for it..." << std::endl;
            some_pointer = new int[100];
            std::cout << "But then something throws an exception." << std::endl;
            throw "<whatever exception>";
            delete[] some_pointer;
        } catch(const char* error) {
            std::cout << "ERROR: " << error << std::endl;
            std::cout
              << "And we are going to catch block, hence we are avoiding "
                 "delete. So now we have some memory leakage."
              << std::endl;
        }
        std::cout << "  \\\\\\\\......\\\\\\\\  " << std::endl;
        std::cout << std::endl;

        std::cout << "  ////******////  " << std::endl;
        try {
            std::cout
              << "In Resource Acquisition Is Initialization or RAII we use "
                 "some object, e.g. std::vector instead of C-style array"
              << std::endl;
            std::vector<int> vec(100);
            std::cout << "And if something throws an exception." << std::endl;
            throw "<whatever exception>";
        } catch(const char* error) {
            std::cout << "ERROR: " << error << std::endl;
            std::cout
              << "We are going to catch block, but as std::vector handles "
                 "memory we don't have any leakage."
              << std::endl;
        }
        std::cout << "  \\\\\\\\......\\\\\\\\  " << std::endl;
        std::cout << std::endl;

        std::cout << "  ////******////  " << std::endl;
        try {
            std::cout
              << "In Resource Acquisition Is Initialization or RAII we use "
                 "some object, e.g. Vector instead of C-style array"
              << std::endl;
            Vector<int> vec(100);
            std::cout << "And if something throws an exception." << std::endl;
            throw "<whatever exception>";
        } catch(const char* error) {
            std::cout << "ERROR: " << error << std::endl;
            std::cout << "We are going to catch block, but as Vector handles "
                         "memory we don't have any leakage."
                      << std::endl;
        }
        std::cout << "  \\\\\\\\......\\\\\\\\  " << std::endl;
        std::cout << std::endl;
    }
    return 0;
}