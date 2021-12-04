#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>

namespace fs = std::filesystem;

int main(int , char* [])
{
  constexpr bool readFile = true;

  const std::string forward{"forward"};
  const std::string down{"down"};
  const std::string up{"up"};

  std::vector<std::tuple<std::string, int>> measurements;

  if(readFile) {
    const std::string path{"input.txt"};
    std::ifstream infile(path, std::ios::in);
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        std::string a;
        int b;
        if (!(iss >> a >> b)) { break; } // error

        measurements.push_back({a, b});
    }
    infile.close();

    if (measurements.empty()) {
      std::cerr << "inputfile empty" << std::endl;
      return -1;
    }
  } else {
    measurements.assign({{forward, 5}, {down, 5}, {forward, 8}, {up, 3}, {down,8}, {forward, 2}});
  }

  auto posHorizontal = 0;
  auto posDepth = 0;
  auto aim = 0;

  for(auto val : measurements) {
    const auto& [command, value] = val;

    if(forward.compare(command) == 0) {
        posHorizontal += value;
        posDepth += aim * value;
    } else if (down.compare(command) == 0) {
        aim += value;
    }else if (up.compare(command) == 0) {
        aim -= value;
    } else {
      std::cerr << "unknown command " << command << std::endl;
    }
  }
  std::cout << "Horizontal: " << posHorizontal << std::endl;
  std::cout << "Depth: " << posDepth << std::endl;
  std::cout << "Aim: " << aim << std::endl;
  std::cout << "---------------------------" << std::endl;
  std::cout << "Result: " << posDepth * posHorizontal << std::endl;

  return 0;
}