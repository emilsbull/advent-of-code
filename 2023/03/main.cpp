#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
#include <set>
#include <map>

#include <algorithm>
#include <functional>
#include <optional>

#include "array_utils.h"
#include "map_utils.h"
#include "string_utils.h"

struct PartNumber
{
    int number{0};
    bool isValid{false};
};

bool isSign(char c)
{
    return !(std::isdigit(c) || (c == '.'));
}

std::pair<int, int> parse(const std::vector<std::string>& schematic)
{
    std::vector<PartNumber> numbers;
    std::map<std::pair<size_t, size_t>, size_t> numberAtlas;
    std::vector<std::pair<size_t, size_t> > gears;

    size_t rowMax = schematic.size();
    for (size_t rowCursor = 0; rowCursor <= rowMax; ++rowCursor) {
        std::optional<std::reference_wrapper<PartNumber> > number;

        auto curRow = schematic[rowCursor];
        size_t colMax = curRow.size();

        for (size_t colCursor = 0; colCursor <= colMax; ++colCursor) {
            char c = curRow[colCursor];
            if (std::isdigit(c)) {
                if (!number) {
                    numbers.emplace_back();
                    number = numbers.back();
                }
                numberAtlas[std::make_pair(rowCursor, colCursor)] = numbers.size() - 1;

                bool& hit = number->get().isValid;
                utils::visitAdiacent(rowCursor, colCursor, schematic, [&hit](auto c) { hit |= isSign(c); });

                number->get().number = number->get().number * 10 + c - '0';
            } else {
                if (number) {
                    // number completed
                    number.reset();
                }
                if (c == '*') {
                    gears.emplace_back(std::make_pair(rowCursor, colCursor));
                }
            }
        }
    }

    // ##### evaluate

    int sumA{0};

    for (auto& number : numbers) {
        if (number.isValid) {
            sumA += number.number;
        }
    }

    // -------

    int sumB{0};

    //utils::printMap(numberAtlas);

    for (auto [gearRow, gearCol] : gears) {
        std::set<size_t> adjacentNumbers;
        utils::adiacentIndices(gearRow, gearCol, schematic, [&numberAtlas, &adjacentNumbers](size_t r, size_t c) {
            auto coord = std::make_pair(r, c);

            if (numberAtlas.find(coord) != numberAtlas.end()) {
                adjacentNumbers.insert(numberAtlas[coord]);
            }
        });

        if (adjacentNumbers.size() == 2) {
            int temp = 1;
            for (auto idx : adjacentNumbers) {
                temp *= numbers[idx].number;
            }
            sumB += temp;
        }
    }

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