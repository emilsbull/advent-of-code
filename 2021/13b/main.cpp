#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <cstdint>
#include <map>

#include "string_utils.h"

namespace fs = std::filesystem;

class Paper
{
public:
  Paper(std::size_t max_X, std::size_t max_Y) : markedDots(max_X+1, std::vector<bool>(max_Y+1, false))
  {
  }

  void addDots(std::vector<std::pair<std::size_t, std::size_t>> dots)
  {
    for (auto [x, y] : dots)
    {
      markedDots[y][x] = true;
    }
  }

  void print()
  {
    for (auto line : markedDots)
    {
      for (auto marked : line)
      {
        std::cout << (marked ? "#" : ".");
      }
      std::cout << std::endl;
    }
  }

  void foldHorizontal(std::size_t index)
  {
    for (auto i = 0u; i < markedDots.size() - index; ++i)
    {
      for (auto j = 0u; j < markedDots[i].size(); ++j)
      {
        markedDots[index - i][j] = markedDots[index - i][j] || markedDots[index + i][j];
      }
    }
    markedDots.resize(index);
  }

  void foldVertical(std::size_t index)
  {
    for (auto i = 0u; i < markedDots.size(); ++i)
    {
      for (auto j = 0u; j < markedDots[i].size() - index; ++j)
      {
        markedDots[i][index - j] = markedDots[i][index - j] || markedDots[i][index + j];
      }
      markedDots[i].resize(index);
    }
  }

  int visiblePoints() {
    int ret = 0;
    for(auto line : markedDots) {
      for(auto marked : line) {
        if(marked)
        ret ++;
      }
    }
    return ret;
  }

private:
  std::vector<std::vector<bool>> markedDots;
};

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};


  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  bool readMarks = true;

  std::vector<std::pair<std::size_t, std::size_t>> marked;
  std::vector<std::pair<std::string, std::size_t>> foldings;

  while (std::getline(infile, line))
  {
    utils::trim(line);
    if (line.empty())
    {
      readMarks = false;
      continue;
    }
    if (readMarks)
    {
      auto sString = utils::splitString(line, ",");
      marked.emplace_back(std::stoi(sString[0]), std::stoi(sString[1]));
    }
    else
    {
      auto sString = utils::splitString(line, "=");
      std::string axis = sString[0].substr(sString[0].size() - 1, 1);
      auto index = std::stoi(sString[1]);
      foldings.emplace_back(axis, index);
    }
  }
  std::size_t width = 0u;
  std::size_t height = 0u;
  std::for_each(marked.begin(), marked.end(), [&width, &height](auto val)
                {
                  auto [y, x] = val;
                  width = std::max(x, width);
                  height = std::max(y, height);
                });

  
  Paper p(width, height);
  p.addDots(marked);
  // p.print();
  // std::cout << "---------------------" << std::endl;

  for(auto [axis, index]:foldings) {
    if(axis.compare("x") == 0) {
      p.foldVertical(index);
    } else {
      p.foldHorizontal(index);
    }
  }

  p.print();
  std::cout << "---------------------" << std::endl;
  std::cout << "marked Points: " << p.visiblePoints() << std::endl; 
  return 0;
}