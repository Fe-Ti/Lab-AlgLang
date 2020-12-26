// Copyright 2020 Fe-Ti <btm.007@mail.ru>

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <vector>

const unsigned int d_name_len = 40;
const unsigned int d_num = 4;
const unsigned int s_name_len = 80;
const unsigned int group_code_len = 21;

std::string HELP = "Help screen:"
                   "splash - splash screen\n"
                   "load - load group database\n"
                   "save - save group DB\n"
                   "edit - edit group DB\n"
                   "print - print group contents\n"
                   "clear - clear the contents of the group\n"
                   "help - show this help\n"
                   "\nPress [F] to pay respects and continue.\n";

std::string EDIT_HELP = "add - to add student,\n"
                        "del - to delete one,\n"
                        "cc - to change group code.";

std::string SPLASH =
  "                                                /|            \n"
  "   ######    #####                             //|@           \n"
  "  #@@@@@@#  #@@@@@#                           ///|@@          \n"
  " #@@#####  #@@####  ######   ######          ////|@@@         \n"
  " #@#       #@#      #@@@@@#  #@@@@@#        //##/|@@@@        \n"
  " #@@####   #@#      #@###@@# #@###@@#      ///##/|@@@@@       \n"
  "  #@@@@@#  #@#  ##  #@#  #@# #@#  #@#     ///////|@@@@@@      \n"
  "   ####@@# #@# #@@# #@#  #@# #@###@@#     =======#=======     \n"
  "       #@# #@#  #@# #@#  #@# #@@@@@#       @@@@@@|///////     \n"
  "  #####@@# #@@###@# #@#  #@# #@###@@#       @@@@@|/##///      \n"
  " #@@@@@@#   #@@@@@# #@#  #@# #@#  #@#        @@@@|/##//       \n"
  "  ######     #####  #@###@@# #@####@#         @@@|////        \n"
  "                    #@@@@@#  #@@@@@@#          @@|///         \n"
  "                    ######   #######            @|//          \n"
  "                                                 |/           \n";

// TODO: parameters in settings and different DB names
std::string db_name_b = "groupDB.bny";
std::string db_name_t = "groupDB.txt";
unsigned short int protect_clear = 1; // 1 - enable, whatever else - disable
unsigned short int num_style = 0;     // 0 - C numbering; 1 - Pascal numbering
unsigned short int num_width = 5;     // number colomn width (when printing)
unsigned short int s_num_width =
  10; // students amount colomn width (when printing)
unsigned short int TERM_HEIGHT = 24; // Terminal screen height
unsigned short int TERM_WIDTH = 80;  // Terminal screen height

struct discipline {
    char d_name[d_name_len];
    unsigned short int mark;
};

struct student {
    char s_name[s_name_len];
    discipline d_arr[d_num];
};

struct file_header { // used for saving, loading and etc
    char group_code[group_code_len] = "null";
    unsigned int s_num = 0;
    unsigned int d_num_h = d_num;
};

struct d_matrix { // special structure used in analyze func
    std::vector<std::string> d_names;
    std::vector<float> marks_sum;
    std::vector<unsigned int> ds_nums;
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
    // writing the header then the group
    for(student buff_student : group) {
        ofile.write(reinterpret_cast<char*>(&buff_student),
                    sizeof(buff_student));
    }
    ofile.close();
}

void
operator<<(std::ofstream& ofile, std::vector<student>& group)
{ // the half of this func is in load func
    for(student i : group) {
        std::cout << "Writing " << i.s_name << std::endl;
        ofile << i.s_name << std::endl;
        for(unsigned int j = 0; j < d_num; ++j)
            ofile << i.d_arr[j].d_name << std::endl
                  << i.d_arr[j].mark << std::endl;
    }
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
        std::ofstream ofile(db_name_t);
        if(ofile.is_open()) { // somehow this works  -.(O_O).-
            ofile << header.group_code << std::endl;
            ofile << header.s_num << " " << header.d_num_h << " ";
            // the last " " is a workaround beacuse
            // std::endl causes a mistake when reading

            ofile << group; // the most useful overload ever
            ofile.close();
        } else {
            std::cout << "Error opening the file." << std::endl;
        }
    } else {
        std::cout << action << ": command not found" << std::endl;
    }
}

void
b_read(std::vector<student>& group, file_header& header)
{

    student buff_student;
    file_header new_header;
    std::ifstream ifile(db_name_b, std::ios::binary);

    if(!ifile.is_open()) {
        // a simple protection for missing files as in other funcs
        std::cout << "Failed opening file." << std::endl;
        return;
    }

    ifile.read(reinterpret_cast<char*>(&new_header), sizeof(new_header));
    // reading the header
    if(new_header.d_num_h != d_num) {
        std::cout << "Database is incompatible!" << std::endl;
        return; // checking a new header
    } else {
        header = new_header; // updating if it's OK
    }
    std::cout << "There are " << header.s_num << " students with " << d_num
              << " disciplines from " << header.group_code << "." << std::endl;
    // now reading the group (the first s_num students)
    for(unsigned int i = 0; i < header.s_num; ++i) {
        ifile.read(reinterpret_cast<char*>(&buff_student),
                   sizeof(buff_student));
        group.push_back(buff_student);
    }

    ifile.close(); // closing the stream
}

