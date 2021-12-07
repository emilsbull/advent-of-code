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

// Function for calculating
// the median
double findMedian(std::vector<int> a,
                  int n)
{

  // If size of the arr[] is even
  if (n % 2 == 0)
  {

    // Applying nth_element
    // on n/2th index
    std::nth_element(a.begin(),
                     a.begin() + n / 2,
                     a.end());

    // Applying nth_element
    // on (n-1)/2 th index
    std::nth_element(a.begin(),
                     a.begin() + (n - 1) / 2,
                     a.end());

    // Find the average of value at
    // index N/2 and (N-1)/2
    return (double)(a[(n - 1) / 2] + a[n / 2]) / 2.0;
  }

  // If size of the arr[] is odd
  else
  {

    // Applying nth_element
    // on n/2
    std::nth_element(a.begin(),
                     a.begin() + n / 2,
                     a.end());

    // Value at index (N/2)th
    // is the median
    return (double)a[n / 2];
  }
}

int getFuel(const std::vector<int> &input, int pos)
{
  int fuel = 0;

  for (auto crab : input)
  {
    fuel += std::abs(crab - pos);
  }

  return fuel;
}

int main(int, char *[])
{
  constexpr bool readFile = true;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  std::vector<int> input;

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;
  while (std::getline(infile, line))
  {
    std::stringstream sstream(line);
    while (sstream.good())
    {
      std::string substr;
      std::getline(sstream, substr, ',');
      auto val = std::atoi(substr.c_str());
      input.push_back(val);
    }
  }

  int median = static_cast<int>(findMedian(input, input.size()));

  std::cout << "Median: " << median << std::endl;
  std::cout << "Fuel Cost: " << getFuel(input, median) << std::endl;
  return 0;
}