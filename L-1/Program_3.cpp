#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	
	std::cout << "Здравствуйте!\n";
	
	bool k = 0, l = 0, m = 0, n = 0; 
	std::cout << "Введите k, l, m, n, разделяя их пробелами\n";
	std::cin >> k >> l >> m >> n;
	
	bool result = l||(((m&&!n)||(!m&&n))&&(!k)); 
	std::cout << "Ответ:\n";
	std::cout << "l||(m&&!n||!m&&n)&&!k = " << std::boolalpha << result;
	
	return 0;
	}
