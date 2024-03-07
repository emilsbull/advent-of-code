#include <algorithm>
#include <array>
#include <cmath>
#include <istream>
#include <map>
#include <sstream>
#include <utility>
#include <vector>

#include "input_helpers.h"
#include "map_utils.h"
#include "string_utils.h"

int main()
{
    int64_t part1 = 0;
    int64_t part2 = 0;

    constexpr bool realPuzzle = true;
    const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

    std::vector<std::string> input = utils::getInput(file);
    std::map<std::string, std::pair<std::string, std::string>> tree;
    std::string navigation = input.front();

    for (auto i = 2u; i < input.size(); ++i) {
        auto node = input[i].substr(0, 3);
        auto l = input[i].substr(7, 3);
        auto r = input[i].substr(12, 3);
        tree[node] = std::pair(l, r);
    }

    {
        // part 1
        std::string currentNode = "AAA";
        auto iteration = 0;
        auto cursor = 0u;
        while (currentNode.compare("ZZZ") != 0) {
            auto action = navigation[cursor++];
            if (cursor >= navigation.size())
                cursor = 0u;
            if(action == 'L')
            currentNode = tree[currentNode].first;
            else 
            currentNode = tree[currentNode].second;
            iteration++;
        }
        part1 = iteration;
    }

    {
        // part 2
    }

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
}
