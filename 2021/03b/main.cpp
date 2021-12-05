#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <cstdint>
#include <bitset>

namespace fs = std::filesystem;

template <int nBits>
bool mostCommonBit(const std::vector<std::bitset<nBits>> &data, std::size_t index)
{
  auto ones = 0U;
  auto zeros = 0U;
  for (auto val : data)
  {
    if (val[index])
    {
      ones++;
    }
    else
    {
      zeros++;
    }
  }
  return ones >= zeros;
}

int main(int, char *[])
{
  constexpr bool readFile = true;
  constexpr int nBits = (readFile ? 12 : 5);

  std::vector<std::bitset<nBits>> measurements;

  if (readFile)
  {
    const std::string path{"input.txt"};
    std::ifstream infile(path, std::ios::in);
    std::string line;
    while (std::getline(infile, line))
    {
      std::istringstream iss(line);
      std::bitset<nBits> a;
      if (!(iss >> a))
      {
        break;
      } // error

      measurements.push_back(a);
    }
    infile.close();

    if (measurements.empty())
    {
      std::cerr << "inputfile empty" << std::endl;
      return -1;
    }
  }
  else
  {
    measurements.assign({0b00100,
                         0b11110,
                         0b10110,
                         0b10111,
                         0b10101,
                         0b01111,
                         0b00111,
                         0b11100,
                         0b10000,
                         0b11001,
                         0b00010,
                         0b01010});
    //                     10110
  }

  // ------ 3b

  auto o2gen(measurements);
  auto co2scrubber(measurements);

  for (auto i = nBits - 1; i >= 0; i--)
  {
    bool mcb = mostCommonBit<nBits>(o2gen, i);
    o2gen.erase(std::remove_if(o2gen.begin(), o2gen.end(), [i, mcb](std::bitset<nBits> bla)
                               { return bla[i] != mcb; }),
                o2gen.end());
    if (o2gen.size() == 1)
    {
      break;
    }
  }

  for (auto i = nBits - 1; i >= 0; i--)
  {
    bool mcb = !mostCommonBit<nBits>(co2scrubber, i);
    co2scrubber.erase(std::remove_if(co2scrubber.begin(), co2scrubber.end(), [i, mcb](std::bitset<nBits> bla)
                                     { return bla[i] != mcb; }),
                      co2scrubber.end());
    if (co2scrubber.size() == 1)
    {
      break;
    }
  }

  std::cout << "o2gen: " << o2gen.at(0) << " - " << o2gen.at(0).to_ullong() << std::endl;
  std::cout << "co2scrubber: " << co2scrubber.at(0) << " - " << co2scrubber.at(0).to_ullong() << std::endl;
  std::cout << "---------------------------" << std::endl;
  std::cout << "Result 03b: " << o2gen.at(0).to_ullong() * co2scrubber.at(0).to_ullong() << std::endl;

  return 0;
}