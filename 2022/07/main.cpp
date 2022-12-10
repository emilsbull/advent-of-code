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

struct File
{
  std::string name;
  std::size_t size;

  File(std::string name, std::size_t size) : name(name), size(size) {}
};

struct Directory
{
  std::string name;
  std::map<std::string, std::shared_ptr<File>> files{};
  std::map<std::string, std::shared_ptr<Directory>> subDirs{};
  std::shared_ptr<Directory> parent{nullptr};

  Directory(std::string name, std::shared_ptr<Directory> parent = nullptr) : name(name), parent(parent) {}

  std::size_t getSize()
  {
    std::size_t size = 0;
    for (const auto &[name, file] : files)
    {
      size += file->size;
    }
    for (const auto &[name, dir] : subDirs)
    {
      size += dir->getSize();
    }
    return size;
  }
};

void countA(int &result, std::shared_ptr<Directory> dir)
{
  constexpr int minSize = 100000;
  int dirSize = dir->getSize();

  if (dirSize < minSize)
  {
    result += dirSize;
  }
  for (auto const &[name, subdir] : dir->subDirs)
  {
    countA(result, subdir);
  }
}

void puzzleA(std::shared_ptr<Directory> node)
{
  int result = 0;

  countA(result, node);
  std::cout << "---------------------" << std::endl;
  std::cout << "output A:" << result;
  std::cout << std::endl;
}

void puzzleB()
{
  std::cout << "---------------------" << std::endl;
  std::cout << "output B:";
  std::cout << std::endl;
}

int main(int, char *[])
{
  constexpr bool realPuzzle = true;
  const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::shared_ptr<Directory> rootDir(new Directory("/"));
  std::shared_ptr<Directory> currentDir = rootDir;

  while (std::getline(infile, line))
  {
    if (line.empty())
    {
      continue;
    }

    if (line.starts_with('$'))
    {
      // command
      if (line.starts_with("$ cd"))
      {
        auto folder = line.substr(5);
        if (folder.compare("/") == 0)
        {
          currentDir = rootDir;
        }
        else if (folder.compare("..") == 0)
        {
          currentDir = currentDir->parent;
        }
        else
        {
          currentDir = currentDir->subDirs[folder];
        }
      }
    }
    else
    {
      auto dirEntry = utils::splitString(line, " ");
      try
      {
        int size = std::stoi(utils::trim(dirEntry[0]));
        std::string name = dirEntry[1];
        currentDir->files[name] = std::make_shared<File>(name, size);
      }
      catch (...)
      {
        std::string name = dirEntry[1];
        currentDir->subDirs[name] = std::make_shared<Directory>(name, currentDir);
      }
    }
  }

  puzzleA(rootDir);
  puzzleB();
  return 0;
}