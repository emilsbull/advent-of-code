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

namespace fs = std::filesystem;

const char *ws = " \t\n\r\f\v";

// trim from end of string (right)
inline std::string &rtrim(std::string &s, const char *t = ws)
{
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}

// trim from beginning of string (left)
inline std::string &ltrim(std::string &s, const char *t = ws)
{
  s.erase(0, s.find_first_not_of(t));
  return s;
}

// trim from both ends of string (right then left)
inline std::string &trim(std::string &s, const char *t = ws)
{
  return ltrim(rtrim(s, t), t);
}

std::vector<std::string> splitString(std::string input, std::string delimiter)
{
  std::vector<std::string> result;

  auto start = 0U;
  auto end = input.find(delimiter);
  while (end != std::string::npos)
  {
    auto substr = input.substr(start, end - start);
    trim(substr);
    if (substr.size() > 0)
    {
      result.push_back(substr);
    }
    start = end + delimiter.length();
    end = input.find(delimiter, start);
  }
  auto substr = input.substr(start, end - start);
  trim(substr);
  if (substr.size() > 0)
  {
    result.push_back(substr);
  }
  return result;
}

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  std::vector<std::vector<std::string>> input;

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;
  while (std::getline(infile, line))
  {
    auto split = splitString(line, "|");
    input.emplace_back(splitString(split.at(1), " "));
  }

  if (input.empty())
  {
    std::cerr << "PARSING ERROR";
    return -1;
  }

  auto ones = 0;
  auto sevens = 0;
  auto fours = 0;
  auto eights = 0;
  for (auto i = 0U; i < input.size(); ++i)
  {
    for (auto number : input[i])
    {
      switch (number.size())
      {
      case 2:
        ones++;
        break;
      case 3:
        sevens++;
        break;
      case 4:
        fours++;
        break;
      case 7:
        eights++;
        break;

      default:
        break;
      }
    }
  }

  auto result = ones + fours + sevens+ eights;
  std::cout << "ones: " << ones << std::endl;
  std::cout << "fours: " << fours << std::endl;
  std::cout << "sevens: " << sevens << std::endl;
  std::cout << "eights: " << eights << std::endl;
  std::cout << "---------------------" << std::endl;
  std::cout << "Sum: " << result << std::endl;
  return 0;
}