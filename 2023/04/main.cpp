#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
#include <set>
#include <map>

#include <algorithm>
#include <functional>
#include <optional>
#include <cmath>

#include "array_utils.h"
#include "map_utils.h"
#include "string_utils.h"

std::pair<int, int> parse(const std::vector<std::string>& input)
{
    int sumA{0};

    for (auto& line : input) {
        std::string scrachboard = utils::splitString(line, ":").at(1);
        auto s = utils::splitString(scrachboard, "|");
        std::string numbersStr = s.at(0);
        std::string winningNumbersStr = s.at(1);

        int num{0};
        std::set<int> winningNumbers;
        // read set of winning numbers
        std::stringstream ss(winningNumbersStr);
        while (ss >> num) {
            winningNumbers.insert(num);
        }

        // read lottery numbers
        ss.clear();
        ss.str(numbersStr);
        int correctNumbers = 0;
        while (ss >> num) {
            // check if number is a winning number
            if (winningNumbers.contains(num))
                correctNumbers++;
        }

        // if any number is a winning number, get points
        if (correctNumbers > 0)
            sumA += std::pow(2, correctNumbers - 1);
    }

    // ##### evaluate

    // -------

    int sumB{0};

    return {sumA, sumB};
}

void puzzle(const std::vector<std::string>& commands)
{
    auto [resultA, resultB] = parse(commands);

    std::cout << "---------------------" << std::endl;
    std::cout << "output A:" << resultA;
    std::cout << std::endl;

    std::cout << "---------------------" << std::endl;
    std::cout << "output b:" << resultB;
    std::cout << std::endl;
}

int main(int, char*[])
{
    constexpr bool realPuzzle = true;
    const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

    const std::string path{file};
    std::ifstream infile(path, std::ios::in);
    std::string line;

    std::vector<std::string> commands;

    while (std::getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        commands.push_back(line);
    }

    puzzle(commands);
    return 0;
}
