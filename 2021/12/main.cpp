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

class cave
{
public:
  void addTunnel(std::string from, std::string to)
  {
    if (map.find(from) != map.end())
    {
      map[from].push_back(to);
    }
    else
    {
      map[from] = std::vector<std::string>(1, to);
    }
  }

  void print()
  {
    for (auto &[key, value] : map)
    {
      for (auto val : value)
      {
        std::cout << key << " -> " << val << std::endl;
      }
    }
  }
  int getPaths(std::string from, std::string to)
  {
    std::map<std::string, bool> visited;
    return search(from, to, visited);
  }

private:
  std::map<std::string, std::vector<std::string>> map;

  int search(std::string node, const std::string &end, std::map<std::string, bool> visited)
  {
    if (node.compare(end) == 0)
    {
      return 1;
    }
    int result = 0;

    if (std::islower(node[0]))
    {
      visited[node] = true;
    }

    for (auto next : map[node])
    {
      if (visited.find(next) != visited.end())
      {
        continue;
      }
      else
      {
        result += search(next, end, visited);
      }
    }

    return result;
  }
};

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  cave c;

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;
  while (std::getline(infile, line))
  {
    utils::trim(line);
    auto sString = utils::splitString(line, "-");
    c.addTunnel(sString[0], sString[1]);
    c.addTunnel(sString[1], sString[0]);
  }

  c.print();
  std::cout << "---------------------" << std::endl;
  std::cout << "nPaths: " << c.getPaths("start", "end") << std::endl;
  return 0;
}