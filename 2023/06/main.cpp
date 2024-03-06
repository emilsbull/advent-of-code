#include <sstream>
#include <vector>
#include <cmath>

#include "string_utils.h"
#include "input_helpers.h"

namespace formula
{
    uint64_t count_solutions(int64_t T_max, int64_t distance)
    {
        // The boat will travel:
        //    distance = T_hold * (T_max - T_hold)
        // Need to solve:
        //    -1 * T_hold * T_hold + T_max * T_hold > distance
        // find 0 crossing
        //    -1 * T_hold * T_hold + T_max * T_hold - distance == 0
        // Reminder: a*x^2 + b*x + c
        // Solutions: (-b +- sqrt(b*b-4ac)) / 2a

        double max = (-T_max - std::sqrt(T_max * T_max - 4 * (-1) * (-distance))) / (2 * (-1));
        double min = (-T_max + std::sqrt(T_max * T_max - 4 * (-1) * (-distance))) / (2 * (-1));
        return std::floor(std::nexttoward(max, min)) - std::ceil(std::nexttoward(min, max)) + 1;
    }
}  // namespace formula

int main()
{
    int64_t part1 = 0;
    int64_t part2 = 0;

    constexpr bool realPuzzle = true;
    const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

    std::vector<std::string> input = utils::getInput(file);
    if(input.size() < 2) {
        std::cout << "error parsing input size: " << input.size() << std::endl;
    }

    {
        // part 1
        auto toNumbers = [](const std::string& line) -> std::vector<uint64_t> {
            std::vector<uint64_t> numbers;
            auto numIn = utils::splitString(line, ":").at(1);

            std::istringstream iss{numIn};

            uint64_t x;
            while (iss >> x) {
                numbers.push_back(x);
            }
            return numbers;
        };

        std::vector<uint64_t> times = toNumbers(input[0]);
        std::vector<uint64_t> distances = toNumbers(input[1]);

        uint64_t p{1};
        for (size_t i = 0; i < times.size(); ++i) {
            p *= formula::count_solutions(times[i], distances[i]);
        }
        part1 = p;
    }

    {
        auto toNumber = [](const std::string& line) -> uint64_t {
            uint64_t n{};
            for (const auto c : line) {
                if (std::isdigit(c)) {
                    n = n * 10 + c - '0';
                }
            }
            return n;
        };

        auto time = toNumber(input[0]);
        auto distance = toNumber(input[1]);
        
        part2 = formula::count_solutions(time, distance);
    }

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;
}
