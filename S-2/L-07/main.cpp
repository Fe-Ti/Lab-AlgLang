// Copyright 2020 Fe-Ti <btm.007@mail.ru>

#include <chrono>
#include <ctime>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

std::mutex locker;

void
max_int_in_slice(const std::vector<int>& vec,
                 const unsigned long int& slice_begin,
                 const unsigned long int& slice_end,
                 int& buffer_cell)
{
    int max_int = vec[slice_begin];
    for(size_t i = slice_begin + 1; i < slice_end; ++i) {
        if(max_int < vec[i])  // if the i element is greater than our max
            max_int = vec[i]; // then our max is i element
    }

    std::lock_guard<std::mutex> lock(locker);
    // locking mutex for safety reasons
    buffer_cell = max_int; // writing max_int from the slice
    std::cout << "thread #" << std::this_thread::get_id() << " found ";
    std::cout << max_int << " as local max." << std::endl;
}

int
find_max_int_mt(const std::vector<int>& vec, const int t_count)
{
    if(vec.empty()) // empty vector protection
        return -1;

    int slice_size = vec.size() / t_count; // we need integer
    std::vector<int> buffer(t_count); // allocating memory for writing results
    std::vector<std::thread> thread_buf; // pointer array for handling threads

    for(int i = 0; i < t_count; ++i) {
        thread_buf.push_back(
          std::thread(max_int_in_slice,
                      vec,
                      slice_size * i,
                      slice_size * (i + 1),
                      std::ref(buffer[i]))); // allocating threads
    }

    for(int i = 0; i < t_count; ++i)
        thread_buf[i].join(); // waiting for every thread to complete the task

    int max_int = buffer[0];
    for(int i = 1; i < t_count; ++i) {
        if(max_int < buffer[i]) { // for each max comparing it with global max
            max_int = buffer[i];
        }
    }

    return max_int; // returning global max
}

int
find_max_int_st(const std::vector<int>& vec)
{
    if(vec.empty()) // empty vector protection
        return -1;

    int max_int = vec[0]; // setting max to vec[0]

    for(size_t i = 1; i < vec.size(); ++i) {
        if(max_int < vec[i]) // for each element comparing it with max
            max_int = vec[i];
    }

    return max_int; // returning max
}

int
main(int argc, char* argv[])
{
    int st; // singlethreaded max
    int mt; // multithreaded max
    int t_count;
    int64_t len;
    if(argc > 2) {
        t_count = std::atoi(argv[1]);
        len = std::atoi(argv[2]);
    } else {
        if(argc > 1) {
            t_count = std::atoi(argv[1]);
        } else {
            std::cout << "Enter thread count:" << std::endl;
            std::cin >> t_count;
        }
        std::cout << "Enter array length:" << std::endl;
        std::cin >> len;
    }
    // for(long int len = 4; len < 400000001; len *= 10) {
    std::cout << "-------------------------" << std::endl;
    std::cout << "length = " << len << std::endl;

    std::srand(std::time(nullptr));
    std::vector<int> vec;
    for(long int i = 0; i < len; ++i)
        vec.push_back(std::rand() % 10000000); // 0000000);

    auto start_st = std::chrono::steady_clock::now();
    st = find_max_int_st(vec);
    auto end_st = std::chrono::steady_clock::now();

    auto start_mt = std::chrono::steady_clock::now();
    mt = find_max_int_mt(vec, t_count);
    auto end_mt = std::chrono::steady_clock::now();

    auto stt =
      std::chrono::duration_cast<std::chrono::milliseconds>(end_st - start_st)
        .count();
    auto mtt =
      std::chrono::duration_cast<std::chrono::milliseconds>(end_mt - start_mt)
        .count();

    std::cout << "single threaded =+= multi threaded" << std::endl;
    std::cout << "QC       : " << st << "  =+=  " << mt << std::endl;
    std::cout << "time (ms): " << stt << "  =+=  " << mtt << std::endl;
    // }
    return 0;
}
