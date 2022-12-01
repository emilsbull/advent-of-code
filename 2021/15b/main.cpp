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

#include "string_utils.h"

namespace fs = std::filesystem;

void print(std::vector<std::vector<int>> costMap, std::vector<std::vector<int>> map)
{
  // `M × N` matrix
  int M = costMap.size();
  int N = costMap[0].size();
  std::vector<std::vector<char>> printMap(M, std::vector<char>(N, '.'));

  auto cM = 0;
  auto cN = 0;

  while (true)
  {

    printMap[cM][cN] = std::to_string(map[cM][cN])[0]; //'#';

    if (cN == N - 1)
    {
      if (cM == M - 1)
      {
        break;
      }
    }

    auto up = std::numeric_limits<int>::max();
    auto left = std::numeric_limits<int>::max();
    auto right = std::numeric_limits<int>::max();
    auto down = std::numeric_limits<int>::max();

    if (cN < N - 1)
    {
      right = costMap[cM][cN + 1];
    }
    if (cN > 0)
    {
      left = costMap[cM][cN - 1];
    }
    if (cM < M - 1)
    {
      down = costMap[cM + 1][cN];
    }
    if (cM > 0)
    {
      up = costMap[cM - 1][cN];
    }

    auto min = std::min({up, down, left, right});
    if (min == up)
    {
      cM--;
    }
    else if (min == down)
    {
      cM++;
    }
    else if (min == right)
    {
      cN++;
    }
    else if (min == left)
    {
      cN--;
    }
  }
  printMap[cM][cN] = std::to_string(map[cM][cN])[0]; //'#';

  for (auto line : printMap)
  {
    for (auto val : line)
    {
      std::cout << val;
    }
    std::cout << std::endl;
  }
}

int findMinCost(std::vector<std::vector<int>> const &cost)
{
  // base case
  if (cost.size() == 0)
  {
    return 0;
  }

  // `M × N` matrix
  int M = cost.size();
  int N = cost[0].size();

  std::vector<std::vector<int>> accumulatedCost(M, std::vector<int>(N, std::numeric_limits<int>::max()));

  for (auto bla = 0; bla < 1000; bla++)
  {
    for (auto line = M - 1; line >= 0; line--)
    {
      for (auto col = N - 1; col >= 0; col--)
      {
        if (line == M - 1 && col == N - 1)
        {
          accumulatedCost[line][col] = cost[line][col];
          continue;
        }

        auto up = std::numeric_limits<int>::max();
        auto left = std::numeric_limits<int>::max();
        auto right = std::numeric_limits<int>::max();
        auto down = std::numeric_limits<int>::max();

        if (col < N - 1)
        {
          right = accumulatedCost[line][col + 1];
        }
        if (col > 0)
        {
          left = accumulatedCost[line][col - 1];
        }
        if (line < M - 1)
        {
          down = accumulatedCost[line + 1][col];
        }
        if (line > 0)
        {
          up = accumulatedCost[line - 1][col];
        }
        accumulatedCost[line][col] = cost[line][col] + std::min({up, down, left, right});
      }
    }

    std::cout << "---------------------" << std::endl;
    std::cout << "iterate cost: " << accumulatedCost[0][0] << std::endl;
    print(accumulatedCost, cost);
  }

  return accumulatedCost[0][0] - cost[0][0];
}

int main(int, char *[])
{
  constexpr bool readFile = false;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::vector<std::vector<int>> map;

  while (std::getline(infile, line))
  {
    utils::trim(line);
    if (line.empty())
    {
      continue;
    }
    map.emplace_back();
    for (auto c : line)
    {
      map.back().emplace_back(c - '0');
    }
  }
  // const std::size_t mapWidth = map[0].size();
  const std::size_t mapHeight = map.size();

  std::vector<std::vector<int>> greaterMap = map;

  for (auto i = 0; i < 5; ++i)
  {
    std::vector<std::vector<int>> tempMap = map;
    std::for_each(tempMap.begin(), tempMap.end(), [i](auto &v)
                  {
                    std::for_each(v.begin(), v.end(), [i](auto &element)
                                  {
                                    element += i;
                                    if (element > 9)
                                    {
                                      element -=9;
                                    }
                                  });
                  });
    for (auto line = 0u; line < mapHeight; ++line)
    {
      greaterMap[line].insert(greaterMap[line].end(), tempMap[line].begin(), tempMap[line].end());
    }
  }

  std::vector<std::vector<int>> tempMap = greaterMap;
  for (auto i = 1; i < 5; ++i)
  {
    std::for_each(tempMap.begin(), tempMap.end(), [](auto &v)
                  {
                    std::for_each(v.begin(), v.end(), [](auto &element)
                                  {
                                    element++;
                                    if (element > 9)
                                    {
                                      element = 1;
                                    }
                                  });
                  });
    for (auto line = 0u; line < mapHeight; ++line)
    {
      greaterMap.push_back(tempMap[line]);
    }
  }

  auto cost = findMinCost(greaterMap);
  std::cout << "---------------------" << std::endl;
  std::cout << "result:" << cost << std::endl;
  return 0;
}