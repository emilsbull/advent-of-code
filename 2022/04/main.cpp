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

class Range {
  public:
  Range(std::string range) {
    auto split = utils::splitString(range, "-");
    from = std::stoi(split[0]);
    to = std::stoi(split[1]);
  }

  bool contains(const Range& other) const {
    return (from <= other.from) && (to >= other.to);
  }

  static bool contains(const Range& first, const Range& second) {
    return first.contains(second) || second.contains(first);
  }

  private:
  int from{0};
  int to{0};
};


void puzzleA(std::vector<std::string> inputPuzzle)
{
  int count = 0;

  for(auto &line: inputPuzzle) {
    auto split = utils::splitString(line, ",");
    Range first(split[0]);
    Range second(split[1]);

    if(Range::contains(first, second)) {
      count++;
    }
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "pointsA:" << count << std::endl;
}

void puzzleB(std::vector<std::string> /* inputPuzzle */)
{

/*   std::cout << "---------------------" << std::endl;
  std::cout << "pointsB:" << points << std::endl; */
}

int main(int, char *[])
{
  constexpr bool readFile = false;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::vector<std::string> input;

  while (std::getline(infile, line))
  {
    utils::trim(line);
    if (line.empty())
    {
      continue;
    }
    input.push_back(line);
  }

  puzzleA(input);
  puzzleB(input);
  return 0;
}