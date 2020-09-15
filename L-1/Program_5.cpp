#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	
	std::cout << "Здравствуйте!\n";
	
	int f = 0, d = 0, c = 0, e = 0;
	std::cout << "Введите числа f, d, c, e, разделяя их пробелом.\n";
	std::cin >> f >> d >> c >> e;
	
	int result = (~( f | d )) & (( (~c) & e )|( (~e) & c )); 
	
	std::cout << "Ответ:\n";
	std::cout << "(~(f|d))&(((~c)&e)|((~e)&c)) = "<< std::hex << result;
	
	return 0;
	}
