#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
	int f=0, d=0, c=0, e=0; 
	std::cout << "Input f,d,c,e splitting them with space \n";
	std::cin >>f>>d>>c>>e;
	int result = (~(f|d))&(((~c)&e)|((~e)&c)); 
	std::cout << "The result of (~(f|d))&(((~c)&e)|((~e)&c)) \nis  "<< std::hex << result;
	
	return 0;
	}
