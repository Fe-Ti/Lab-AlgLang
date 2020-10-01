#include <iostream>
#include <vector>
#include <ctime>

void print_vec(const std::vector<int>& vec) {
    for (int i : vec) {
        std::cout << i << " ";
        }
    std::cout << std::endl;
    }

std::vector<int> odd_even_sort(std::vector<int>& vec) {
    int vec_len = vec.size(), is_vec_sorted = 0;
    while (!(is_vec_sorted)) {
        is_vec_sorted = 1;
        for (int i=1; i < vec_len - 1; i += 2) {
            if (vec[i] > vec[i + 1]) {
                vec[i] += vec[i + 1];
                vec[i+1] = vec[i]-vec[i + 1];
                vec[i] = vec[i] - vec[i + 1];
                is_vec_sorted = 0;
                }
            }
        for (int i=0; i < vec_len - 1; i += 2) {
            if (vec[i] > vec[i + 1]) {
                vec[i] += vec[i + 1];
                vec[i+1] = vec[i]-vec[i + 1];
                vec[i] = vec[i] - vec[i + 1];
                is_vec_sorted = 0;
                }
            }
        }
    return vec;
    }

std::vector<int> merge_sort(std::vector<int>& vec) {
    int vec_len = vec.size(),is_vec_sorted = 0, step = 1;
    for (int i = 0; i < vec_len; i++) {
        for (int j = 1; j < vec_len; j+=) {

            }
        }
    return vec;
    }

std::vector<int> bitonic_sort(std::vector<int>& vec) {

    return vec;
    }

int main() {
    std::srand(std::time(nullptr));
    int amount=10, some_integer=0;
    // some_integer - переменная для ввода/вывода значений
    std::vector<int> vec{};
    for (int i=0; i<amount; ++i) {
        vec.push_back(std::rand()%201 - 100);
        }
    std::cout << "Enter sort type {0,1,2} " << std::endl;
    std::cin >> some_integer;

    switch (some_integer) {
        case 0: {
            odd_even_sort(vec);
            break;
            }
        case 1: {
            merge_sort(vec);
            break;
            }
        case 2: {
            bitonic_sort(vec);
            break;
            }
        }
    print_vec(vec);
    return 0;
    }
