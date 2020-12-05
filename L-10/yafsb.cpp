// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//

#include <bitset>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

namespace stdfs = std::filesystem;

// if the code was of a production quality,
// I would use smth like this {load_config("yafsb.conf");}
// but there is no real need. So here is some hardcoding
stdfs::path curr_dir = stdfs::current_path();
stdfs::path home_dir = curr_dir;

void
pwd()
{
    std::cout << curr_dir.string() << std::endl;
}

int
main()
{

    std::string action;
    do {
        if(!action.empty()) // skipping if action is ""
        {
            pwd();
        }
        std::cout << std::bit getline(std::cin, action);
    } while(action != "exit");

    return 0;
}
