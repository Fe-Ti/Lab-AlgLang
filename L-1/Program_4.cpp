#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	long int b=0; 
	std::cout<<"Input b \n";
	std::cin >> b;
	long int result=1;
	result<<=b ; // moving 1 in left direction
	std::cout << "The result of 2**b is in dec " << std::dec << result << "\nin oct " << std::oct << result;
	
	return 0;
	}
