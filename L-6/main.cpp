// Copyright 2020 Fe-Ti <btm.007@mail.ru>

#include <iostream>
#include <vector>

std::string HELP = "Press [F] to pay respects.";

struct discipline {
    char d_name[80];
    unsigned short int mark;
};

struct student {
    char s_name[80];
    unsigned int d_num;
    discipline* d_array;
};

struct file_header {
    unsigned int s_num;
};

void
save()
{
}
void
load()
{
}
void
edit()
{
}
void
print()
{
}
void
create()
{
}
void
clear()
{
}

int
main()
{
    std::vector<student> group;
    std::string action;

    std::getline(std::cin, action);
    while(action != "exit") {
        if(action == "load") {

        } else if(action == "save") {
            save();
        } else if(action == "load") {

        } else if(action == "edit") {

        } else if(action == "print") {

        } else if(action == "create") {

        } else if(action == "clear") {

        } else if(action == "help") {
            std::cout << HELP << std::endl;
        } else if(action == "moo") {
            std::cout << "Have you mooed today?" << std::endl;
        } else {
            std::cout << action << ": command not found" << std::endl;
        }
        std::cout << "Enter a command: ";
        std::getline(std::cin, action);
    }

    return 0;
}
