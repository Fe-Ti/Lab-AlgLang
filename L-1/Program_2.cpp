#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	unsigned int a=0; // В при любых целых $а прин. [0;2**32-1]
	std::cout<<"Input a \n";
	std::cin >> a;
	double result = 5*pow(3*a-2,0.5)-4*abs(a); 
	std::cout << "The result of 5*pow(3*a-2,0.5)-4*abs(a) is  "<< std::showpos << result;
	
	return 0;
	}
