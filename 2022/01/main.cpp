#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <cstdint>
#include <map>
#include <numeric>
#include <iterator>

#include "string_utils.h"

namespace fs = std::filesystem;

int main(int, char *[])
{
  constexpr bool readFile = false;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::vector<int> elves;

  int calories = 0;

  while (std::getline(infile, line))
  {
    utils::trim(line);
    if (line.empty())
    {
      elves.emplace_back(calories);
      calories = 0;
      continue;
    }
    calories += std::stoi(line);
  }

  if (calories != 0)
  {
    elves.emplace_back(calories);
    calories = 0;
  }

  auto maxElvinIter = std::max_element(elves.begin(), elves.end());

  std::cout << "---------------------" << std::endl;
  std::cout << "elf:" << std::distance(elves.begin(), maxElvinIter) + 1 << std::endl;
  std::cout << "carried calories:" << *maxElvinIter << std::endl;

  std::sort(elves.begin(), elves.end(), std::greater<int>());

  auto sum = elves[0] + elves[1] + elves[2];

  std::cout << "Top 3 calories:" << sum << std::endl;

  return 0;
}