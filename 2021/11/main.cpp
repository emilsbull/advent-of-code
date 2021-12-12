#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <cstdint>
#include <bitset>
#include <regex>

#include "string_utils.h"

namespace fs = std::filesystem;

void spread(std::vector<std::vector<int>> &input, int x, int y)
{
  input[x][y]++;
}

int evolve(std::vector<std::vector<int>> &input)
{
  int flashes = 0;
  for (auto i = 0U; i < input.size(); ++i)
  {
    for (auto j = 0U; j < input[i].size(); ++j)
    {
      if ((input[i][j] > 9) && (input[i][j] < 100))
      {
        flashes++;
        input[i][j] = 100;
        if ((j + 1U) < input[i].size())
        {
          spread(input, i, j + 1);
        }
        if (((int)j - 1) >= 0)
        {
          spread(input, i, j - 1);
        }
        if ((i + 1U) < input.size())
        {
          spread(input, i + 1, j);

          if ((j + 1U) < input[i].size())
          {
            spread(input, i + 1, j + 1);
          }

          if (((int)j - 1) >= 0)
          {
            spread(input, i + 1, j - 1);
          }
        }
        if (((int)i - 1) >= 0)
        {
          spread(input, i - 1, j);

          if ((j + 1U) < input[i].size())
          {
            spread(input, i - 1, j + 1);
          }

          if (((int)j - 1) >= 0)
          {
            spread(input, i - 1, j - 1);
          }
        }
      }
    }
  }
  return flashes;
}

void print(std::vector<std::vector<int>> input)
{
  for (auto line : input)
  {
    std::for_each(line.begin(), line.end(), [](auto &val)
                  {
                    if (val > 9)
                    {
                      std::cout << "*";
                    }
                    else
                    {
                      std::cout << val;
                    }
                  });
    std::cout << std::endl;
  }
}

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};
  constexpr int steps = 100;

  std::vector<std::vector<int>> input;

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;
  while (std::getline(infile, line))
  {
    utils::trim(line);
    input.emplace_back();
    for (auto number : line)
    {
      input.back().emplace_back(number - '0');
    }
  }

  if (input.empty())
  {
    std::cerr << "PARSING ERROR";
    return -1;
  }

    std::cout << "Before any steps:" << std::endl;
  print(input);
    std::cout << "---------------------" << std::endl;
  int flashes = 0;

  for (int step = 0; step < steps; ++step)
  {
    std::for_each(input.begin(), input.end(), [](auto &line)
                  { std::for_each(line.begin(), line.end(), [](int &val)
                                  { ++val; }); });

    while (true)
    {
      int tempFlashes = evolve(input);
      flashes += tempFlashes;
      if (tempFlashes == 0)
      {
        break;
      }
    }
    std::cout << "After step "<< step +1 << ":" << std::endl;
    print(input);
    std::cout << "---------------------" << std::endl;
    std::for_each(input.begin(), input.end(), [](auto &line)
                  {
                    std::for_each(line.begin(), line.end(), [](int &val)
                                  {
                                    if (val > 9)
                                    {
                                      val = 0;
                                    }
                                  });
                  });
  }

  std::cout << "Flashes: " << flashes << std::endl;
  std::cout << "---------------------" << std::endl;
  return 0;
}