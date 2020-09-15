#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	
	std::cout << "Здравствуйте!\n";
	
	unsigned int a = 0; // В при любых целых $а прин. [0;2**32-1]
	std::cout << "Введите a\n";
	std::cin >> a;
	
	double result = 5*pow(3*a-2,0.5)-4*abs(a);
	std::cout << "Ответ:\n";
	std::cout << "5*pow(3*a-2,0.5)-4*abs(a) = "<< std::showpos << result;
	
	return 0;
	}
