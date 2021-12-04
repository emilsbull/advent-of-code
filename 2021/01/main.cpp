#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
  std::vector<int> measurements {199, 200, 208, 210, 200, 207, 240, 269, 260, 263};

  auto it = measurements.begin();
  auto last = *it++;
  auto timesIncreased = 0;

  for(it; it != measurements.end(); ++it) {
    if(last < *it) {
      timesIncreased++;
    } 
    last = *it;
  }

  std::cout << timesIncreased << std::endl;

}