#include <iostream>
#include <vector>
#include <ctime>

void print_vec(const std::vector<int>& vec)
{
    for (int i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

std::vector<int> odd_even_sort(std::vector<int>& vec)
{
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

void merge_chunk (std::vector<int>& vec, int left, int mid, int right)
{
    int it1 = 0;
    int it2 = 0;
    std::vector<int> result(right - left);

    while ((left + it1 < mid) && (mid + it2 < right)) {
        if (vec[left+it1] < vec[mid + it2]) {
            result[it1 + it2] = vec[left + it1];
            ++it1;
        } else {
            result[it1 + it2] = vec[mid + it2];
            ++it2;
        }
    }
    while (left + it1 < mid) {
        result[it1 + it2] = vec[left + it1];
        ++it1;
    }
    while (mid + it2 < right) {
        result[it1 + it2] = vec[mid + it2];
        ++it2;
    }
    for (size_t i = 0; i < it1+it2; i++){
        vec[left + i] = result[i];
    }
}

std::vector<int> merge_sort(std::vector<int>& vec)
{
    size_t vec_len = vec.size();
    for (size_t i = 1; i < vec_len; i *= 2) {
        for (size_t j = 0; j < vec_len - i; j += 2 * i) {
            merge_chunk(vec, j, j + i, std::min(j + 2 * i, vec_len));
        }
    }
    return vec;
}

std::vector<int> bitonic_sort(std::vector<int>& vec)
{
    return vec;
}

int main()
{
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
