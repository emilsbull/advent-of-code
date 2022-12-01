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

#include "string_utils.h"

namespace fs = std::filesystem;

int main(int, char *[])
{
  constexpr bool readFile = false;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::vector<int> kCal;

  int curentkCal = 0;

  while (std::getline(infile, line))
  {
    utils::trim(line);
    if (line.empty())
    {
      kCal.emplace_back(curentkCal);
      curentkCal = 0;
      continue;
    }

    curentkCal += std::stoi(line);
  }

  auto maxIdx = std::max_element(kCal.begin(), kCal.end());

  std::cout << "---------------------" << std::endl;
  std::cout << "element:" << std::distance(kCal.begin(), maxIdx)+1 << std::endl;
  std::cout << "value:" << *maxIdx << std::endl;
  return 0;
}