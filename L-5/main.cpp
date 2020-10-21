#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

void
print_vec(const std::vector<int>& vec)
{
    for (int i : vec) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
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
    // for (std::pair<const int, std::string> i : umap) {
    std::map<int, std::string> simple_map;

    for (auto& i : umap) {
        simple_map[i.first] = i.second;
        //        std::cout << i.first << " " << i.second << std::endl;
    }
    std::cout << std::endl;

    ///////////////////////////////////////////////////////////////////////////////
    // Part 2
    //  for (auto& i : simple_map) {
    //    std::cout << i.first << " " << i.second << std::endl;
    //  }

    std::cout << std::count_if(simple_map.begin(),
                               simple_map.end(),
                               [](auto& i) { return i.first < 0; });
    std::cout << std::endl;

    std::vector<int> output_vec(simple_map.size());
    std::transform(simple_map.begin(),
                   simple_map.end(),
                   output_vec.begin(),
                   [](std::pair<const int, std::string> i) { return i.first; });
    print_vec(output_vec);
}
