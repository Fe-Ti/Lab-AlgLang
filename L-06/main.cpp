// Copyright 2020 Fe-Ti <btm.007@mail.ru>

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <vector>


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
    "                                           #######            \n"
    "   ######    #####                        #       #           \n"
    "  #@@@@@@#  #@@@@@#                       # ##### #           \n"
    " #@@#####  #@@####  ######   ######       ###   # #           \n"
    " #@#       #@#      #@@@@@#  #@@@@@#            # #           \n"
    " #@@####   #@#      #@###@@# #@###@@#      ###### #           \n"
    "  #@@@@@#  #@#  ##  #@#  #@# #@#  #@#     #       #           \n"
    "   ####@@# #@# #@@# #@#  #@# #@###@@#     # ######            \n"
    "       #@# #@#  #@# #@#  #@# #@@@@@#      # #                 \n"
    "  #####@@# #@@###@# #@#  #@# #@###@@#     # #                 \n"
    " #@@@@@@#   #@@@@@# #@#  #@# #@#  #@#     # #######           \n"
    "  ######     #####  #@###@@# #@####@#     #       #           \n"
    "                    #@@@@@#  #@@@@@@#      ########           \n"
    "                    ######   #######                          \n"
    "                                                              \n";

////////////////////////////////////////////////////////////////////////////////
// TODO: parameters in settings (present here as global non constant variables)
//       <If I had free time, I would implment this feature>
////////////////////////////////////////////////////////////////////////////////
const std::string db_name_b = "groupDB.bny";
const std::string db_name_t = "groupDB.txt";
const uint16_t protect_clear = 1; // 1 - enable, whatever else - disable
////////////////////////////////////////////////////////////////////////////////

struct discipline {
    std::string d_name;
    uint16_t mark;
};

struct student {
    std::string s_name;
    uint16_t disc_count = 0;
    std::vector<discipline> session_results;
};

struct d_matrix { // special structure used in analyze func
    std::vector<std::string> d_names;
    std::vector<float> marks_sum;
    std::vector<unsigned int> ds_nums;
};

void
b_write(std::vector<student>& group)
{
    std::ofstream ofile(db_name_b, std::ios::binary);
    if(!ofile.is_open()) {
        // a simple protection for missing files as in other funcs
        std::cout << "Failed opening file." << std::endl;
        return;
    }
    ofile.close();
}

void
operator<<(std::ofstream& ofile, std::vector<student>& group)
{
    // the half of this func is in load func
    for(student i : group) {
        std::cout << "Writing " << i.s_name << std::endl;
        ofile << i.s_name << std::endl;
        ofile << i.disc_count << std::endl;
        for(discipline& k : i.session_results) {
            ofile << k.d_name << std::endl;
            ofile << k.mark << std::endl;
        }
    }
}

