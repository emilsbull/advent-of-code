#include <array>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "utils/fileinput.h"

template <class ForwardIt>
int firstDigit(ForwardIt first, ForwardIt last)
{
    auto isntdigit = [](char c) { return !isdigit(c); };
    for (auto it = first; it != last; ++it) {
        char c = *it;
        if (isntdigit(c))
            continue;
        return c - '0';
    }
    throw std::out_of_range("bla");
}

constexpr std::array<std::string_view, 19> digits = {"0",    "1",   "2",     "3",     "4",   "5",     "6",
                                                     "7",    "8",   "9",     "one",   "two", "three", "four",
                                                     "five", "six", "seven", "eight", "nine"};
int findDigit(std::string_view str)
{
    auto match = std::ranges::find_if(digits, [&](auto&& digit) { return str.starts_with(digit); });
    if (match == digits.end()) {
        return -1;
    }

    int64_t digit = std::distance(digits.begin(), match);
    if (digit >= 10) {
        return digit - 9;
    }
    return digit;
}

void puzzle(const std::vector<std::string>& commands)
{
    uint64_t sum = 0;
    for (auto command : commands) {
        int num = firstDigit(command.begin(), command.end()) * 10;
        num += firstDigit(command.rbegin(), command.rend());
        sum += num;
    }
    std::cout << "---------------------" << std::endl;
    std::cout << "output A:" << sum;
    std::cout << std::endl;

    sum = 0;
    for (const auto& command : commands) {
        int64_t first = -1;
        int64_t last = -1;
        for (size_t pos = 0; pos < command.size(); ++pos) {
            auto substr = command.substr(pos, command.size() - pos);
            if (int64_t digit = findDigit(substr); digit != -1) {
                if (first == -1) {
                    first = digit;
                }
                last = digit;
            }
        }
        sum += first * 10 + last;
    }
    std::cout << "---------------------" << std::endl;
    std::cout << "output b:" << sum;
    std::cout << std::endl;
}

int main(int /*argc*/, char* argv[])
{
    try {
        constexpr bool realPuzzle = false;
        const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

        std::string file_path = utils::getInputFilePath(argv[0], file);
        if (file_path.empty()) {
            std::cerr << "Error: Could not determine the input file path for " << file_path << ".\n";
            return 1;
        }
        // Open the file
        std::ifstream infile(file_path, std::ios::in);
        if (!infile) {
            std::cerr << "Error: Could not open file " << file_path << "\n";
            return 1;
        }

        if (!std::filesystem::exists(file_path)) {
            std::filesystem::path absolute_path = std::filesystem::absolute(file);
            std::cout << absolute_path << " not found" << std::endl;
            throw std::runtime_error("yoink");
        }

        const std::string path{file};
        std::string line;

        std::vector<std::string> commands;

        while (std::getline(infile, line)) {
            if (line.empty()) {
                continue;
            }
            commands.push_back(line);
        }

        puzzle(commands);
    } catch (std::exception& e) {
        std::cout << "oopsie:" << e.what() << std::endl;
    } catch (...) {
        std::cout << "sth went wrong" << std::endl;
    }
    return 0;
}
