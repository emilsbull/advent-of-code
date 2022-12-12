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

bool isTailMovingX(std::pair<int, int> head, std::pair<int, int> tail)
{
  return abs(head.first - tail.first) >= 2;
}

bool isTailMovingY(std::pair<int, int> head, std::pair<int, int> tail)
{
  return abs(head.second - tail.second) >= 2;
}
bool isTailMoving(std::pair<int, int> head, std::pair<int, int> tail)
{
  return isTailMovingX(head, tail) || isTailMovingY(head, tail);
}

void moveHead(std::pair<int, int> &head, char dir)
{
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

void moveTail(std::pair<int, int> head, std::pair<int, int> &tail)
{
  if (isTailMoving(head, tail))
  {

    if (isTailMovingX(head, tail))
    {
      if (head.first > tail.first)
      {
        tail.first++;
      }
      else
      {
        tail.first--;
      }
      
      if (head.second > tail.second)
      {
        tail.second++;
      }
      else if (head.second < tail.second)
      {
        tail.second--;
      }
    }
    else
    {
      if (head.second > tail.second)
      {
        tail.second++;
      }
      else
      {
        tail.second--;
      }

      if (head.first > tail.first)
      {
        tail.first++;
      }
      else if (head.first < tail.first)
      {
        tail.first--;
      }
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
      auto &head = knots[0];
      auto &tail = knots[1];
      moveHead(head, dir);
      moveTail(head, tail);
      visited[tail] = true;
    }
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "output A:" << visited.size();
  std::cout << std::endl;
}

void puzzleB(std::vector<std::pair<char, int>> motion)
{
  constexpr size_t nKnots = 10;
  std::array<std::pair<int, int>, nKnots> knots;
  std::map<std::pair<int, int>, bool> visited;
  visited[knots[0]] = true;

  for (auto &&[dir, count] : motion)
  {
    for (int i = 0; i < count; ++i)
    {
      moveHead(knots[0], dir);
      for (std::size_t j = 1; j < nKnots; ++j)
      {
        moveTail(knots[j - 1], knots[j]);
      }
      visited[knots.back()] = true;
    }
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "output B:" << visited.size();
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