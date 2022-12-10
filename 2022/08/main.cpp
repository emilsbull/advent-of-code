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

bool visibleA(std::vector<std::vector<int>> grid, size_t x, size_t y)
{
  bool visible = true;

  int treeHeight = grid[y][x];
  // from left
  for (size_t i = 0; i < x; ++i)
  {
    if (grid[y][i] >= treeHeight)
      visible = false;
  }
  if (visible)
    return true;
  visible = true;

  // from right
  for (size_t i = grid[y].size() - 1; i > x; --i)
  {
    if (grid[y][i] >= treeHeight)
      visible = false;
  }
  if (visible)
    return true;
  visible = true;

  // from top
  for (size_t i = 0; i < y; ++i)
  {
    if (grid[i][x] >= treeHeight)
      visible = false;
  }
  if (visible)
    return true;
  visible = true;

  // from right
  for (size_t i = grid.size() - 1; i > y; --i)
  {
    if (grid[i][x] >= treeHeight)
      visible = false;
  }
  if (visible)
    return true;

  return false;
}

void puzzleA(std::vector<std::vector<int>> grid)
{
  int result = 2 * grid.size() + 2 * grid.at(0).size() - 4;

  for (size_t i = 1u; i < grid.size() - 1u; ++i)
  {
    for (size_t j = 1u; j < grid[i].size() - 1u; ++j)
    {
      auto visible = visibleA(grid, j, i);
      if (visible > 0)
      {
        result++;
      }
    }
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "output A:" << result;
  std::cout << std::endl;
}

void puzzleB(std::vector<std::vector<int>> /* grid */)
{
  int result = 0;

  std::cout << "---------------------" << std::endl;
  std::cout << "output B:" << result;
  std::cout << std::endl;
}

int main(int, char *[])
{
  constexpr bool realPuzzle = true;
  const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::vector<std::vector<int>> grid;

  while (std::getline(infile, line))
  {
    if (line.empty())
    {
      continue;
    }
    grid.push_back({});
    for (char c : line)
    {
      grid.back().emplace_back(c - '0');
    }
  }

  puzzleA(grid);
  puzzleB(grid);
  return 0;
}