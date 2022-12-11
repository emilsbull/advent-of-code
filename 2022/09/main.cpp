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

bool moveTail(int hX, int hY, int tX, int tY)
{
  return abs(hX - tX) >= 2 || abs(hY - tY) >= 2;
}

void puzzleA(std::vector<std::pair<char, int>> motion)
{
  int tailX = 0, tailY = 0;
  int headX = 0, headY = 0;
  std::map<std::pair<int, int>, bool> visited;
  visited[{tailX, tailY}] = true;

  for (auto &&[dir, count] : motion)
  {
    for (int i = 0; i < count; ++i)
    {
      switch (dir)
      {
      case 'R':
        headX++;
        break;
      case 'L':
        headX--;
        break;
      case 'U':
        headY++;
        break;
      case 'D':
        headY--;
        break;
      }

      if (moveTail(headX, headY, tailX, tailY))
      {
        if (dir == 'R' || dir == 'L')
        {
          tailY = headY;
        }
        else
        {
          tailX = headX;
        }

        switch (dir)
        {
        case 'R':
          tailX++;
          break;
        case 'L':
          tailX--;
          break;
        case 'U':
          tailY++;
          break;
        case 'D':
          tailY--;
          break;
        }
        visited[{tailX, tailY}] = true;
      }
    }
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "output A:" << visited.size();
  std::cout << std::endl;
}

void puzzleB(std::vector<std::pair<char, int>>)
{
  int score = 0;

  std::cout << "---------------------" << std::endl;
  std::cout << "output B:" << score;
  std::cout << std::endl;
}

int main(int, char *[])
{
  constexpr bool realPuzzle = true;
  const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::vector<std::pair<char, int>> motions;

  while (std::getline(infile, line))
  {
    if (line.empty())
    {
      continue;
    }
    auto split = utils::splitString(line, " ");
    motions.push_back(std::make_pair(*split[0].c_str(), std::stoi(split[1])));
  }

  puzzleA(motions);
  puzzleB(motions);
  return 0;
}