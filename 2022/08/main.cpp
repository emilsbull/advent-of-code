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

int scenicScore(std::vector<std::vector<int>> grid, size_t x, size_t y)
{
  size_t ret = 1;
  size_t score = 1;

  int treeHeight = grid[y][x];
  // from left
  for (score = 1; score <= x; ++score)
  {
    if (grid[y][x - score] >= treeHeight)
    {
      score++;
      break;
    }
  }
  ret *= score-1;

  // from right
  for (score = 1; score < (grid[y].size() - x); score++)
  {
    if (grid[y][x + score] >= treeHeight)
    {
      score++;
      break;
    }
  }
  ret *= score-1;

  // from top
  for (score = 1; score <= y; score++)
  {
    if (grid[y - score][x] >= treeHeight)
    {
      score++;
      break;
    }
  }
  ret *= score-1;

  // from right
  for (score = 1; score < (grid.size() - y); score++)
  {
    if (grid[y + score][x] >= treeHeight)
    {
      score++;
      break;
    }
  }
  ret *= score-1;

  return ret;
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

void puzzleB(std::vector<std::vector<int>> grid)
{
  int score = 0;
  for (size_t i = 1u; i < grid.size() - 1u; ++i)
  {
    for (size_t j = 1u; j < grid[i].size() - 1u; ++j)
    {
      score = std::max(score, scenicScore(grid, j, i));
    }
  }

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