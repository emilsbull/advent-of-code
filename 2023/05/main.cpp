#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
#include <set>
#include <map>

#include <algorithm>
#include <functional>
#include <optional>
#include <numeric>
#include <cmath>

#include "array_utils.h"
#include "map_utils.h"
#include "string_utils.h"

struct Seed {
    int64_t seed{0};
    bool mapped{false};

    friend std::istream &operator>>(std::istream &, Seed &);
};

std::istream &operator>>(std::istream &s, Seed &r)
{
    s >> r.seed;
    r.mapped = false;
    return s;
}

struct Range
{
    int64_t start;
    int64_t destination;
    int64_t length;

    friend std::istream &operator>>(std::istream &, Range &);

    bool contains(Seed v)
    {
        return (v.seed >= start) && (v.seed < start + length);
    }

    bool map(Seed& v)
    {
        if (contains(v) && !v.mapped) {
             v.seed = destination + (v.seed - start);
             v.mapped = true;
             return true;
        }
        return false;
    }
};

std::istream &operator>>(std::istream &s, Range &r)
{
    s >> r.destination >> r.start >> r.length;
    return s;
}

std::pair<int, int> parse(const std::vector<std::string> &input)
{
    // ##### evaluate

    int sumA{0};
    int sumB{0};

    // #######

    std::vector<Seed> seeds;

    enum class state
    {
        seeds,
        mappingHead,
        mapping
    } readingState = state::seeds;

    for (auto &line : input) {
        if (line.empty()) {
            readingState = state::mappingHead;
            continue;
        }

        switch (readingState) {
            case state::seeds: {
                auto seedsList = utils::splitString(line, ":");
                std::stringstream ss(seedsList.at(1));
                Seed seed;
                while (ss >> seed) {
                    seeds.push_back(seed);
                }
                readingState = state::mappingHead;
                break;
            }
            case state::mappingHead: {
                readingState = state::mapping;

                for (auto &seed : seeds) {
                    seed.mapped = false;
                    // std::cout << seed.seed << std::endl;
                }
                // std::cout << "----------" << std::endl;
                break;
            }
            case state::mapping: {
                std::stringstream ss(line);
                Range r;
                ss >> r;

                for (auto &seed : seeds) {
                    r.map(seed);
                }
                break;
            }
        }
    }

    auto aIterator = std::min_element(seeds.begin(), seeds.end(), [](const auto &a, const auto& b) -> bool {return a.seed < b.seed;});
    sumA = aIterator->seed;

    return {sumA, sumB};
}

void puzzle(const std::vector<std::string> &commands)
{
    auto [resultA, resultB] = parse(commands);

    std::cout << "---------------------" << std::endl;
    std::cout << "output A:" << resultA;
    std::cout << std::endl;

    std::cout << "---------------------" << std::endl;
    std::cout << "output b:" << resultB;
    std::cout << std::endl;
}

int main(int, char *[])
{
    constexpr bool realPuzzle = true;
    const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

    const std::string path{file};
    std::ifstream infile(path, std::ios::in);
    std::string line;

    std::vector<std::string> commands;

    while (std::getline(infile, line)) {
        commands.push_back(line);
    }

    puzzle(commands);
    return 0;
}
