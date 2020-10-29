#include <iostream>
#include <string>
#include <vector>

std::vector<std::string>
split(std::string& str, char ch = ' ')
{
    std::vector<std::string> substr_list(0); // vector for output
    bool flag = 1;                           // just a flag for signalling
    for (char i : str) {
        if (i == ch) // checking if $i is a splitting character
        {
            flag = 1; // now we know that we need to start new "word"
        } else {
            if (flag == 0) // if the flag is 0, we'll just push back $i
            {
                substr_list[substr_list.size() - 1].push_back(i);
            } else // if the flag == 1
            {
                substr_list.push_back(""); // starting new "word"
                // and pushing back $i
                substr_list[substr_list.size() - 1].push_back(i);
                flag = 0; // also we don't want to start another one
            }
        }
    }
    return substr_list; // returning our vector
}

// demo stuff
void
print_vec(const std::vector<auto>& vec)
{
    for (auto& i : vec) {
        std::cout << i << "  <---element\n";
    }
    std::cout << std::endl;
}

int
main()
{
    std::string line = "";
    char ch = ' ';
    getline(std::cin, line);
    std::cin >> ch;
    print_vec(split(line, ch));
    return 0;
}
