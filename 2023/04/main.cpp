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

#include "utils/array_utils.h"
#include "utils/map_utils.h"
#include "utils/string_utils.h"
#include "utils/fileinput.h"

std::pair<int, int> parse(const std::vector<std::string>& input)
{
    // ##### evaluate

    int sumA{0};

    // -------

    int sumB{0};

    std::vector<int> amountCards(input.size(), 1);

    for (auto& line : input) {
        auto firstSplit = utils::splitString(line, ":");

        int cardNo;
        std::string dummy;
        std::stringstream ss(firstSplit.at(0));
        ss >> dummy >> cardNo;

        std::string scrachboard = firstSplit.at(1);
        auto s = utils::splitString(scrachboard, "|");
        std::string numbersStr = s.at(0);
        std::string winningNumbersStr = s.at(1);

        int num{0};
        std::set<int> winningNumbers;
        // read set of winning numbers
        ss.clear();
        ss.str(winningNumbersStr);
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

        // [b] how many of the current cards do i have?
        int amountCurrentCards = amountCards[cardNo-1];
        for(int i = 0; i < correctNumbers; ++i) {
            // [b] add to the subsequent cards
            amountCards[cardNo + i] += amountCurrentCards;
        }
    }

    sumB = std::accumulate(amountCards.begin(), amountCards.end(), 0);

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

int main(int /*argc*/, char* argv[])
{
    constexpr bool realPuzzle = true;
    const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

    std::string file_path = utils::getInputFilePath(argv[0], file);
    if (file_path.empty()) {
        std::cerr << "Error: Could not determine the input file path for " << file_path << ".\n";
        return 1;
    }
    std::ifstream infile(file_path, std::ios::in);
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
