#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	
	std::cout << "Здравствуйте!\n";
	
	double x = 0.0;
	std::cout << "Введите x \n";
	std::cin >> x;
	
	long double reference = sin(x), result = 0.0;
	
	long int counter = 0, factorial = 1, stop = 100; 
	short int n = -1;
	
	
	for (counter=0; counter < stop; counter++){
	
		n = (-1)*n;
		
		factorial *= 2*counter+1;
		
		result += (long double) n*(pow(x,2*counter+1)/(factorial));
		
		std::cout << reference << " " << result << " " << counter << " " << factorial << "\n";
		
		}
	
	std::cout << "\nОтвет:" << result;
	std::cout << "\nРазность значений:" << reference-result;
	std::cout << "\nЧисло итераций:" << counter;
	
	return 0;
	}
