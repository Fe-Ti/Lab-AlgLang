#include <iostream>
#include <string>
#include <vector>

// Попытка сделать через регулярное выражение
// была провалена.

std::string replace_word(std::string &str_to_mod,
                         std::string word,
                         std::string replacement,
                         bool is_case_sensitive) {

    word = word;
    int w_size = word.size(),
        begin_pos = 0,
        end_pos = begin_pos + w_size;

    /*
    Сначала замена первого слова,
    затем в цикле послед.замена can
    и избежание "автоклава"
    */

    str_to_mod = str_to_mod.replace( begin_pos,
                                     w_size,
                                     replacement);

    while ((str_to_mod.find(word,end_pos)!=std::string::npos)) {
        begin_pos = str_to_mod.find(word, end_pos);
        end_pos=begin_pos+w_size;

        if (!((str_to_mod[end_pos]>='A')&&(str_to_mod[end_pos]<='Z')||(str_to_mod[end_pos]>='a')&&(str_to_mod[end_pos]<='z'))) {
            str_to_mod = str_to_mod.replace( begin_pos,
                                             w_size,
                                             replacement);
            }
        }

    return str_to_mod;
    }

int main () {
    int counter=0;

    std::string string_1="";
    std::cout << "Enter the string:\n";
    std::cin >> string_1;

    for (char i : string_1) {
        if (i=='1') {
            counter+=1;
            }
        }

    std::cout << "Amount of '1' / string length : " <<
              static_cast<double>(counter)/(string_1.size()) << std::endl;

    int i1=0,i2=0;
    std::cout << "Enter position:" << std::endl;
    std::cin >> i1 >> i2;
    if (i1<=i2) {
        std::cout << string_1.substr(i1,i2-i1+1) << std::endl;
        }

    std::string string_2 = "Can you can a can as a canner can can a can?";
    std::string inputed_string="";
    std::cout << "Enter the substring:\n";
    std::cin >> inputed_string;

    std::string word_to_filter = "can";

    replace_word(string_2,word_to_filter,inputed_string,0);

    std::cout << "Updated string:\n" << string_2;
    return 0;
    }
