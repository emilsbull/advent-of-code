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

class Range
{
public:
  Range(std::string range)
  {
    auto split = utils::splitString(range, "-");
    from = std::stoi(split[0]);
    to = std::stoi(split[1]);
  }

  bool contains(const Range &other) const
  {
    return (from <= other.from) && (to >= other.to);
  }

  static bool contains(const std::pair<Range, Range> &pair)
  {
    return pair.first.contains(pair.second) || pair.second.contains(pair.first);
  }

  bool overlaps(const Range &other) const
  {
    return ((from <= other.from) && (to >= other.from)) || ((from <= other.to) && (to >= other.to));
  }

  static bool overlaps(const std::pair<Range, Range> &pair)
  {
    return pair.first.overlaps(pair.second) || pair.second.overlaps(pair.first);
  }

private:
  int from{0};
  int to{0};
};

void puzzleA(std::vector<std::pair<Range, Range>> inputPuzzle)
{
  int count = 0;

  for (auto &pair : inputPuzzle)
  {
    if (Range::contains(pair))
    {
      count++;
    }
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "pointsA:" << count << std::endl;
}

void puzzleB(std::vector<std::pair<Range, Range>> inputPuzzle)
{
  int count = 0;

  for (auto &pair : inputPuzzle)
  {
    if (Range::overlaps(pair))
    {
      count++;
    }
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "pointsB:" << count << std::endl;
}

int main(int, char *[])
{
  constexpr bool readFile = false;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::vector<std::pair<Range, Range>> input;

  while (std::getline(infile, line))
  {
    utils::trim(line);
    if (line.empty())
    {
      continue;
    }
    auto split = utils::splitString(line, ",");
    input.push_back({split[0], split[1]});
  }

  puzzleA(input);
  puzzleB(input);
  return 0;
}