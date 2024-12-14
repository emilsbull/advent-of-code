#include <algorithm>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "utils/fileinput.h"

// Function to check if a report is safe
bool isSafeReport(const std::vector<int>& levels)
{
    bool increasing = true;
    bool decreasing = true;

    for (size_t i = 1; i < levels.size(); ++i) {
        int diff = levels[i] - levels[i - 1];
        if (std::abs(diff) > 3 || std::abs(diff) < 1)
            return false;  // Rule 2 violation

        if (diff < 0)
            increasing = false;  // Not increasing
        if (diff > 0)
            decreasing = false;  // Not decreasing
    }

    return increasing || decreasing;  // Must be strictly increasing or decreasing
}

// Function to check if a report can be made safe by removing one level
bool isSafeWithDampener(const std::vector<int>& levels)
{
    if (levels.size() < 3)
        return false;

    for (size_t i = 0; i < levels.size(); ++i) {
        std::vector<int> modifiedLevels;

        // Create a copy of levels excluding the current level
        for (size_t j = 0; j < levels.size(); ++j) {
            if (j != i) {
                modifiedLevels.push_back(levels[j]);
            }
        }

        // Check if the modified report is safe
        if (isSafeReport(modifiedLevels)) {
            return true;
        }
    }

    return false;
}

void puzzle(const std::vector<std::string>& commands)
{
    int safeReportCount = 0;
    int safeReportCountWithDampener = 0;
    for (const auto& line : commands) {
        // Read input line by line
        std::istringstream iss(line);
        std::vector<int> levels;
        int level = 0;

        // Parse levels from the current line
        while (iss >> level) {
            levels.push_back(level);
        }

        // Check if the report is safe
        if (isSafeReport(levels)) {
            ++safeReportCount;
        }
        if (isSafeWithDampener(levels)) {
            ++safeReportCountWithDampener;
        }
    }

    std::cout << "result a:" << safeReportCount << std::endl;
    std::cout << "result b:" << safeReportCountWithDampener << std::endl;
}

int main(int /*argc*/, char* argv[])
{
    auto startTime = std::chrono::high_resolution_clock::now();
    try {
        constexpr bool realPuzzle = true;
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
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "Execution Time: " << duration.count() << " ms" << std::endl;

    return 0;
}
