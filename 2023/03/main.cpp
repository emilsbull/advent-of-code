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

                auto hasAdiacentSign = [colMax, rowMax, schematic](size_t row, size_t col) -> bool {
                    bool hit = false;

                    if (row > 0) {
                        if (col > 0) {
                            // o|_|_
                            // _|X|_
                            // _|_|_
                            hit |= isSign(schematic.at(row - 1).at(col - 1));
                        }
                        // _|o|_
                        // _|X|_
                        // _|_|_
                        hit |= isSign(schematic.at(row - 1).at(col));
                        if (col < colMax - 1) {
                            // _|_|o
                            // _|X|_
                            // _|_|_
                            hit |= isSign(schematic.at(row - 1).at(col + 1));
                        }
                    }

                    if (col > 0) {
                        // _|_|_
                        // o|X|_
                        // _|_|_
                        hit |= isSign(schematic[row][col - 1]);
                    }

                    if (col < colMax - 1) {
                        // _|_|_
                        // _|X|o
                        // _|_|_
                        hit |= isSign(schematic[row][col + 1]);
                    }

                    if (row < rowMax - 1) {
                        if (col > 0) {
                            // _|_|_
                            // _|X|_
                            // o|_|_
                            hit |= isSign(schematic[row + 1][col - 1]);
                        }
                        // _|_|_
                        // _|X|_
                        // _|o|_
                        hit |= isSign(schematic[row + 1][col]);
                        if (col < colMax - 1) {
                            // _|_|_
                            // _|X|_
                            // _|_|o
                            hit |= isSign(schematic[row + 1][col + 1]);
                        }
                    }

                    return hit;
                };

                auto& valid = number->isValid;

                valid |= hasAdiacentSign(rowCursor, colCursor);

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