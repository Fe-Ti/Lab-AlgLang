// Copyright 2020 Fe-Ti <btm.007@mail.ru>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

const unsigned int d_name_len = 40;
const unsigned int d_num = 4;
const unsigned int s_name_len = 80;
const unsigned int group_code_len = 21;

std::string HELP = "Press [F] to pay respects.";

std::string EDIT_HELP = "add - to add student,\n"
                        "del - to delete one,\n"
                        "cc - to change group code.";

std::string SPLASH = "Something >>>SpLaSHy<<<";

// TODO: parameters in settings and different DB names
std::string db_name_b = "groupDB.bny";
std::string db_name_t = "groupDB.txt";
unsigned short int num_style = 0;    // 0 - C numbering; 1 - Pascal numbering
unsigned short int TERM_HEIGHT = 24; // Terminal screen height

struct discipline {
    char d_name[d_name_len];
    unsigned short int mark;
};

struct student {
    char s_name[s_name_len];
    discipline d_arr[d_num];
};

struct file_header {
    char group_code[group_code_len] = "null";
    unsigned int s_num = 0;
    unsigned int d_num_h = d_num;
};

void
b_write(std::vector<student>& group, file_header& header)
{
    std::ofstream ofile(db_name_b, std::ios::binary);
    if(!ofile.is_open()) {
        std::cout << "Failed opening file." << std::endl;
        return;
    }

    ofile.write(reinterpret_cast<char*>(&header), sizeof(header));

    for(student buff_student : group) {
        ofile.write(reinterpret_cast<char*>(&buff_student),
                    sizeof(buff_student));
    }
    ofile.close();
}

void
operator<<(std::ofstream& ofile, std::vector<student>& group)
{
    if(!ofile.is_open()) {
        std::cout << "Failed opening file." << std::endl;
        return;
    }
    ofile.close();
}

void
save(std::vector<student>& group, file_header& header)
{
    std::string action;
    std::cout << "Enter the mode(bin - for binary, text - for text):"
              << std::endl;
    std::cin >> action;
    if(action == "bin") {
        b_write(group, header);
    } else if(action == "text") {
        std::ofstream ofile(db_name_t); // TODO
        ofile << group;                 // the best overload ever
    } else {
        std::cout << action << ": command not found" << std::endl;
    }
}

void
b_read(std::vector<student>& group, file_header& header)
{

    student buff_student;
    std::ifstream ifile(db_name_b, std::ios::binary);

    if(!ifile.is_open()) {
        std::cout << "Failed opening file." << std::endl;
        return;
    }

    ifile.read(reinterpret_cast<char*>(&header), sizeof(header));

    if(header.d_num_h != d_num) {
        std::cout << "Database is incompatible!" << std::endl;
        return;
    } else {
        std::cout << "There are " << header.s_num << " students with " << d_num
                  << " disciplines from " << header.group_code << "."
                  << std::endl;
    }

    for(unsigned int i = 0; i < header.s_num; ++i) {
        ifile.read(reinterpret_cast<char*>(&buff_student),
                   sizeof(buff_student));
        group.push_back(buff_student);
    }

    ifile.close();
}

void
operator>>(std::ifstream& ifile,
           std::vector<student>& group) // TODO
{
    if(!ifile.is_open()) {
        std::cout << "Failed opening file." << std::endl;
        return;
    }
    ifile.close();
}

void
load(std::vector<student>& group, file_header& header)
{
    std::string action;
    std::cout << "Enter the mode(bin - for binary, text - for text):"
              << std::endl;
    std::cin >> action;
    if(action == "bin") {
        b_read(group, header);
    } else if(action == "text") {
        std::ifstream ifile(db_name_t); // todo
        ifile >> group;                 // the best overload ever
    } else {
        std::cout << action << ": command not found" << std::endl;
    }
}

void
add(std::vector<student>& group, file_header& header)
{
    student new_student;

    std::cout << "Enter student's name" << std::endl;
    std::cin >> new_student.s_name;

    for(unsigned int i = 0; i < d_num; ++i) {
        std::cout << "Enter discipline " << i + num_style << " name";
        std::cout << std::endl;
        std::cin >> new_student.d_arr[i].d_name;
        std::cout << "Enter mark" << std::endl;
        std::cin >> new_student.d_arr[i].mark;
    }

    std::cout << "Adding new student to the group...";
    if(std::cin.fail()) {
        std::cout << " [ Fail ] " << std::endl;
        std::cin.clear();
    } else {
        group.push_back(new_student);
        std::cout << " [  OK  ] " << std::endl;
        header.s_num = group.size();
    }
}

