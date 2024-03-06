#ifndef INPUT_HELPERS_H
#define INPUT_HELPERS_H

#include <vector>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <iostream>

namespace utils
{

    template <typename T>
    std::vector<T> getInput(std::string inputPath)
    {
        std::vector<T> data;
        std::ifstream infile(inputPath, std::ios::in);
        std::string line;

        if (infile.is_open()) {
            while (getline(infile, line)) {
                T element;
                std::stringstream input(line);
                while (input >> element)
                    data.push_back(element);
            }
            infile.close();
        } else {
            std::cout << "Unable to open file " << inputPath << std::endl;
        }

        return data;
    }

    std::vector<std::string> getInput(std::string inputPath)
    {
        std::vector<std::string> data;
        std::ifstream infile(inputPath, std::ios::in);
        std::string line;

        if (infile.is_open()) {
            while (getline(infile, line)) {
                data.push_back(line);
            }
            infile.close();
        } else {
            std::cout << "Unable to open file " << inputPath << std::endl;
        }

        return data;
    }

    std::vector<std::vector<char> > getInputGrid(std::string inputPath)
    {
        std::vector<std::vector<char> > data;
        std::ifstream infile(inputPath, std::ios::in);
        std::string line;

        if (infile.is_open()) {
            while (getline(infile, line)) {
                std::vector<char> row(line.begin(), line.end());
                data.push_back(row);
            }
            infile.close();
        } else {
            std::cout << "Unable to open file " << inputPath << std::endl;
        }

        return data;
    }

}  // namespace utils
#endif  // INPUT_HELPERS_H
