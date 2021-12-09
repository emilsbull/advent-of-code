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

int exploreBasin(std::vector<std::vector<int>> &input, int i, int j)
{
  int size = 0;
  if (input[i][j] < 9)
  {
    input[i][j] = 100; // mark as explored
    size++;
    if ((j + 1U) < input[i].size())
    {
      size += exploreBasin(input, i, j + 1);
    }
    if (((int)j - 1) >= 0)
    {
      size += exploreBasin(input, i, j - 1);
    }
    if ((i + 1U) < input.size())
    {
      size += exploreBasin(input, i + 1, j);
    }
    if (((int)i - 1) >= 0)
    {
      size += exploreBasin(input, i - 1, j);
    }
  }
  return size;
}

int sizeOfBasin(std::vector<std::vector<int>> input, int x, int y)
{
  return exploreBasin(input, x, y);
}

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  std::vector<std::vector<int>> input;
  std::vector<int> basins;

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
        totalRisk += height + 1;
        basins.emplace_back(sizeOfBasin(input, i, j));
        std::cout << "Low[" << std::setw(2) << std::setfill(' ') << i << "][" << std::setw(2) << std::setfill(' ') << j << "]: " << height << " BasinSize: " << basins.back() << std::endl;
      }
    }
  }

  std::sort(basins.begin(), basins.end());

  auto rIter = basins.rbegin();
  auto result = 1;

  for (int i = 0; i < 3; ++i)
  {
    std::cout << "basin[" << i << "]: " << *rIter << std::endl;
    result *= *rIter;
    rIter++;
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "Basins: " << result << std::endl;
  std::cout << "Risk: " << totalRisk << std::endl;
  return 0;
}