void
save(std::vector<student>& group)
{
    std::string action;
    std::cout << "Enter the mode(bin - for binary, text - for text):"
              << std::endl;
    std::cin >> action;
    if(action == "bin") {
        b_write(group);
    } else if(action == "text") {
        std::ofstream ofile(db_name_t);
        if(ofile.is_open()) {
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
b_read(std::vector<student>& group)
{

    student buff_student;
    std::ifstream ifile(db_name_b, std::ios::binary);
    if(!ifile.is_open()) {
        // a simple protection for missing files as in other funcs
        std::cout << "Failed opening file." << std::endl;
        return;
    }
    ifile.close(); // closing the stream
}

void
operator>>(std::ifstream& ifile, std::vector<student>& group)
{
    student new_student;
    discipline new_disc;
    std::string buffer;

    std::getline(ifile, new_student.s_name);
    std::cout << "Name " <<  new_student.s_name << std::endl;
    while (!new_student.s_name.empty()) {
        //  ifile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        getline (ifile, buffer);
        new_student.disc_count = std::stoi(buffer);
        std::cout << "DCnt " <<  new_student.disc_count << std::endl;

        for(uint16_t i = 0; i < new_student.disc_count; ++i) {
            //    ifile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(ifile, new_disc.d_name);
            std::cout << "Name " <<  new_disc.d_name << std::endl;
            getline (ifile, buffer);
            new_disc.mark= std::stoi(buffer);
            std::cout << "Mark " << new_disc.mark << std::endl;

            new_student.session_results.push_back(new_disc);
        }
        group.push_back(new_student);
        new_student.disc_count = 0;
        new_student.session_results.clear();
        std::getline(ifile, new_student.s_name);
        std::cout << "Name " <<  new_student.s_name << std::endl;
    }
}

void
load(std::vector<student>& group)
{
    group.clear();
    std::string action;
    std::cout << "Enter the mode(bin - for binary, text - for text):"
              << std::endl;
    std::cin >> action;
    if(action == "bin") {
        b_read(group);
    } else if(action == "text") {
        std::ifstream ifile(db_name_t);
        if(ifile.is_open()) {
            ifile >> group;
        } else {
            std::cout << "Error opening the file." << std::endl;
        }
    } else {
        std::cout << action << ": command not found" << std::endl;
    }
}

void
add(std::vector<student>& group)
{
    student new_student;
    discipline new_disc;
    std::cout << "Enter the student's name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, new_student.s_name);
    std::cout << "Enter the number of disciplines: " << std::endl;
    std::cin >> new_student.disc_count;
    for(uint16_t i = 0; i < new_student.disc_count; ++i) {
        std::cout << "Enter the name of the discipline: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, new_disc.d_name);
        std::cout << "Enter the mark: ";
        std::cin >> new_disc.mark;
        new_student.session_results.push_back(new_disc);
    }
    std::cout << "Adding new student to the group...";
    if(std::cin.fail()) { // if we've inputed data of non-correct type
        std::cout << " [ Fail ] " << std::endl; // we'd not get an infinite loop
        std::cin.clear();
    } else {
        group.push_back(new_student);
        std::cout << " [  OK  ] " << std::endl;
    }
}

void
del(std::vector<student>& group)   // deleting a student
{
    int64_t number;
    std::cout << "Enter item number to delete[0-"
              << group.size() - 1 << "](-1 to cancel): ";
    std::cin >> number;
    if(number < 0) {
        std::cout << "ERROR: The number is lesser than 0." << std::endl;
        return;
    } else {
        group.erase(group.begin() + number);
    }
}


void
edit(std::vector<student>& group)
{
    std::string action;
    while(action != "exit") {

        std::cout << "Enter an edit command: ";
        std::cin >> action;

        if(action == "add") {
            add(group);
        } else if(action == "del" || action == "delete") {
            if(group.size() > 0) {
                del(group);
            } else {
                std::cout << "Group is empty" << std::endl;
            }
        } else if(action != "exit") {
            std::cout << action << ": command not found" << std::endl;
            std::cout << EDIT_HELP << std::endl;
        }
        std::cout << "Group size is " << group.size() << std::endl;
    }
}

std::ostream&
operator<<(std::ostream& out, student& buffer_student)
{
    out << buffer_student.s_name << std::endl;
    for(discipline& i : buffer_student.session_results) {
        out << i.d_name << " - " << i.mark << std::endl;
    }
    return out;
}

void
print(std::vector<student>& group)   // printing all students
{
    for(student& buffer_student : group) {
        std::cout << buffer_student << std::endl;
    }
}

void
clear(std::vector<student>& group)
{
    std::string action;
    if(protect_clear == 1) { // there we have a clear protection
        std::cout << "Are you sure? [Y/n]" << std::endl;
        std::cin >> action;
        if(action == std::string("Y")) {
            group.clear();
        }
    } else {
        group.clear();
    }
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
        for(unsigned int i = 0; i < st.disc_count; ++i) {
            d_name_s = st.session_results[i].d_name;
            mark = st.session_results[i].mark;

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
print_status(d_matrix& mx)   // printing statistics
{

}

int
main()
{
    d_matrix matrix;
    std::vector<student> group;
    std::string action;
    std::cout << SPLASH << std::endl;

    std::cout << "Enter a command: ";
    std::cin >> action;
    while(action != "exit") {
        if(action == "splash") {
            std::cout << SPLASH << std::endl;
        } else if(action == "save") {
            save(group);
        } else if(action == "load") {
            load(group);
            analyze(group, matrix);
            sort(group.begin(), group.end(), abcomp);
        } else if(action == "edit") {
            edit(group);
            analyze(group, matrix);
        } else if(action == "print") {
            print(group);
        } else if(action == "clear") {
            clear(group);
            analyze(group, matrix);
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