void
operator>>(std::ifstream& ifile, std::vector<student>& group)
{
    // Oh, my function size... *FACEPALM*
    // Also if we try to read a faulty DB
    // we'll fail. Cool.
    student buffer;
    std::string buffer_s_name;
    std::string d_name;
    std::string mark; // several buffers for reading strings

    std::getline(ifile, buffer_s_name);
    while(!ifile.eof() || buffer_s_name != "") {

        // debugging info
        std::cout << "Loading buffer_s_name " << buffer_s_name << std::endl;

        for(unsigned int i = 0; i < s_name_len; ++i)
            buffer.s_name[i] = buffer_s_name[i];
        buffer_s_name.clear();
        for(unsigned int j = 0; j < d_num; ++j) {
            std::getline(ifile, d_name);

            // debugging info
            std::cout << "Loading d_name " << d_name << std::endl;

            for(unsigned int i = 0; i < d_name_len; ++i)
                buffer.d_arr[j].d_name[i] = d_name[i];
            std::getline(ifile, mark);

            // debugging info
            std::cout << "Loading mark " << mark << std::endl;

            buffer.d_arr[j].mark = std::stoi(mark);
            d_name.clear();
            mark.clear();
        }
        group.push_back(buffer);

        std::getline(ifile, buffer_s_name);
        // workaround for .eof not working properly (#kludge)
    }
}

void
load(std::vector<student>& group, file_header& header)
{
    group.clear(); // when there is no protection [LOL]
    std::string action;
    std::cout << "Enter the mode(bin - for binary, text - for text):"
              << std::endl;
    std::cin >> action;
    if(action == "bin") {
        b_read(group, header);
    } else if(action == "text") { // a lot of srange stuff
        // just because the arch. of DB was not meant to have a text FIO
        std::ifstream ifile(db_name_t);
        if(ifile.is_open()) {
            std::string header_s_num;
            std::string header_d_num;
            std::string header_group_code;
            std::getline(ifile, header_group_code);

            // debugging info
            std::cout << "Loading " << header_group_code << std::endl;

            ifile >> header_s_num >> header_d_num;

            // debugging info
            std::cout << "Loading " << header_s_num << std::endl;
            std::cout << "Loading " << header_d_num << std::endl;

            if(header.d_num_h == d_num) {
                header.s_num = std::stoi(header_s_num);
                header.d_num_h = std::stoi(header_d_num);
                for(unsigned int i = 0; i < group_code_len; ++i)
                    header.group_code[i] = header_group_code[i];

                ifile >> group; // LOL
                ifile.close();
                std::cout << "There are " << header.s_num << " students with "
                          << d_num << " disciplines from " << header.group_code
                          << "." << std::endl;
            } else {
                std::cout << "Database is incompatible!" << std::endl;
            }
        } else {
            std::cout << "Error opening the file." << std::endl;
        }
    } else {
        std::cout << action << ": command not found" << std::endl;
    }
}

void
add(std::vector<student>& group, file_header& header) // adding a new student
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
    if(std::cin.fail()) { // if we've inputed data of non-correct type
        std::cout << " [ Fail ] " << std::endl; // we'd not get an infinite loop
        std::cin.clear();
    } else {
        group.push_back(new_student);
        std::cout << " [  OK  ] " << std::endl;
        header.s_num = group.size();
    }
}

void
del(std::vector<student>& group, file_header& header) // deleting a student
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
edit_group_code(file_header& header) // editing group code
{
    std::string action;
    while(action != "exit") {
        std::cout << "Current group code is \"" << header.group_code
                  << "\". Enter a new one starting with '!' or enter \"exit\""
                  << std::endl;
        getline(std::cin, action);

        std::cout << "action word len " << action.length() << ", it#0"
                  << action.length() - 1 << ", it#1"
                  << group_code_len - action.length() + 1
                  << std::endl; // debuging info

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
        }

        else if(action == "del" || action == "delete") {
            if(group.size() > 0) {
                del(group, header);
            } else
                std::cout << "Group is empty" << std::endl;
        } else if(action == "cc" || action == "ec") {
            edit_group_code(header);
        } else if(action != "exit") {
            std::cout << action << ": command not found" << std::endl;
            std::cout << EDIT_HELP << std::endl;
        }
        std::cout << "Group size is " << group.size() << std::endl;
    }
}

void
operator<<(std::ostream& out, student& buffer_student) // ugly, but it works
{                                                      // printing 1 student
    std::cout << buffer_student.s_name << std::endl;

    std::cout << "|" << std::setw(num_width) << "N"
              << "|" << std::setfill('_') << std::setw(d_name_len - 1);
    std::cout << "Discipline";
    std::cout << "__|__Mark" << std::endl;

    for(size_t i = 0 + num_style; i < d_num + num_style; ++i) {

        std::cout << "|" << std::setw(num_width) << i << "|"
                  << std::setfill('_') << std::setw(d_name_len - 1);
        std::cout << buffer_student.d_arr[i - num_style].d_name;

        std::cout << "__|__" << buffer_student.d_arr[i - num_style].mark
                  << std::endl;
    }
}

