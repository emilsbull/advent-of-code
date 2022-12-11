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

bool isTailMoving(std::pair<int, int> head, std::pair<int, int> tail)
{
  return abs(head.first - tail.first) >= 2 || abs(head.second - tail.second) >= 2;
}

void moveHead(std::pair<int, int>& head, char dir) {
      switch (dir)
      {
      case 'R':
        head.first++;
        break;
      case 'L':
        head.first--;
        break;
      case 'U':
        head.second++;
        break;
      case 'D':
        head.second--;
        break;
      }
}

void moveTail(std::pair<int, int> head, std::pair<int, int>& tail, char dir) {
      if (isTailMoving(head, tail))
      {
        if (dir == 'R' || dir == 'L')
        {
          tail.second = head.second;
        }
        else
        {
          tail.first = head.first;
        }

        switch (dir)
        {
        case 'R':
          tail.first++;
          break;
        case 'L':
          tail.first--;
          break;
        case 'U':
          tail.second++;
          break;
        case 'D':
          tail.second--;
          break;
        }
      }
}

void puzzleA(std::vector<std::pair<char, int>> motion)
{
  std::array<std::pair<int, int>, 2> knots;
  std::map<std::pair<int, int>, bool> visited;
  visited[{0, 0}] = true;

  for (auto &&[dir, count] : motion)
  {
    for (int i = 0; i < count; ++i)
    {
      auto& head = knots[0];
      auto& tail = knots[1];
      moveHead(head, dir);
      moveTail(head, tail, dir);
      visited[tail] = true;
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