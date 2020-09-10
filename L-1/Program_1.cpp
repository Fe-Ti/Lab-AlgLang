#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	long int x=0; 
	std::cout<<"Input x \n";
	std::cin >> x;
	long int result = 3*pow(x,5)+2*pow(x,3)+1; 
	std::cout << "The result of 3*pow(x,5)+2*pow(x,3)+1 is " << std::setprecision(3) << result;
	
	return 0;
	}
