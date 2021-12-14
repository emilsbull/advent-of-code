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
  value retVal = std::numeric_limits<value>::min();
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

  constexpr auto steps = 40;

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  bool readTemplate = true;

  std::string polymer_template;
  std::map<std::string, std::string> puzzle_substitute;

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
      puzzle_substitute[utils::trim(sString[0])] = utils::trim(sString[1]);
    }
  }
  std::cout << "polymer_template: " << polymer_template << std::endl;

  // devide polimer template in pairs
  // ABCD -> AB BC CD
  std::map<std::string, uint64_t> poliPair;
  for (auto i = 1u; i < polymer_template.size(); i++)
  {
    auto pair = polymer_template.substr(i - 1, 2);
    poliPair[pair]++;
  }

  for (auto step = 0; step < steps; ++step)
  {
    // temp copy of element pair counter
    std::map<std::string, uint64_t> temp;
    for (auto [pp, count] : poliPair)
    {
      for (auto [subPat, sub] : puzzle_substitute)
      {
        if (subPat.compare(pp) == 0)
        {
          // XY -> Z
          // subPat: XY
          // sub: Z
          std::string tempidx = pp[0] + sub; // XZ
          // add XZ and increase count
          temp[tempidx] += count;
          tempidx = sub + pp[1]; // ZY
          // add ZY and increase count
          temp[tempidx] += count;
          break;
        }
      }
    }
    poliPair = temp;
  }

  for (auto [k, v] : poliPair)
  {
    std::cout << k << ": " << v << std::endl;
  }
  std::cout << "---------------------" << std::endl;

  std::map<char, uint64_t> count;
  // increment for first element of template
  count[polymer_template[0]]++;
  for (auto [c, cnt] : poliPair)
  {
    // add up all second elements of the pair -> avoid double counting
    count[c[1]] += cnt;
  }
  for (auto [k, v] : count)
  {
    std::cout << k << ": " << v << std::endl;
  }

  auto [maxKey, maxVal] = mapMax(count);
  auto [minKey, minVal] = mapMin(count);

  std::cout << "---------------------" << std::endl;
  std::cout << "maxVal:" << maxVal << std::endl;
  std::cout << "minVal:" << minVal << std::endl;
  std::cout << "result:" << maxVal - minVal << std::endl;
  return 0;
}