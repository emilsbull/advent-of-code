#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <stack>

#include "string_utils.h"

namespace fs = std::filesystem;

int validate(std::string line)
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
        return 25137;
      }
      break;
    case ')':
      if (stack.top() == '(')
      {
        stack.pop();
      }
      else
      {
        return 3;
      }
      break;
    case ']':
      if (stack.top() == '[')
      {
        stack.pop();
      }
      else
      {
        return 57;
      }
      break;
    case '}':
      if (stack.top() == '{')
      {
        stack.pop();
      }
      else
      {
        return 1197;
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
  return 0;
}

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  int result = 0;

  while (std::getline(infile, line))
  {
    utils::trim(line);
    result += validate(line);
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "Result: " << result << std::endl;
  return 0;
}