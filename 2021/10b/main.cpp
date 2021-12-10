#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <stack>
#include <tuple>

#include "string_utils.h"

namespace fs = std::filesystem;

std::pair<int, uint64_t> validate(std::string line)
{

  std::stack<char> stack;

  for (auto c : line)
  {
    switch (c)
    {
    case '>':
      if (stack.top() == '<')
      {
        stack.pop();
      }
      else
      {
        return std::make_pair(25137, 0);
      }
      break;
    case ')':
      if (stack.top() == '(')
      {
        stack.pop();
      }
      else
      {
        return std::make_pair(3, 0);
      }
      break;
    case ']':
      if (stack.top() == '[')
      {
        stack.pop();
      }
      else
      {
        return std::make_pair(57, 0);
      }
      break;
    case '}':
      if (stack.top() == '{')
      {
        stack.pop();
      }
      else
      {
        return std::make_pair(1197, 0);
      }
      break;

    case '<':
    case '(':
    case '[':
    case '{':
      stack.push(c);
      break;
    }
  }

  uint64_t incomplete = 0U;

  while (!stack.empty())
  {
    switch (stack.top())
    {
    case '(':
      incomplete = incomplete * 5U + 1U;
      break;
    case '[':
      incomplete = incomplete * 5U + 2U;
      break;
    case '{':
      incomplete = incomplete * 5U + 3U;
      break;
    case '<':
      incomplete = incomplete * 5U + 4U;
      break;
    }
    stack.pop();
  }

  return std::make_pair(0, incomplete);
}

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::vector<uint64_t> incompleteVector;

  int result = 0;

  while (std::getline(infile, line))
  {
    utils::trim(line);
    auto [corrupted, incomplete] = validate(line);
    result += corrupted;
    if (incomplete != 0)
    {
      incompleteVector.push_back(incomplete);
    }
  }

  std::sort(incompleteVector.begin(), incompleteVector.end());

  for (auto i = 0U; i < incompleteVector.size(); ++i)
  {
    std::cout << "vec[" << std::setw(3) << std::setfill(' ') << i << "]: " << incompleteVector[i] << std::endl;
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "Result A: " << result << std::endl;
  std::cout << "Result B: " << incompleteVector[incompleteVector.size() / 2] << std::endl;
  return 0;
}