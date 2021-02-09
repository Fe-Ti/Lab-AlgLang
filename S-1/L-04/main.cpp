#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

const bool INCR = true;
const bool DECR = false;

void
print_vec(const vector<int>& vec)
{
    for(int i : vec) {
        cout << i << ", ";
    }
    cout << endl;
}

vector<int>
odd_even_sort(vector<int>& vec)
{
    int vec_len = vec.size(), is_vec_sorted = 0;
    while(!(is_vec_sorted)) {
        is_vec_sorted = 1;
        for(int i = 1; i < vec_len - 1; i += 2) {
            if(vec[i] > vec[i + 1]) {
                vec[i] += vec[i + 1];
                vec[i + 1] = vec[i] - vec[i + 1];
                vec[i] = vec[i] - vec[i + 1];
                is_vec_sorted = 0;
            }
        }
        for(int i = 0; i < vec_len - 1; i += 2) {
            if(vec[i] > vec[i + 1]) {
                vec[i] += vec[i + 1];
                vec[i + 1] = vec[i] - vec[i + 1];
                vec[i] = vec[i] - vec[i + 1];
                is_vec_sorted = 0;
            }
        }
    }
    return vec;
}

void
merge_chunk(vector<int>& vec, int left, int mid, int right)
{
    int it1 = 0;
    int it2 = 0;
    vector<int> result(right - left);

    while((left + it1 < mid) && (mid + it2 < right)) {
        if(vec[left + it1] < vec[mid + it2]) {
            result[it1 + it2] = vec[left + it1];
            ++it1;
        } else {
            result[it1 + it2] = vec[mid + it2];
            ++it2;
        }
    }
    while(left + it1 < mid) {
        result[it1 + it2] = vec[left + it1];
        ++it1;
    }
    while(mid + it2 < right) {
        result[it1 + it2] = vec[mid + it2];
        ++it2;
    }
    for(size_t i = 0; i < it1 + it2; i++) {
        vec[left + i] = result[i];
    }
}

vector<int>
merge_sort(vector<int>& vec)
{
    size_t vec_len = vec.size();
    for(size_t i = 1; i < vec_len; i *= 2) {
        for(size_t j = 0; j < vec_len - i; j += 2 * i) {
            merge_chunk(vec, j, j + i, min(j + 2 * i, vec_len));
        }
    }
    return vec;
}

void
bt_comswap(vector<int>& vec, const int& i, const int& j, const bool direction)
{
    if(direction == (vec[i] > vec[j]))
        swap(vec[i], vec[j]);
}

void
bt_merge(vector<int>& vec,
         const int& low,
         const int& curr_size,
         const bool& direction)
{
    if(curr_size > 1) {
        int next_size = curr_size / 2;
        for(int i = low; i < low + next_size; ++i)
            bt_comswap(vec, i, i + next_size, direction);
        bt_merge(vec, low, next_size, direction);
        bt_merge(vec, low + next_size, next_size, direction);
    }
}

void
bitonic_sort(vector<int>& vec,
             const int& low,
             const int& curr_size,
             const bool& direction)
{
    if(curr_size > 1) {
        int next_size = curr_size / 2;
        bitonic_sort(vec, low, next_size, INCR);
        bitonic_sort(vec, low + next_size, next_size, DECR);
        bt_merge(vec, low, curr_size, direction);
    }
}

vector<int>
run_bitonic_sort(vector<int>& vec)
{
    cout << "Work in progress" << endl;
    bitonic_sort(vec, 0, vec.size(), INCR);
    return vec;
}

int
main()
{
    srand(time(nullptr));
    int amount = 16, some_integer = 0;
    // some_integer - переменная для ввода/вывода значений
    vector<int> vec;
    for(int i = 0; i < amount; ++i) {
        vec.push_back(rand() % 201 - 100);
    }
    cout << "Enter sort type {0,1,2} " << endl;
    cin >> some_integer;

    switch(some_integer) {
        case 0: {
            odd_even_sort(vec);
            break;
        }
        case 1: {
            merge_sort(vec);
            break;
        }
        case 2: {
            run_bitonic_sort(vec);
            break;
        }
    }
    print_vec(vec);
    return 0;
}
