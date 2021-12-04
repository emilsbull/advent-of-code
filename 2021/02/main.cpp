#include <iostream>
#include <vector>
// #include <experimental/filesystem>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>

namespace fs = std::filesystem;

int main(int , char* [])
{
  const std::string path{"input.txt"};
  // std::vector<int> measurements {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};
  std::vector<std::tuple<std::string, int>> measurements;

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

  const std::string forward{"forward"};
  const std::string down{"down"};
  const std::string up{"up"};

  auto posHorizontal = 0;
  auto posDepth = 0;

  for(auto val : measurements) {
    const auto& [command, value] = val;

    if(forward.compare(command) == 0) {
        posHorizontal += value;
    } else if (down.compare(command) == 0) {
        posDepth += value;
    }else if (up.compare(command) == 0) {
        posDepth -= value;
    } else {
      std::cerr << "unknown command " << command << std::endl;
    }
  }

  std::cout << "Result: " << posDepth * posHorizontal << std::endl;

  return 0;
}