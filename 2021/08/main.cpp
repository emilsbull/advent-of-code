#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <cstdint>
#include <bitset>
#include <regex>

#include "string_utils.h"

namespace fs = std::filesystem;

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  std::vector<std::vector<std::string>> input;

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;
  while (std::getline(infile, line))
  {
    auto split = utils::splitString(line, "|");
    input.emplace_back(utils::splitString(split.at(1), " "));
  }

  if (input.empty())
  {
    std::cerr << "PARSING ERROR";
    return -1;
  }

  auto ones = 0;
  auto sevens = 0;
  auto fours = 0;
  auto eights = 0;
  for (auto digits : input)
  {
    ones += count_if(digits.begin(), digits.end(), [](auto s)
                     { return s.size() == 2; });
    fours += count_if(digits.begin(), digits.end(), [](auto s)
                      { return s.size() == 4; });
    sevens += count_if(digits.begin(), digits.end(), [](auto s)
                       { return s.size() == 3; });
    eights += count_if(digits.begin(), digits.end(), [](auto s)
                       { return s.size() == 7; });
  }

  auto result = ones + fours + sevens + eights;
  std::cout << "ones: " << ones << std::endl;
  std::cout << "fours: " << fours << std::endl;
  std::cout << "sevens: " << sevens << std::endl;
  std::cout << "eights: " << eights << std::endl;
  std::cout << "---------------------" << std::endl;
  std::cout << "Sum: " << result << std::endl;
  return 0;
}