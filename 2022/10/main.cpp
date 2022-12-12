#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <cstdint>
#include <map>
#include <numeric>
#include <iterator>
#include <cstdio>

#include "string_utils.h"

void puzzleA(std::vector<std::string> commands)
{
  int registerX = 1;
  int cycle = 0;
  int result = 0;

  std::vector<int> stops{20, 60, 100, 140, 180, 220};

  auto nextStep = [&]() {
    cycle++;
    if (std::find(stops.begin(), stops.end(), cycle) != stops.end())
    {
      result += (cycle * registerX);
    }
  };

  for (auto &line : commands)
  {
    nextStep();
    if (line.compare("noop") != 0)  {
      nextStep();
      auto addx = utils::splitString(line, " ");
      registerX += std::stoi(addx[1]);
    }
  }
  std::cout << "---------------------" << std::endl;
  std::cout << "output A:" << result;
  std::cout << std::endl;
}

void puzzleB(std::vector<std::string> commands)
{
  std::cout << "---------------------" << std::endl;
  std::cout << "output B:" << commands.size();
  std::cout << std::endl;
}

int main(int, char *[])
{
  constexpr bool realPuzzle = true;
  const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::vector<std::string> commands;

  while (std::getline(infile, line))
  {
    if (line.empty())
    {
      continue;
    }
    commands.push_back(line);
  }

  puzzleA(commands);
  puzzleB(commands);
  return 0;
}