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
#include <algorithm>

namespace fs = std::filesystem;

uint64_t getFuel(const std::vector<int> &input, int pos)
{
  uint64_t fuel = 0;

  for (auto crab : input)
  {
    auto distance = std::abs(crab - pos);
    for (auto i = 1; i <= distance; i++)
    {
      fuel += i;
    }
  }

  return fuel;
}

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  std::vector<int> input;

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;
  while (std::getline(infile, line))
  {
    std::stringstream sstream(line);
    while (sstream.good())
    {
      std::string substr;
      std::getline(sstream, substr, ',');
      auto val = std::atoi(substr.c_str());
      input.push_back(val);
    }
  }

  int min = *std::min_element(input.begin(), input.end());
  int max = *std::max_element(input.begin(), input.end());

  auto cheapest = min;
  auto fuel = getFuel(input, cheapest);

  for (auto i = min + 1; i <= max; ++i)
  {
    auto tempFuel = getFuel(input, i);
    if (tempFuel < fuel)
    {
      fuel = tempFuel;
      cheapest = i;
    }
  }

  std::cout << "cheapest pos: " << cheapest << std::endl;
  std::cout << "Fuel Cost: " << fuel << std::endl;
  return 0;
}