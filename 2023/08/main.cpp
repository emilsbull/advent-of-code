#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "utils/fileinput.h"
#include "utils/input_helpers.h"
#include "utils/map_utils.h"
#include "utils/string_utils.h"

int main(int /*argc*/, char* argv[])
{
    constexpr bool realPuzzle = true;
    const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

    std::string file_path = utils::getInputFilePath(argv[0], file);
    if (file_path.empty()) {
        std::cerr << "Error: Could not determine the input file path for " << file_path << ".\n";
        return 1;
    }

    int64_t part1 = 0;
    int64_t part2 = 0;

    std::vector<std::string> input = utils::getInput(file_path);
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
        while (currentNode != "ZZZ") {
            auto action = navigation[cursor++];
            if (cursor >= navigation.size())
                cursor = 0u;
            if (action == 'L')
                currentNode = tree[currentNode].first;
            else
                currentNode = tree[currentNode].second;
            iteration++;
        }
        part1 = iteration;
    }

    {
        // part 2
        std::vector<std::string> startNodes;
        std::vector<std::string> endNodes;
        for (auto [key, _] : tree) {
            if (key[2] == 'A') {
                startNodes.push_back(key);
            }
            if (key[2] == 'Z') {
                endNodes.push_back(key);
            }
        }

        std::vector<int> cycles(startNodes.size());
        auto cIdx = 0u;

        for (const auto& start : startNodes) {
            std::string currentNode = start;
            auto cursor = 0u;
            while (std::ranges::find(endNodes, currentNode) == endNodes.end()) {
                auto action = navigation[cursor++];
                if (cursor >= navigation.size())
                    cursor = 0u;
                if (action == 'L')
                    currentNode = tree[currentNode].first;
                else
                    currentNode = tree[currentNode].second;
                cycles[cIdx]++;
            }
            cIdx++;
        }
        part2 = 1;
        for (int& cycle : cycles) {
            part2 = std::lcm(part2, cycle);
        }
    }

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
}
