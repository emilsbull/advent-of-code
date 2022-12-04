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
#include <iterator>

#include "string_utils.h"

namespace fs = std::filesystem;

enum class Sign
{
  Rock = 1,
  Paper = 2,
  Scissor = 3,
  END = -1
};

enum class Result
{
  Loose,
  Win,
  Draw,
  Bad
};

inline Sign getSign(std::string &str)
{
  switch (str.at(0))
  {
  case 'A':
  case 'X':
    return Sign::Rock;
    break;
  case 'B':
  case 'Y':
    return Sign::Paper;
    break;
  case 'C':
  case 'Z':
    return Sign::Scissor;
    break;
  }

  return Sign::END;
};

inline Result getResult(std::string &str)
{
  switch (str.at(0))
  {
  case 'X':
    return Result::Loose;
    break;
  case 'Y':
    return Result::Draw;
    break;
  case 'Z':
    return Result::Win;
    break;
  }

  return Result::Bad;
};

inline Sign makeResult(Sign other, Result res)
{
  switch (res)
  {
  case Result::Draw:
    return other;
  case Result::Win:
    switch (other)
    {
    case Sign::Rock:
      return Sign::Paper;
    case Sign::Paper:
      return Sign::Scissor;
    case Sign::Scissor:
      return Sign::Rock;
    default:
      return Sign::END;
    }
  case Result::Loose:
    switch (other)
    {
    case Sign::Rock:
      return Sign::Scissor;
    case Sign::Paper:
      return Sign::Rock;
    case Sign::Scissor:
      return Sign::Paper;
    default:
      return Sign::END;
    }
  default:
    return Sign::END;
  }
}

inline bool hasWon(Sign other, Sign me)
{
  switch (other)
  {
  case Sign::Rock:
    return (me == Sign::Paper);
    break;
  case Sign::Paper:
    return (me == Sign::Scissor);
    break;
  case Sign::Scissor:
    return (me == Sign::Rock);
    break;
  default:
    std::cout << "oops" << std::endl;
    break;
  }
  return false;
}

inline int getPoints(Sign other, Sign me)
{
  if (other == me)
  {
    return static_cast<int>(me) + 3;
  }

  if (hasWon(other, me))
  {
    return static_cast<int>(me) + 6;
  }

  return static_cast<int>(me);
}

int main(int, char *[])
{
  constexpr bool readFile = false;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  int points = 0;
  int pointsB = 0;

  while (std::getline(infile, line))
  {
    utils::trim(line);
    if (line.empty())
    {
      continue;
    }
    auto foo = utils::splitString(line, " ");
    points += getPoints(getSign(foo[0]), getSign(foo[1]));

    auto bar = getResult(foo[1]);
    pointsB += getPoints(getSign(foo[0]), makeResult(getSign(foo[0]), bar));
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "points:" << points << std::endl;

  std::cout << "---------------------" << std::endl;
  std::cout << "points B:" << pointsB << std::endl;
  return 0;
}