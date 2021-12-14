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

template <typename key, typename value>
std::pair<key, value> mapMax(std::map<key, value> map)
{
  key retKey;
  value retVal = std::numeric_limits<value>::min();;
  for (auto [mk, mv] : map)
  {
    if (mv > retVal)
    {
      retVal = mv;
      retKey = mk;
    }
  }
  return {retKey, retVal};
}
template <typename key, typename value>
std::pair<key, value> mapMin(std::map<key, value> map)
{
  key retKey;
  value retVal = std::numeric_limits<value>::max();
  for (auto [mk, mv] : map)
  {
    if (mv < retVal)
    {
      retVal = mv;
      retKey = mk;
    }
  }
  return {retKey, retVal};
}

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  constexpr auto steps = 10;

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  bool readTemplate = true;

  std::vector<std::pair<std::size_t, std::size_t>> marked;
  std::vector<std::pair<std::string, std::size_t>> foldings;

  std::string polymer_template;
  std::map<std::string, std::string> substitute;

  while (std::getline(infile, line))
  {
    utils::trim(line);
    if (line.empty())
    {
      readTemplate = false;
      continue;
    }
    if (readTemplate)
    {
      polymer_template = utils::trim(line);
    }
    else
    {
      auto sString = utils::splitString(line, " -> ");
      substitute[sString[0]] = sString[1];
    }
  }
  std::cout << "polymer_template: " << polymer_template << std::endl;

  for (auto step = 0; step < steps; ++step)
  {
    for (auto i = 1u; i < polymer_template.size(); ++i)
    {
      auto pair = polymer_template.substr(i - 1, 2);
      for (auto [pattern, sub] : substitute)
      {
        if (pattern.compare(pair) == 0)
        {
          polymer_template.insert(i, sub);
          i += sub.size();
          break;
        }
      }
    }
  }

  std::map<char, int> count;
  for (auto c : polymer_template)
  {
    count[c]++;
  }
  for (auto [k, v] : count)
  {
    std::cout << k << ":" << v << std::endl;
  }

  auto [maxKey, maxVal] = mapMax(count);
  auto [minKey, minVal] = mapMin(count);

  std::cout << "---------------------" << std::endl;
  std::cout << "maxVal:" << maxVal << std::endl;
  std::cout << "minVal:" << minVal << std::endl;
  std::cout << "result:" << maxVal - minVal<< std::endl;
  return 0;
}