#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	
	std::cout << "Здравствуйте!\n";
	
	long int x = 0; 
	std::cout << "Введите x\n";
	std::cin >> x;
	
	double result = (double) 3*pow(x,5)+2*pow(x,3)+1;
	std::cout << "Ответ:\n";
	std::cout << "3*pow(x,5)+2*pow(x,3)+1 = " << std::setprecision(3) << result;
	
	return 0;
	}
