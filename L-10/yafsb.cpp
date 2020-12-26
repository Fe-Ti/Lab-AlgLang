// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//

#include <bitset>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

namespace stdfs = std::filesystem;

const std::string cnf = ": command not found";

struct session_data {
    std::string ps1;
    stdfs::path curr_dir;
    stdfs::path home_dir;
};

void
pwd(session_data& session)
{
    std::cout << session.curr_dir.string() << std::endl;
}

std::string
item_type(stdfs::directory_entry item)
{
    if(item.is_directory())
        return "directory";
    else if(item.is_symlink())
        return "symlink  ";
    else
        return "file     ";
}

void
ls(session_data& session)
{
    std::cout << "Contents list:" << std::endl;
    for(auto& item : stdfs::directory_iterator(session.curr_dir)) {
        std::cout << "";
        std::cout << item_type(item) << " -> ";
        std::cout << stdfs::relative(item.path()).string() << std::endl;
    }
}

void
mkdir(session_data& session)
{
    stdfs::path dest;
    std::string action;
    std::cin >> action;
    if(action[0] != '/') {
        dest = session.curr_dir / action;
    } else {
        dest = action;
    }
    try {

        if(!stdfs::directory_entry(dest).exists()) {
            stdfs::create_directory(dest);
        } else {
            std::cout << "The directory already exists." << std::endl;
        }
    } catch(stdfs::filesystem_error& error) {
        std::cout << error.what() << std::endl;
    }
}

void
info(session_data& session)
{
    std::string action;
    std::cin >> action;
    std::cout << action << " is ";
    try {
        if(action[0] != '/') {
            std::cout << stdfs::file_size(session.curr_dir / action);
        } else {
            std::cout << stdfs::file_size(action);
        }
        std::cout << " bytes length." << std::endl;
    } catch(stdfs::filesystem_error& error) {
        std::cout << error.what() << std::endl;
    }
}

void
cp(session_data& session)
{
    std::string action;
    stdfs::path dest;
    stdfs::path source;
    std::cin >> action;
    if(action[0] != '/') {
        source = session.curr_dir / action;
    } else {
        source = action;
    }
    std::cin >> action;
    if(action[0] != '/') {
        dest = session.curr_dir / action;
    } else {
        dest = action;
    }
    try {
        stdfs::copy(source,
                    dest,
                    stdfs::copy_options::recursive |
                      stdfs::copy_options::update_existing);
    } catch(stdfs::filesystem_error& error) {
        std::cout << error.what() << std::endl;
    }
}

void
rm(session_data& session)
{
    std::string action;
    std::cin >> action;
}

void
cd(session_data& session)
{
    std::string action;
    std::cin >> action;
}

void
mv(session_data& session)
{
    std::string action;
    std::cin >> action;
}

void
help(session_data& session)
{
}

int
main()
{
    session_data session;
    // if the code was of a production quality,
    // I would use smth like this {load_config("yafsb.conf");}
    // but there is no real need. So here is some hardcoded init.

    // session.
    session.curr_dir = stdfs::current_path();
    session.home_dir = session.curr_dir; // should be read from a config file
    // we'll show current path as a $PS1
    session.ps1 = session.curr_dir.string() + std::string("$ ");
    std::string action;

    std::cout << session.ps1;
    std::cin >> action;
    while(action != "exit") {
        if(action == "pwd") {
            pwd(session);
        } else if(action == "ls") {
            ls(session);
        } else if(action == "mkdir") {
            mkdir(session);
        } else if(action == "info") {
            info(session);
        } else if(action == "cp") {
            cp(session);
        } else if(action == "rm") {
            rm(session);
        } else if(action == "cd") {
            cd(session);
        } else if(action == "mv") {
            mv(session);
        } else if(action == "help") {
            help(session);
        } else if(action != "exit") {
            std::cout << action << cnf << std::endl;
            std::cout << "Enter 'help' to see avaliable commands." << std::endl;
        }
        std::cin.clear();
        std::cout << session.ps1;
        std::cin >> action;
    }

    return 0;
}
