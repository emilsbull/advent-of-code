#include <fstream>
#include <iostream>
#include <vector>
#include <ranges>
#include <array>
#include <algorithm>
#include <sstream>
#include <string_view>
#include <optional>

#include "string_utils.h"
#include "array_utils.h"

struct PartNumber
{
    int number{0};
    bool isValid{false};
};

bool isSign(char c)
{
    return !(std::isdigit(c) || (c == '.'));
}

std::vector<PartNumber> parse(const std::vector<std::string>& schematic)
{
    std::vector<PartNumber> result;

    size_t rowMax = schematic.size();
    for (size_t rowCursor = 0; rowCursor <= rowMax; ++rowCursor) {
        auto curRow = schematic[rowCursor];
        size_t colMax = curRow.size();
        std::optional<PartNumber> number;
        for (size_t colCursor = 0; colCursor <= colMax; ++colCursor) {
            char c = curRow[colCursor];
            if (std::isdigit(c)) {
                if (!number) {
                    number = PartNumber();
                }

                bool& hit = number->isValid;
                utils::visitAdiacent(rowCursor, colCursor, schematic, [&hit](auto c) {
                    hit |= isSign(c);
                });

            } else if (number) {
                // number completed
                result.emplace_back(*number);
                number.reset();
            }

            if (number.has_value()) {
                auto& num = number->number;

                num *= 10;
                num += c - '0';
            }
        }
        if (number) {
            // number completed
            result.emplace_back(*number);
            number.reset();
        }
    }

    return result;
}

void puzzle(const std::vector<std::string>& commands)
{
    auto result = parse(commands);

    int sum = 0;

    for (auto& number : result) {
        if (number.isValid) {
            sum += number.number;
        }
    }

    std::cout << "---------------------" << std::endl;
    std::cout << "output A:" << sum;
    std::cout << std::endl;

    std::cout << "---------------------" << std::endl;
    std::cout << "output b:"
              << "tbd";
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