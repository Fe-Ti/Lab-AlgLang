#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    std::unordered_multimap<int, std::string> umap = {
        { 0, "TEST" },
        { 2, "TEST2" },
        { 3, "HOMM3" },
        { 4, "HOMM4" }
    };
    umap.erase(0);
    umap.erase(3);
    umap.insert({ 6, "123" });
    umap.insert({ 6, "321" });
    umap.insert({ 6, "312" });
    umap.insert({ 6, "132" });
    for (std::pair<const int, std::string> i : umap) {
        std::cout << i.first << " " << i.second << std::endl;
    }
}
