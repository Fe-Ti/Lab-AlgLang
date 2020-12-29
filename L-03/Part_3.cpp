#include <iostream>
#include <vector>

int main (){
    unsigned int m=0;
    std::cout << "Enter m: ";
    std::cin >> m;

    std::vector<int> v{};
    int element = 0, summ = 0, it=0;
    for (int i=0;i<m;i++){
        std::cout << "Enter "<<i<<" element: " << std::endl;
        std::cin >> element;
        v.push_back(element);
        summ+=element;
    }
    v.push_back(m);
    summ+=m;

    for (int i : v ){
        std::cout << "Element: "<< i << std::endl;
    }
    std::cout << "The summ is " << summ << std::endl;

    for (int i : v){
        // std::cout << it << '\n';
        if (i == 0){
            // std::cout << it << '\n';
            v.erase(v.begin()+it);
            break;
            }
        it++;
    }
    it=0;
    for (int i : v ){
        std::cout << it << " element: "<< i << std::endl;
        it++;
    }

    return 0;
}
