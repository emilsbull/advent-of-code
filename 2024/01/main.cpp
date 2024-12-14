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

void puzzle(const std::vector<std::string>& commands)
{
    std::vector<int> leftList;
    std::vector<int> rightList;
    int result = 0;
    int resultb = 0;

    for (const auto& line : commands) {
    int left = 0;
    int right = 0;
        std::stringstream ss(line);
        ss >> left >> right;
        leftList.push_back(left);
        rightList.push_back(right);
    }

    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    for(auto i = 0U; i < leftList.size(); ++i) {
        result += std::abs(leftList[i] - rightList[i]);
    }

    std::cout << "result a:" << result << std::endl;
    
    for(int i : leftList) {
        resultb += i * std::count(rightList.begin(), rightList.end(), i);
    }
    std::cout << "result b:" << resultb << std::endl;
}

int main(int /*argc*/, char* argv[])
{
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
    return 0;
}
