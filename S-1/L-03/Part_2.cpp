#include <iostream>

int main (){
    unsigned int n=0;
    std::cout << "Enter n: ";
    std::cin >> n;

    int* dyn_array = new int [n];

    for (int i=0;i<n;i++){
        std::cout << "Enter "<<i<<" element: ";
        std::cin >> dyn_array[i];
    }
    for (int i=0;i<n;i++){
        std::cout << i << " element is " << dyn_array[i] << std::endl;
    }

    for (int i=0;i<n;i++){
        if (dyn_array[i]==0){
            dyn_array[i]=15;
        }
        std::cout << i << " element is " << dyn_array[i] << std::endl;
        }

    int k1=0, k2=0, summ=0;
    std::cin >> k1 >> k2;
    if (k1<=k2){
        for (int i=k1;i<=k2;i++){
            summ+=dyn_array[i];
            }
        }
    std::cout << "The summ is " << summ;

    delete[] dyn_array;
    return 0;

}
