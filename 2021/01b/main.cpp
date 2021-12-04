#include <iostream>
#include <vector>
// #include <experimental/filesystem>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

int main(int , char* [])
{
  const std::string path{"input.txt"};
  // std::vector<int> measurements {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
  std::vector<int> measurements;

  std::ifstream infile(path, std::ios::in);
  std::string line;
  while (std::getline(infile, line))
  {
      std::istringstream iss(line);
      int a;
      if (!(iss >> a)) { break; } // error

      measurements.push_back(a);
  }
  infile.close();

  if (measurements.empty() || measurements.size() < 3) {
    std::cerr << "inputfile empty" << std::endl;
    return -1;
  }

  auto lastSum = measurements[0] + measurements[1] + measurements[2];
  auto timesIncreased = 0;

  for (std::size_t i = 3; i < measurements.size(); ++ i) {
    auto sum = measurements[i - 2] + measurements[i -1] + measurements[i];
    if(lastSum < sum) {
      timesIncreased++;
    } 
    lastSum = sum;
  }

  std::cout << timesIncreased << std::endl;
  return 0;
}