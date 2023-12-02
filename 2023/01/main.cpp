#include <fstream>
#include <iostream>
#include <vector>
#include <ranges>
#include <array>
#include <algorithm>

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
    if (match == digits.end())
        return -1;

    int64_t digit = std::distance(digits.begin(), match);
    if (digit >= 10)
        return digit - 9;
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
    for (auto command : commands) {
        int64_t first = -1;
        int64_t last = -1;
        for (size_t  pos = 0; pos < command.size(); ++pos) {
            auto substr = command.substr(pos, command.size() - pos);
            if (int64_t digit = findDigit(substr); digit != -1) {
                if (first == -1)
                    first = digit;
                last = digit;
            }
        }
        sum += first * 10 + last;
    }
    std::cout << "---------------------" << std::endl;
    std::cout << "output b:" << sum;
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