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

  std::vector<std::string> compartments;
  int points = 0;

  while (std::getline(infile, line))
  {
    utils::trim(line);
    if (line.empty())
    {
      continue;
    }
    compartments.push_back(line.substr(0, line.size()/2));
    compartments.push_back(line.substr(line.size()/2, line.size()));

    for(char item : compartments[0]) {
      if (compartments[1].find(item) != std::string::npos){
        if(islower(item)) {
          points += item - ('a') + 1;
        } else {
          points += item - 'A' + 1 + 'z' - 'a' + 1;
        }
        break;
      }
    }
    compartments.clear();
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "points:" << points << std::endl;
  return 0;
}