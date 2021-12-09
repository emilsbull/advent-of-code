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

  std::vector<std::vector<int>> input;

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;
  while (std::getline(infile, line))
  {
    utils::trim(line);
    input.emplace_back();
    for (auto number : line)
    {
      input.back().emplace_back(number - '0');
    }
  }

  if (input.empty())
  {
    std::cerr << "PARSING ERROR";
    return -1;
  }

  std::cout << "Size: (" << input.size() << "|" << input.at(0).size() << ")" << std::endl;

  int totalRisk = 0;
  for (auto i = 0U; i < input.size(); ++i)
  {
    for (auto j = 0U; j < input[i].size(); ++j)
    {
      int height = input[i][j];
      bool low = true;
      if ((j + 1U) < input[i].size())
      {
        low &= (height < input[i][j + 1]);
      }
      if (((int)j - 1) >= 0)
      {
        low &= (height < input[i][j - 1]);
      }
      if ((i + 1U) < input.size())
      {
        low &= (height < input[i + 1][j]);
      }
      if (((int)i - 1) >= 0)
      {
        low &= (height < input[i - 1][j]);
      }

      if (low)
      {
        std::cout << "Low[" << std::setw(2) << std::setfill(' ') << i << "][" << std::setw(2) << std::setfill(' ') << j << "]: " << height << std::endl;
        totalRisk += height + 1;
      }
    }
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "Risk: " << totalRisk << std::endl;
  return 0;
}