void
print_all(std::vector<student>& group) // printing all students
{
    for(student& buffer_student : group) {
        std::cout << buffer_student;
    }
}

void
print(std::vector<student>& group, file_header& header) // printing func
{
    unsigned int index = 0;
    std::string action;

    if(group.size() * d_num <= TERM_HEIGHT) {
        print_all(group); // if the group is small, we'll print all students
    }

    std::cout << "There are " << header.s_num << " students with " << d_num
              << " disciplines from " << header.group_code << "." << std::endl;
    std::cout << "Enter the desired indexes (exit - to exit the print fnc):";
    std::cout << std::endl;
    std::cout << "Note: indexes start from 0, all - to print all." << std::endl;

    while(action != "exit") {
        std::cin >> action;
        if(action == "all") {
            print_all(group);
        } else if(action != "exit") {
            try {
                index = std::stoi(action);
                if(index < group.size()) {
                    std::cout << group[index];
                } else {
                    std::cout << "There is no such index." << std::endl;
                }
            } catch(...) { // catching everything (I should learn more about
                           // this thing)
                std::cout << "ERROR!" << std::endl;
            }
        }
    }
}

void
clear(std::vector<student>& group, file_header& header)
{
    std::string action;
    if(protect_clear == 1) { // there we have a clear protection
        std::cout << "Are you sure? [Y/n]" << std::endl;
        std::cin >> action;
        if(action == std::string("Y")) {
            group.clear();
            header.s_num = group.size();
        }
    } else {
        group.clear();
        header.s_num = group.size();
    }
}

void
settings()
{
}

void
analyze(std::vector<student>& group, d_matrix& mx)
{
    mx.d_names.clear();
    mx.marks_sum.clear(); // cleaning the matrix
    mx.ds_nums.clear();

    std::string d_name_s;
    unsigned short int mark;
    const unsigned int ds_num = 1;
    unsigned int pos;
    auto iter = mx.d_names.begin(); // just for initialization

    for(student& st : group) {
        for(unsigned int i = 0; i < d_num; ++i) {
            d_name_s = static_cast<std::string>(st.d_arr[i].d_name);
            mark = st.d_arr[i].mark;

            iter = std::find(mx.d_names.begin(), mx.d_names.end(), d_name_s);

            if(iter == mx.d_names.end()) {
                mx.d_names.push_back(d_name_s);
                mx.marks_sum.push_back(mark);
                mx.ds_nums.push_back(ds_num);
            } else {
                pos = std::distance(mx.d_names.begin(), iter);
                mx.marks_sum[pos] += static_cast<float>(mark);
                mx.ds_nums[pos] += ds_num;
            }
        }
    }
}

struct { // custom function object for sort
    bool operator()(student a, student b)
    {
        return a.s_name > b.s_name;
    }
} abcomp;

void
print_status(d_matrix& mx) // printing statistics
{
    std::cout << std::setw(TERM_WIDTH) << std::setfill('_')
              << "Group status:" << std::endl;

    std::cout << "|" << std::setw(num_width) << "N"
              << "|" << std::setfill('_') << std::setw(d_name_len - 1)
              << "Discipline"
              << "|" << std::setfill('_') << std::setw(num_width) << "Mark"
              << "|" << std::setfill('_') << std::setw(s_num_width) << "Amount"
              << std::setw(TERM_WIDTH - s_num_width - 2 * num_width -
                           d_name_len - 3)
              << std::setfill('_') << "|" << std::endl;

    for(unsigned int i = 0; i < mx.d_names.size(); ++i) {
        std::cout << "|" << std::setw(num_width) << i << "|"
                  << std::setfill('_') << std::setw(d_name_len - 1)
                  << mx.d_names[i] << "|" << std::setfill('_')
                  << std::setw(num_width) << mx.marks_sum[i] / mx.ds_nums[i]
                  << "|" << std::setfill('_') << std::setw(s_num_width)
                  << mx.ds_nums[i]
                  << std::setw(TERM_WIDTH - s_num_width - 2 * num_width -
                               d_name_len - 3)
                  << std::setfill('_') << "|" << std::endl;
    }
    
    std::cout << std::setw(TERM_WIDTH) << std::setfill('-') << "-" << std::endl;
}

int
main()
{
    d_matrix matrix;
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
            analyze(group, matrix);
            sort(group.begin(), group.end(), abcomp);
        } else if(action == "edit") {
            edit(group, header);
            analyze(group, matrix);
        } else if(action == "print") {
            print(group, header);
        } else if(action == "clear") {
            clear(group, header);
            analyze(group, matrix);
        } else if(action == "settings") {
            settings(); // TBD
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
        print_status(matrix);
        std::cout << "Enter a command: ";
        std::cin >> action;
    }

    return 0;
}
