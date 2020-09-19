#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	
	std::cout << "Здравствуйте!\nТаблица ASCII\nСимвол == Код" << std::endl;
	////////////////////////////////////////////////////////////////////
	// Задача 1
	unsigned char ch1;
	
	for (ch1=0;ch1<=127;ch1++){
		// последовательный вывод символов таблицы
		std::cout << ch1 << " == " << static_cast<int>(ch1)  << std::endl;
		
		}
	////////////////////////////////////////////////////////////////////
	//  Задача 2
	char ch2 = 0;
	std::cout << "Введите символ" << std::endl;
	std::cin >> ch2;
	
	if ((ch2 >= 48)&&(ch2 <= 57)) {
		
		std::cout << "Введённый символ - цифра." << std::endl;
		
		}
	else {
		
		if (((ch2 >= 97)&&(ch2 <= 122))||((ch2 >= 65)&&(ch2 <= 90))){
			std::cout << "Введённый символ - буква." << std::endl;
			}
		else{
			std::cout << "Неизвестный символ." << std::endl;
			}
		
		}
	////////////////////////////////////////////////////////////////////
	// Задача 3
	
	uint64_t x_3 = 0; // unsigned long int
	
	std::cout << "Введите Х" << std::endl;
	std::cin >> x_3;
	double y = 0;
	
	switch (x_3 % 4){
		
		case 0 : {y = -1; break;}
		case 1 : {y = x_3; break;}
		case 2 : {y = 1/(static_cast<double>(x_3)); break;}
		case 3 : {y = -x_3; break;}
		
		default : { std::cout<<"Что-то пошло не так" << std::endl; return 1; } 
		}
	
	std::cout << "Ответ: " << std::endl;
	std::cout << y << std::endl;
	////////////////////////////////////////////////////////////////////
	// Задача 4 
	double x_4 = 0.0;
	std::cout << "Введите x " << std::endl;
	std::cin >> x_4;
	
	long double reference = sin(x_4), result = 0.0;
	long int counter = 0, factorial = 1, stop = 100; 
	short int n = -1;
	
	for (counter=0; counter < stop; counter++){
		
		n = (-1)*n; // обход pow(-1,counter)
		factorial *= 2*counter+1; // обход лишних расчётов (факториал)
		result += static_cast<double>(n*(pow(x_4,2*counter+1)/(factorial)));
		
		}
	
	std::cout << "Ответ:" << result << std::endl;
	std::cout << "Разность значений:" << reference-result << std::endl;
	std::cout << "Число итераций:" << counter << std::endl;
	
	return 0;
	}
