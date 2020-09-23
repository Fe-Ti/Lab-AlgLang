#include <iostream>
#include <experimental/random>
#include <string>

int main (){
    int array[10];
    for (int i=0;i<10;i++){

        array[i]= std::experimental::randint(-10,10);
        std::cout << array[i] << " ";

    }
    std::cout << std::endl;

    int summ=0;
    for (int i=0;i<10;i++){
        std::cout << static_cast<double>(array[i])/array[9] << " ";
        summ+=array[i];
    }
    std::cout << static_cast<double>(summ)/array[9];
}
