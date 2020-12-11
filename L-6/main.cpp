// Copyright 2020 Fe-Ti <btm.007@mail.ru>

#include <fstream>
#include <iostream>
#include <vector>

std::string HELP = "Press [F] to pay respects.";
std::string db_name_b = "groupDB.bny";
std::string db_name_t = "groupDB.txt";

struct discipline {
    char d_name[80];
    unsigned short int mark;
};

struct student {
    char s_name[80];
    unsigned int d_num;
    discipline* d_array = new discipline[d_num];
};

struct file_header {
    unsigned int s_num;
};

void
b_write(std::vector<student>& group)
{
    std::ofstream ofile(db_name_b, std::ios::binary);

    for(student i : group) {
        ofile.write()
    }
}

void
operator<<(std::vector<student>& group)
{
    std::ofstream of(db_name_t);
}

void
save(std::vector<student>& group)
{
    std::string action;
    std::getline(std::cin, action);
    if(action == "bin") {
        b_write(group);
    } else if(action == "text") {
        << (group); // the best overload ever
    } else {
        std::cout << action << ": command not found" std::endl;
    }
}

void
b_read(std::vector<student>& group)
{
    file_header header;
    student buff_student;
    std::ifstream ifile(db_name_b, std::ios::binary);

    ifile.read(reinterpret_cast<char*>(&header), sizeof(header));

    for(unsigned int i = 0; i < header.s_num; ++i) {
        ifile.read(reinterpret_cast<char*>(&buff_student), sizeof(buff_student));
        group.push_back(buff_student);
    }
}

void
operator>>(std::vector<student>& group)
{
    std::ifstream ifile(db_name_t);
}

void
load(std::vector<student>& group)
{
    std::string action;
    std::getline(std::cin, action);
    if(action == "bin") {
        b_read(group);
    } else if(action == "text") {
        >> (group); // the best overload ever
    } else {
        std::cout << action << ": command not found" std::endl;
    }
}

void
edit(std::vector<student>& group)
{
    std::string action;
}

void
print(std::vector<student>& group)
{
}

void
clear(std::vector<student>& group)
{
}

void
settings()
{
    std::string action;
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
            save(group);
        } else if(action == "load") {
            load(group);
        } else if(action == "edit") {
            edit(group);
        } else if(action == "print") {
            print(group);
        } else if(action == "create") {
            create(group);
        } else if(action == "clear") {
            clear(group);
        } else if(action == "settings") {
            settings();
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
