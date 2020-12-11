// Copyright 2020 Fe-Ti <btm.007@mail.ru>

#include <fstream>
#include <iostream>
#include <vector>

const unsigned int d_name_len = 80;
const unsigned int s_name_len = 80;
const unsigned int s_name_len = 40;


std::string HELP = "Press [F] to pay respects.";

std::string SPLASH = "Something >>>SpLaSHy<<<";


// TODO: parameters in settings and different DB names
std::string db_name_b = "groupDB.bny";
std::string db_name_t = "groupDB.txt";
unsigned short int num_style = 0; // 0 - C numbering; 1 - Pascal numbering

struct discipline {
    char d_name[d_name_len];
    unsigned short int mark;
};

struct student {
    char s_name[s_name_len];
    unsigned int d_num;
    discipline* d_array = new discipline[d_num];
};

struct file_header {
    char group_code[group_code_len]];
    unsigned int s_num;
};

void
b_write(std::vector<student>& group)
{
    std::ofstream ofile(db_name_b, std::ios::binary);
    if(!ofile.is_open()) {
        std::cout << "failed opening file" << std::endl;
        return;
    }
    student buff_student;
    for(student i : group) {
        ofile.write(reinterpret_cast<char*>(&buff_student),
                    sizeof(buff_student))
    }
    ofile.close()
}

void
operator<<(std::vector<student>& group)
{
    std::ofstream ofile(db_name_t);

    if(!ofile.is_open()) {
        std::cout << "failed opening file" << std::endl;
        return;
    }
    ofile.close();
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

    if(!ofile.is_open()) {
        std::cout << "failed opening file" << std::endl;
        return;
    }
    ifile.read(reinterpret_cast<char*>(&header), sizeof(header));

    for(unsigned int i = 0; i < header.s_num; ++i) {
        ifile.read(reinterpret_cast<char*>(&buff_student),
                   sizeof(buff_student));
        group.push_back(buff_student);
    }
    ifile.close();
}

void
operator>>(std::vector<student>& group) // TODO
{
    std::ifstream ifile(db_name_t);
    if(!ofile.is_open()) {
        std::cout << "failed opening file" << std::endl;
        return;
    }
    ifile.close();
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
add(std::vector<student>& group)
{
    char s_name[s_name_len];
    char d_name[d_name_len];
    std::cout << "";
    
}
void
del(std::vector<student>& group)
{
    unsigned int
    std::cout << "Enter item number to delete[0-"<< group.size() - 1 + num_style <<"](-1 to cancel): ";
    std::cin >> number;
    if (number < 0)
        return;
    else
        group.erase(group.begin()+number - num_style);
}

void
edit(std::vector<student>& group)
{
    std::string action;
    while(action != "exit") {
        if(action == "add") {
            add(group);
        } else if(action == "del" || action == "delete") {
            del(group);
        }
    }
}

void // TODO
print(std::vector<student>& group)
{
}

void // TODO
clear(std::vector<student>& group)
{
}

void
settings() // TODO
{
    std::string action;
}

int
main()
{
    std::vector<student> group;
    file_header group_header;
    std::string action;
    

    std::getline(std::cin, action);
    while(action != "exit") {
        if(action == "splash") {
            std::cout << SPLASH << std::endl;
        } else if(action == "save") {
            save(group);
        } else if(action == "load") {
            load(group);
        } else if(action == "edit") {
            edit(group, group_header);
        } else if(action == "print") {
            print(group, group_header);
        } else if(action == "create") {
            create(group, group_header);
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
