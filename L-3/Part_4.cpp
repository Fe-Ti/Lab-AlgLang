#include <iostream>
#include <string>

int main (){
    int counter=0;

    std::string string_1="";
    std::cout << "Enter the string:\n";
    std::cin >> string_1;

    for (char i : string_1){
        if (i=='1'){counter+=1;}
    }
    std::cout << "Amount of '1' / string length : " << static_cast<double>(counter)/(string_1.size()) << std::endl;

    int i1=0,i2=0;
    std::cin >> i1 >> i2;
    if (i1<=i2){
        std::cout << string_1.substr(i1,i2-i1+1) << std::endl;
    }
    string_1 = "Can you can a can as a canner can can a can?";
    std::string inputed_string="";
    std::cout << "Enter the substring:\n";
    std::cin >> inputed_string;


// TODO
    int begin_of_can = string_1.find(" can");
    std::cout<< begin_of_can << std::endl;
    while (begin_of_can!=std::string::npos){
        string_1.replace(begin_of_can,begin_of_can+3,inputed_string);
        begin_of_can = string_1.find(" can ");
    }

    begin_of_can = string_1.find("Can ");
    string_1.replace(begin_of_can,begin_of_can+3,inputed_string);
    begin_of_can = string_1.find("can?");
    string_1.replace(begin_of_can,begin_of_can+3,inputed_string);
// TODO

    std::cout << "Updated string:\n" << string_1;
    return 0;
}
