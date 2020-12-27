// Copyright 2020 Fe-Ti <btm.007@mail.ru>
//
/*
 * ### What is this ###
 * This is a very simple set of functions built
 * upon the <filesystem> API. It doesn't pretend to be
 * a command shell, but it tries to mimic such behaviour.
 *
 * A link to the tutorial of shell writing can be found below
 * https://brennan.io/2015/01/16/write-a-shell-in-c/
 *
 * ### How does this code works ###
 *
 * 1)User enters a command:
 *
 *      mv green/tea .
 *      ^
 *      | "mv" == "mv", so we call mv(session_data&) function
 *
 * 2)Now in the mv function cin has buffered "green/tea .":
 *      source path -> green/tea
 *      destination path -> . (i.e. our current dir)
 *
 * 3)Now calling renaming function and, if we've got an FS error,
 * printing the explanatory string.
 *
 * Note:
 * I'm trying to handle the exceptions via try-catch contruction.
 *
 * 4)Then returning to main function.
 *
 */
//

#include <filesystem>
#include <iostream>
#include <string>

namespace stdfs = std::filesystem;

const std::string CNF = ": command not found";
const std::string SCS = "Success";
const std::string HELP = "Available commands:\n"
                         "pwd   - print working directory\n"
                         "ls    - list working directory\n"
                         "cd    - change directory\n"
                         "info  - print file size\n"
                         "mkdir - make directory\n"
                         "rm    - recursively remove directory\n"
                         "cp    - recursively copy directory\n"
                         "mv    - move|rename directory|file\n"
                         "\n"
                         "help  - print this help\n"
                         "Usage sample:\n"
                         "cp foo /home/bar\n";

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
item_type(stdfs::directory_entry item) // internal func
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
    if(action[0] != '/') { // transforming the path into absolute one
        dest = session.curr_dir / action;
    } else {
        dest = action;
    } // the same construction can be seen in other functions
      // (yes, I know another way how to make an absolute paths)
    try {

        if(!stdfs::directory_entry(dest).exists()) {
            stdfs::create_directory(dest);
            std::cout << SCS;
        } else {
            std::cout << "The directory already exists." << std::endl;
        }
    } catch(stdfs::filesystem_error& error) {
        std::cout << error.what() << std::endl;
    }
}

void
info(session_data& session) // here could be your info
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
rm(session_data& session) // recursively removes
                          // dirs and subdirs
{
    std::string action;
    stdfs::path target;
    std::cin >> action;
    if(action[0] != '/') {
        target = session.curr_dir / action;
    } else {
        target = action;
    }
    try {
        stdfs::remove_all(target);
    } catch(stdfs::filesystem_error& error) {
        std::cout << error.what() << std::endl;
    }
}

void
cd(session_data& session)
{
    std::string action;
    stdfs::path dest;
    std::cin >> action;
    if(action[0] != '/') {
        dest = session.curr_dir / action;
    } else {
        dest = action;
    }
    try {
        stdfs::current_path(dest);
        session.curr_dir = stdfs::current_path();
    } catch(stdfs::filesystem_error& error) {
        std::cout << error.what() << std::endl;
        return;
    }
    session.ps1 = session.curr_dir.string() + std::string("$ ");
}

void
mv(session_data& session)
{
    std::string action;
    stdfs::path source;
    stdfs::path dest;
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
        stdfs::rename(source, dest);
        std::cout << SCS << " moving ";
        std::cout << source << " -> " << dest;
    } catch(stdfs::filesystem_error& error) {
        std::cout << error.what() << std::endl;
    }
}

void
help(session_data& session)
{
    std::cout << HELP << std::endl;
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
            std::cout << action << CNF << std::endl;
            std::cout << "Enter 'help' to see avaliable commands." << std::endl;
        }
        std::cin.clear();
        std::cout << session.ps1;
        std::cin >> action;
    }

    return 0;
}
