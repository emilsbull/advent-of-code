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

enum Segment : uint8_t
{
  a = 1U << 0,
  b = 1U << 1,
  c = 1U << 2,
  d = 1U << 3,
  e = 1U << 4,
  f = 1U << 5,
  g = 1U << 6,
};

//  dddd
// e    a
// e    a
//  ffff
// g    b
// g    b
//  cccc
enum Number : uint8_t
{
  zero = Segment::a | Segment::b | Segment::c | Segment::d | Segment::e | Segment::g,
  one = Segment::a | Segment::b,
  two = Segment::a | Segment::c | Segment::d | Segment::f | Segment::g,
  three = Segment::a | Segment::b | Segment::c | Segment::d | Segment::f,
  four = Segment::a | Segment::b | Segment::e | Segment::f,
  five = Segment::b | Segment::c | Segment::d | Segment::f | Segment::e,
  six = Segment::b | Segment::c | Segment::d | Segment::e | Segment::f | Segment::g,
  seven = Segment::a | Segment::b | Segment::d,
  eight = Segment::a | Segment::b | Segment::c | Segment::d | Segment::e | Segment::f | Segment::g,
  nine = Segment::a | Segment::b | Segment::c | Segment::d | Segment::e | Segment::f,
  NONE = 0x00U
};

uint8_t toNumber(std::string string)
{
  uint8_t result = Number::NONE;

  for (auto c : string)
  {
    switch (c)
    {
    case 'a':
      result |= Segment::a;
      break;
    case 'b':
      result |= Segment::b;
      break;
    case 'c':
      result |= Segment::c;
      break;
    case 'd':
      result |= Segment::d;
      break;
    case 'e':
      result |= Segment::e;
      break;
    case 'f':
      result |= Segment::f;
      break;
    case 'g':
      result |= Segment::g;
      break;
    }
  }
  return result;
}

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  std::vector<std::vector<std::string>> input;
  std::vector<std::vector<std::string>> trainingData;
  std::array<uint8_t, 10> toCrypt;
  std::map<uint8_t, uint8_t> toDecrypt;

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;
  while (std::getline(infile, line))
  {
    auto split = utils::splitString(line, "|");
    trainingData.emplace_back(utils::splitString(split[0], " "));
    input.emplace_back(utils::splitString(split[1], " "));
  }

  if (input.empty() || trainingData.empty() || trainingData.size() != input.size())
  {
    std::cerr << "PARSING ERROR";
    return -1;
  }

  auto result = 0;
  for (auto i = 0U; i < input.size(); ++i)
  {
    toDecrypt.clear();
    toCrypt.fill(0U);

    // get 1, 4, 7, 8
    // missing 0, 2, 3, 5, 6, 9
    for (auto tInput : trainingData[i])
    {
      uint8_t cryptNumber = toNumber(tInput);
      switch (tInput.size())
      {
      case 2:
        toDecrypt.emplace(cryptNumber, (uint8_t)Number::one);
        toCrypt[1] = cryptNumber;
        break;
      case 3:
        toDecrypt.emplace(cryptNumber, (uint8_t)Number::seven);
        toCrypt[7] = cryptNumber;
        break;
      case 4:
        toDecrypt.emplace(cryptNumber, (uint8_t)Number::four);
        toCrypt[4] = cryptNumber;
        break;
      case 7:
        toDecrypt.emplace(cryptNumber, (uint8_t)Number::eight);
        toCrypt[8] = cryptNumber;
        break;

      default:
        break;
      }
    }
    // get 1, 3, 4, 7, 8, 9, 6
    // missing 0, 2, 5
    for (auto tInput : trainingData[i])
    {
      uint8_t cryptNumber = toNumber(tInput);
      switch (tInput.size())
      {
      case 5:
        if ((toCrypt[1] & cryptNumber) == toCrypt[1])
        {
          toDecrypt.emplace(cryptNumber, (uint8_t)Number::three);
          toCrypt[3] = cryptNumber;
        }
        break;
      case 6:
        if ((toCrypt[4] & cryptNumber) == toCrypt[4])
        {
          toDecrypt.emplace(cryptNumber, (uint8_t)Number::nine);
          toCrypt[9] = cryptNumber;
        }
        if ((toCrypt[7] & cryptNumber) != toCrypt[7])
        {
          toDecrypt.emplace(cryptNumber, (uint8_t)Number::six);
          toCrypt[6] = cryptNumber;
        }
        break;
      default:
        break;
      }
    }
    // get 0, 1, 3, 4, 5, 6, 7, 8, 9,
    // missing 2
    for (auto tInput : trainingData[i])
    {
      uint8_t cryptNumber = toNumber(tInput);
      switch (tInput.size())
      {
      case 5:
        if ((toCrypt[6] & cryptNumber) == cryptNumber)
        {
          toDecrypt.emplace(cryptNumber, (uint8_t)Number::five);
          toCrypt[5] = cryptNumber;
        }
        break;
      case 6:
        if ((toCrypt[6] != cryptNumber) && (toCrypt[9] != cryptNumber))
        {
          toDecrypt.emplace(cryptNumber, (uint8_t)Number::zero);
          toCrypt[0] = cryptNumber;
        }
        break;
      default:
        break;
      }
    }
    // get 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    for (auto tInput : trainingData[i])
    {
      uint8_t cryptNumber = toNumber(tInput);
      switch (tInput.size())
      {
      case 5:
        if ((toCrypt[3] != cryptNumber) && (toCrypt[5] != cryptNumber))
        {
          toDecrypt.emplace(cryptNumber, (uint8_t)Number::two);
          toCrypt[2] = cryptNumber;
        }
        break;
      default:
        break;
      }
    }

    // decrypt numbers
    auto currentNumber = 0;
    for (auto digit : input[i])
    {
      uint8_t num = toNumber(digit);

      auto currentDigit = 0;
      switch (toDecrypt[num])
      {
      case Number::zero:
        currentDigit = 0;
        break;
      case Number::one:
        currentDigit = 1;
        break;
      case Number::two:
        currentDigit = 2;
        break;
      case Number::three:
        currentDigit = 3;
        break;
      case Number::four:
        currentDigit = 4;
        break;
      case Number::five:
        currentDigit = 5;
        break;
      case Number::six:
        currentDigit = 6;
        break;
      case Number::seven:
        currentDigit = 7;
        break;
      case Number::eight:
        currentDigit = 8;
        break;
      case Number::nine:
        currentDigit = 9;
        break;
      default:
        currentDigit = -1;
      }
      currentNumber = currentNumber * 10 + currentDigit;
    }
    std::cout << " " << currentNumber << std::endl;
    result += currentNumber;
  }

  std::cout << "Sum: " << result << std::endl;
  return 0;
}