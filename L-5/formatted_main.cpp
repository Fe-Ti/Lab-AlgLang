#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

void
stupid_simple_print_func(int number)
{
    std::cout << number << " ";
}

int
main()
{
    std::unordered_multimap<int, std::string> umap = {
        { 0, "TEST" },     { -2, "TEST2" },     { 3, "HOMMef3" },
        { 0, "HOMMsef3" }, { -73, "HOMMawd3" }, { -3, "HOMM3sg" },
        { 3, "TESTwea3" }, { -3, "TESeT3" },    { 5, "TESTs3" },
        { 4, "HOMM4" }
    };
    umap.erase(0);
    umap.erase(3);
    umap.insert({ 6, "123" });
    umap.insert({ 6, "321" });
    umap.insert({ 6, "312" });
    umap.insert({ 6, "132" });
    std::map<int, std::string> simple_map;

    for (auto& i : umap) {
        simple_map[i.first] = i.second;
    }
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////
    // Part 2

    std::cout << std::count_if(simple_map.begin(),
                               simple_map.end(),
                               [](auto& i) { return i.first < 0; });
    std::cout << std::endl;

    std::vector<int> output_vec(simple_map.size());
    std::transform(simple_map.begin(),
                   simple_map.end(),
                   output_vec.begin(),
                   [](std::pair<const int, std::string> i) { return i.first; });

    std::for_each(
      output_vec.begin(), output_vec.end(), stupid_simple_print_func);
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////
    // Part 3

    int num_to_search = 6;
    auto position =
      std::find(output_vec.begin(), output_vec.end(), num_to_search);
    std::cout << std::distance(output_vec.begin(), position) << std::endl;
    std::cout << std::endl;

    std::replace_if(
      output_vec.begin(), output_vec.end(), [](int i) { return i < 0; }, -2);
    std::for_each(
      output_vec.begin(), output_vec.end(), stupid_simple_print_func);
    std::cout << std::endl;

    std::sort(output_vec.begin(), output_vec.end(), std::greater<int>());
    std::for_each(
      output_vec.begin(), output_vec.end(), stupid_simple_print_func);
    std::cout << std::endl;

    std::set<int> simple_set;
    for (int i : output_vec) {
        simple_set.insert(i);
    }
    std::for_each(
      simple_set.begin(), simple_set.end(), stupid_simple_print_func);

    return 0;
}
