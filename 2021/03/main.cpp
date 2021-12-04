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

int main(int , char* [])
{
  constexpr bool readFile = true;
  constexpr int nBits = (readFile ? 12 : 5);
  
  std::vector<std::bitset<nBits>> measurements;

  if(readFile) {
    const std::string path{"input.txt"};
    std::ifstream infile(path, std::ios::in);
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::bitset<nBits> a;
        if (!(iss >> a)) { break; } // error

        measurements.push_back(a);
    }
    infile.close();

    if (measurements.empty()) {
      std::cerr << "inputfile empty" << std::endl;
      return -1;
    }
  } else {
    measurements.assign({
      0b00100, 
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
    //  10110
  }
  
  std::bitset<nBits> gamma;
  std::bitset<nBits> epsilon;

  auto ones = 0;
  auto zeros = 0;

  for(int i = 0; i < nBits; ++i) {
    zeros = 0;
    ones = 0;
      for(auto& val: measurements) {
        bool bit = val[i] > 0;
        if (!bit) {
          zeros++;
        } else {
          ones++;
        }
      }
    if (zeros > ones) {
      epsilon.set(i, true);
    } else {
      gamma.set(i, true);
    }
  }

  std::cout << "gamma: " << gamma << std::endl;
  std::cout << "epsilon: " << epsilon << std::endl;
  std::cout << "---------------------------" << std::endl;
  std::cout << "Result: " << gamma.to_ulong() * epsilon.to_ulong() << std::endl;

  return 0;
}