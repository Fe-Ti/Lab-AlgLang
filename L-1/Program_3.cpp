#include <iostream>
#include <iomanip>
#include <cmath>



int main() {
	bool k=0,l=0,m=0,n=0; 
	std::cout << "Input k,l,m,n splitting them with space \n";
	std::cin >>k>>l>>m>>n;
	bool result = l||(((m&&!n)||(!m&&n))&&(!k)); 
	std::cout << "The result of l||(m&&!n||!m&&n)&&!k \nis  "<< std::boolalpha << result;
	
	return 0;
	}
