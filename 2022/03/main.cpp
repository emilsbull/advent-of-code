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

int getPoints(char item)
{
  if (islower(item))
    return item - ('a') + 1;
  return item - 'A' + 1 + 'z' - 'a' + 1;
}

bool itemFound(std::string rucksack, char item)
{
  return rucksack.find(item) != std::string::npos;
}

void puzzleA(std::vector<std::string> inputPuzzle)
{
  std::vector<std::string> compartments;
  int points = 0;

  for (auto &line : inputPuzzle)
  {
    compartments.push_back(line.substr(0, line.size() / 2));
    compartments.push_back(line.substr(line.size() / 2, line.size()));

    for (char item : compartments[0])
    {
      if (itemFound(compartments[1], item))
      {
        points += getPoints(item);
        break;
      }
    }
    compartments.clear();
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "points:" << points << std::endl;
}

int getPointsB(std::vector<std::string> rucksacks)
{

  for (auto rucksack : rucksacks)
  {
    for (char item : rucksack)
    {
      if (itemFound(rucksacks[0], item) && itemFound(rucksacks[1], item) && itemFound(rucksacks[2], item))
      {
        return getPoints(item);
      }
    }
  }
  return 0;
}

void puzzleB(std::vector<std::string> inputPuzzle)
{
  std::vector<std::string> rucksacks;
  int points = 0;

  for (auto &line : inputPuzzle)
  {
    rucksacks.push_back(line);
    if (rucksacks.size() == 3)
    {
      points += getPointsB(rucksacks);
      rucksacks.clear();
    }
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "pointsB:" << points << std::endl;
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