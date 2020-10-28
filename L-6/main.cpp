#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct discipline {
    std::string name = "";  // The name of the discipline
    unsigned short int mark = 0;  // student's mark
};

struct student {
    std::string name = ""; // student's name
    std::vector<discipline> session_results{};
};

std::vector<std::string> split (std::string &str, char ch = ' ')
{
    std::vector<std::string> substr_list(0); // vector for output
    bool flag = 1;  // just a flag for signalling
    for (char i : str) {
        if (i == ch) { // checking if $i is a splitting character
            flag = 1;  // now we know that we need to start new "word"
        } else {
            if (flag == 0) { // if the flag is 0, we'll just push back $i
                substr_list[substr_list.size() - 1].push_back(i);
            } else { // if the flag == 1
                substr_list.push_back("");  // starting new "word"
                // and pushing back $i
                substr_list[substr_list.size() - 1].push_back(i);
                flag = 0;  // also we don't want to start another one
            }
        }
    }
    return substr_list;  // returning our vector
}


//std::vector<std::string>
void
read_db(const std::string& db_name,
        std::vector<student>& group, int limit = 1)
{
    std::ifstream studb(db_name);

    student cur_student{"",{}};
    discipline cur_discipline{"",0};

    std::vector<std::string> str_buffer(0);

    std::string line = "start";
    short unsigned int counter_of_emptys = 0;

    while ((line != "EOF")&&(counter_of_emptys < limit)) {
        std::cout << line << std::endl;
        if (line.empty()) {
            std::cout << "Encountered empty line!\n";
            ++counter_of_emptys;
        } else {
            std::cout << "passed first else!\n";
            if (line == "BEGIN_ENTRY") {
                getline(studb, line);
                cur_student.name = line;
                getline(studb, line);
                str_buffer = split(line,',');
                for (size_t i = 0; i < str_buffer.size(); i+=2) {
                    cur_discipline.name = str_buffer[i];
                    cur_discipline.mark = static_cast<int>(str_buffer[i + 1][0]) - 48;
                    cur_student.session_results.push_back(cur_discipline);
                }
            }
            if (line == "END_ENTRY") {
                group.push_back(cur_student);
                cur_student.name.clear();
                cur_student.session_results.clear();
            }
        }
        getline(studb, line);
    }
    studb.close();

//    return group;
}
void
print_db (const std::vector<student>& group)
{
    for (student i : group) {
        std::cout << i.name << std::endl;
        for (discipline j : i.session_results)
            std::cout << j.name << " : " << j.mark << std::endl;
    }
    std::cout << group.size() << std::endl;
}

void
analyze (const std::vector<student>& group, student& status)
{
    std::vector<std::string> disc_names(0);
    auto is_in_disc = disc_names.begin();
    float buffer = 0.0;
    int pos = 0;

    for (student i : group) {
        for (discipline j : i.session_results) {
            is_in_disc = std::find(disc_names.begin(),disc_names.end(), j.name);
            if (is_in_disc != disc_names.end())
            {
                pos = std::distance(disc_names.begin(), is_in_disc);
                buffer = static_cast<float>(j.mark);
                buffer += static_cast<float>(status.session_results[pos]);
                status.session_results. = buffer / 2;
            }
            else
            {
                disc_names.push_back(j.name);
                status.session_results.push_back(j);
            }
            }
    }
}

int main()
{
    student status{"Average student",{}};
    std::vector<student> group(0);
    std::string action = "";
    while (action != "exit") {
        std::getline(std::cin, action);
        if (action == "read") {
            group.clear();
            status.session_results.clear();
            read_db("students.txt", group);
            analyze(group, status);
        }
        if (action == "print") {
            print_db(group);
        }
        if (action == "sort") {
            std::sort(group.begin(),group.end(),[](student a, student b) {
                return a.name < b.name;
            });
        }
        if (action == "write") {
            std::cout << "LOL" << std::endl;
        }
        if (action == "status") {
            for (discipline j : status.session_results)
                std::cout << j.name << " : " << j.mark << std::endl;
        }

//        if (action == "")
//        {
//
//        }

    }
}
