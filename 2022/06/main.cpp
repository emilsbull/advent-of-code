#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <ranges>
#include <string>

auto is_marker(std::string s) -> bool {
    std::ranges::sort(s);
    return std::ranges::unique(s).begin() == s.end();
}

auto first_marker(std::string_view buffer, int marker_length) -> int {
    return (std::views::iota(marker_length)
          | std::views::transform([&](int i) { return std::make_pair(i, buffer.substr(i - marker_length, marker_length)); })
          | std::views::filter([&](const std::pair<int, std::string_view>& p) { return is_marker(std::string(p.second)); })
          | std::views::take(1)).front().first;
}

auto main() -> int {

  constexpr bool readFile = false;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  while (std::getline(infile, line))
  {
    if (line.empty())
    {
      continue;
    }
    std::cout << "result A:" << first_marker(line, 4) << std::endl;
    std::cout << "result B:" << first_marker(line, 14) << std::endl;
  }
}