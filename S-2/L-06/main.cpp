// Copyright 2020-2021 Fe-Ti <btm.007@mail.ru>

#include <chrono>
#include <ctime>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

template<typename T>
std::ostream&
operator<<(std::ostream& out, const std::vector<T>& vec)
{
    for(const T& i : vec) {
        out << i << " ";
    }
    return out;
}

const size_t LIMIT = 2;

bool
comp(int64_t& a, int64_t& b)
{
    return a > b;
}

std::mutex locker;

void
merge(std::vector<int64_t>& vec,
      const size_t& start_pos,
      const size_t& end_pos,
      size_t& t_lim,
      const size_t& s_lim)
{
    if(end_pos - start_pos + 1 > LIMIT) {

        size_t offset = (end_pos - start_pos) / 2;
        size_t p0_start_pos = start_pos;
        size_t p0_end_pos = start_pos + offset;
        size_t p1_start_pos = p0_end_pos + 1;
        size_t p1_end_pos = end_pos;
        if(t_lim > 0 && end_pos - start_pos + 1 < s_lim) {
            locker.lock();
            --t_lim;
            locker.unlock();
            std::thread p0t(merge,
                            std::ref(vec),
                            p0_start_pos,
                            p0_end_pos,
                            std::ref(t_lim),
                            s_lim);
            merge(vec, p0_start_pos, p0_end_pos, t_lim, s_lim);
            p0t.join();
            locker.lock();
            ++t_lim;
            locker.unlock();
        } else {
            merge(vec, p0_start_pos, p0_end_pos, t_lim, s_lim);
            merge(vec, p1_start_pos, p1_end_pos, t_lim, s_lim);
        }
        std::vector<int64_t> buff_v(end_pos - start_pos + 1);
        size_t bcounter = 0;
        size_t i = p0_start_pos;
        size_t offseted_i = p1_start_pos;
        while(bcounter < buff_v.size()) {
            if(i <= p0_end_pos && offseted_i <= p1_end_pos) {
                // std::cout << vec[i] << "<=>" << vec[offseted_i] << std::endl;
                if(comp(vec[i], vec[offseted_i])) {
                    buff_v[bcounter] = vec[i];
                    ++i;
                } else {
                    buff_v[bcounter] = vec[offseted_i];
                    ++offseted_i;
                }
            } else {
                // std::cout << "copying the rest...";
                // if(i <= p0_end_pos)
                for(; i <= p0_end_pos; ++i) {
                    buff_v[bcounter] = vec[i];
                    ++bcounter;
                    // std::cout << "i" << vec[i];
                }
                // else if(offseted_i <= p1_end_pos)
                for(; offseted_i <= p1_end_pos; ++offseted_i) {
                    buff_v[bcounter] = vec[offseted_i];
                    ++bcounter;
                    // std::cout << "o" << vec[offseted_i];
                }
                // std::cout << std::endl;
                break;
            }
            ++bcounter;
        }
        for(i = 0; i <= end_pos - start_pos; ++i) {
            vec[i + start_pos] = buff_v[i];
        }
        // std::cout << buff_v << std::endl;
    } else {
        if(!comp(vec[start_pos], vec[end_pos])) {
            std::swap(vec[start_pos], vec[end_pos]);
        }
    }
}
template<typename T>
std::string
check_result(std::vector<T> v)
{
    for(size_t i = 1; i < v.size(); ++i) {
        if(comp(v[i], v[i - 1])) {
            return std::string("Error on " + std::to_string(i) + " position!");
        }
    }
    return std::string("No errors detected.");
}

int
main(int argc, char** argv)
{
    size_t elem_count;
    size_t t_count;
    size_t s_lim;
    if(argc > 2) {
        elem_count = std::atoi(argv[1]);
        t_count = std::atoi(argv[2]);

    } else {
        if(argc > 1) {
            elem_count = std::atoi(argv[1]);
        } else {
            std::cout << "Enter element count:" << std::endl;
            std::cin >> elem_count;
        }
        std::cout << "Enter thread count:" << std::endl;
        std::cin >> t_count;
    }
    if(argc > 3) {
        s_lim = std::atoi(argv[3]);
    } else {
        std::cout << "Enter block size:" << std::endl;
        std::cin >> s_lim;
    }

    std::srand(std::time(nullptr));
    std::vector<int64_t> vec;
    for(size_t i = 0; i < elem_count; ++i)
        vec.push_back(std::rand() % 5000);
    std::vector<int64_t> ref_vec = vec;

    auto start_mt = std::chrono::steady_clock::now();
    merge(vec, 0, elem_count - 1, t_count, s_lim); //, elem_count);
    auto end_mt = std::chrono::steady_clock::now();
    auto mtt =
      std::chrono::duration_cast<std::chrono::microseconds>(end_mt - start_mt)
        .count();

    if(vec.size() < 101) {
        std::cout << "QC_b: " << ref_vec << std::endl;
        std::cout << "QC_a: " << vec << std::endl;
    }
    std::cout << "Time........: " << mtt << " us" << std::endl;
    std::cout << "Vector size.: " << vec.size() << " elements" << std::endl;
    std::cout << "Block size..: " << s_lim << " elements" << std::endl;
    std::cout << "Thread count: " << t_count << std::endl;
    std::cout << "Result......: " << check_result(vec) << std::endl;
    std::cout << std::endl;

    return 0;
}
