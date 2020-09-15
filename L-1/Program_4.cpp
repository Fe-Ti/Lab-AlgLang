#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	
	std::cout << "Здравствуйте!\n";
	
	long int b = 0; 
	std::cout << "Введите b \n";
	std::cin >> b;
	
	long int result = 1;
	result <<= b ; // сдвиг 1 влево
	
	std::cout << "Ответ:\n";
	std::cout << "2**b = в десятичной СС " << std::dec << result << "\n и в восьмеричной" << std::oct << result;
	
	return 0;
	}
