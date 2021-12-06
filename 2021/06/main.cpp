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

namespace fs = std::filesystem;

int main(int, char *[])
{
  constexpr bool readFile = true;
  constexpr int days = 80;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  std::array<long long int, 10> lanternfishes;
  lanternfishes.fill(0);

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
      auto fishTimer = std::atoi(substr.c_str());
      lanternfishes[fishTimer]++;
    }
  }

  std::cout << "             0     1     2     3     4     5     6     7     8     9" << std::endl;
  std::cout << "Day[" << std::setfill(' ') << std::setw(3) << 0 << "]";
  for (auto fish : lanternfishes)
  {
    std::cout << std::setfill(' ') << std::setw(6) << fish;
  }
  std::cout << std::endl;
  
  for (int i = 0; i < days; i++)
  {
    auto fishExplode = lanternfishes[0];
    lanternfishes[7] += fishExplode;
    lanternfishes[9] = fishExplode;
    lanternfishes[0] = 0;

    for (auto i = 1U; i < lanternfishes.size(); ++i)
    {
      std::swap(lanternfishes[i - 1], lanternfishes[i]);
    }
    
    std::cout << "Day[" << std::setfill(' ') << std::setw(3) << i + 1 << "]";
    for (auto fish : lanternfishes)
    {
      std::cout << std::setfill(' ') << std::setw(6) << fish;
    }
    std::cout << std::endl;
  }

  auto result = 0;
  for (auto fish : lanternfishes)
  {
    result += fish;
  }

  std::cout << "Result: " << result << std::endl;
  return 0;
}