void
del(std::vector<student>& group, file_header& header)
{
    long int number; // In theory simple int cant cover all possible
                     // group sizes (but I've never seen such groups)
    std::cout << "Enter item number to delete[" << num_style << "-"
              << group.size() - 1 + num_style << "](-1 to cancel): ";
    std::cin >> number;
    if(number < 0) {
        std::cout << "ERROR: The number is lesser than 0." << std::endl;
        return;
    } else {
        group.erase(group.begin() + number - num_style);
        header.s_num = group.size();
    }
}

void
edit_group_code(file_header& header)
{
    std::string action;
    while(action != "exit") {
        std::cout << "Current group code is \"" << header.group_code
                  << "\". Enter a new one starting with '!' or enter \"exit\""
                  << std::endl;
        getline(std::cin, action);

        std::cout << "action word len " << action.length() << ", it#0"
                  << action.length() - 1 << ", it#1"
                  << group_code_len - action.length() + 1 << std::endl;

        if(action[0] == '!' && action.length() <= group_code_len) {
            for(unsigned int i = 0; i < action.length() - 1; ++i) {
                header.group_code[i] = action[i + 1];
            }
            for(unsigned int i = 0; i < group_code_len - action.length() + 1;
                ++i) {
                header.group_code[i + action.length() - 1] = '\0';
            }
        } else if(action != "exit") {
            std::cout << action << ": command not found" << std::endl;
        }
    }
}

void
edit(std::vector<student>& group, file_header& header)
{
    std::string action;
    while(action != "exit") {

        std::cout << "Enter an edit command: ";
        std::cin >> action;

        if(action == "add") {
            add(group, header);
        } else if(action != "exit") {
            std::cout << EDIT_HELP << std::endl;
        } else if(action == "del" || action == "delete") {
            if(group.size() > 0) {
                del(group, header);
            } else
                std::cout << "Group is empty" << std::endl;
        } else if(action == "cc" || action == "ec") {
            edit_group_code(header);
        } else if(action != "exit") {
            std::cout << action << ": command not found" << std::endl;
        }
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Group size is " << group.size() << std::endl;
    }
}

void
operator<<(std::iostream& out; student & buffer_student)
{
    std::cout << std::setw(80) << buffer_student.s_name << std::endl;
    for(size_t i; i < d_num; ++i) {
        std::cout << std::setw(40) << buffer_student.d_arr[i].d_name;
        std::cout << std::setw(40) << buffer_student.d_arr[i].mark << std::endl;
    }
}

void // TODO
print(std::vector<student>& group, file_header& header)
{
    if(group.size() * d_num <= TERM_HEIGHT) {
        for(student buffer_student : &group) {
            std::cout << buffer_student;
        }
        return;
    }
    std::string action;
}

void // TODO
clear(std::vector<student>& group, file_header& header)
{
}

void
settings() // TODO
{
}

int
main()
{
    std::vector<student> group;
    file_header header;
    std::string action;
    std::cout << SPLASH << std::endl;

    std::cout << "Enter a command: ";
    std::cin >> action;
    while(action != "exit") {
        if(action == "splash") {
            std::cout << SPLASH << std::endl;
        } else if(action == "save") {
            save(group, header);
        } else if(action == "load") {
            load(group, header);
        } else if(action == "edit") {
            edit(group, header);
        } else if(action == "print") {
            print(group, header);
        } // else if(action == "create") {
          //   create(group, header);}
        else if(action == "clear") {
            clear(group, header);
        } else if(action == "settings") {
            settings();
        } else if((action == "help") || (action == "F")) {
            std::cout << HELP << std::endl;
        } else if(action == "moo") {
            std::cout << "Have you mooed today?" << std::endl;
        } else if(action != "exit") {
            std::cout << action << ": command not found" << std::endl;
        }
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Enter a command: ";
        std::cin >> action;
    }

    return 0;
}
