#include <iostream>
//#include <experimental/random>
#include <string>
#include <ctime>

int main (){
    std::srand(std::time(nullptr));
    int s_array[10];
    std::cout << "s_array:" << std::endl;
    for (int i=0;i<10;i++){
        //s_array[i]= std::experimental::randint(-10,10);
        s_array[i]= std::rand()%21 - 10;
        std::cout << s_array[i] << " ";
    }
    std::cout << std::endl << "s_array[i]/s_array[9]:" << std::endl;

    int summ=0;
    for (int i=0;i<10;i++){
        std::cout << static_cast<double>(s_array[i])/s_array[9] << " ";
        summ+=s_array[i];
    }
    std::cout << std::endl << "summ(s_array)/s_array[9]:" << static_cast<double>(summ)/s_array[9];
    return 0;

}
