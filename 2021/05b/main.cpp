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

struct vec2
{
  int x{0};
  int y{0};
};

enum class Direction
{
  Horizontal,
  Vertical,
  Diagonal
};

class Command
{
public:
  explicit Command(std::string input)
  {

    std::regex rex("[^0-9]+");
    std::regex_token_iterator<std::string::iterator> i(input.begin(), input.end(), rex, -1);

    start.x = std::stoi(*i++);
    start.y = std::stoi(*i++);
    end.x = std::stoi(*i++);
    end.y = std::stoi(*i++);
  }

  void print()
  {
    std::cout << "start(" << start.x << "|" << start.y << ") end(" << end.x << "|" << end.y << ")" << std::endl;
  }

  std::tuple<vec2, Direction, vec2> get()
  {
    if (start.x == end.x)
    {
      if (start.y > end.y)
      {
        std::swap(start, end);
      }
      return std::make_tuple(start, Direction::Horizontal, end);
    }
    else if (start.y == end.y)
    {
      if (start.x > end.x)
      {
        std::swap(start, end);
      }
      return std::make_tuple(start, Direction::Vertical, end);
    }
    else
    {
      if (start.x > end.x)
      {
        std::swap(start, end);
      }
      return std::make_tuple(start, Direction::Diagonal, end);
    }
  }

private:
  vec2 start;
  vec2 end;
};

template <int width, int height>
class Board
{
public:
  Board()
  {
    for (auto &row : board)
    {
      std::fill(row.begin(), row.end(), 0);
    }
  }

  void draw(Command cmd)
  {
    auto [start, direction, end] = cmd.get();

    switch (direction)
    {
    case Direction::Horizontal:
      for (; start.y <= end.y; start.y++)
      {
        board[start.x][start.y]++;
      }
      break;
    case Direction::Vertical:
      for (; start.x <= end.x; start.x++)
      {
        board[start.x][start.y]++;
      }
      break;
    case Direction::Diagonal:
    default:
      for (; start.x <= end.x; start.x++)
      {
        board[start.x][start.y]++;
        if (start.y < end.y)
        {
          start.y++;
        }
        else
        {
          start.y--;
        }
      }
      break;
    }
  }

  void print()
  {
    for (auto row : board)
    {
      for (auto val : row)
      {
        if (val > 0)
        {
          std::cout << val;
        }
        else
        {
          std::cout << ".";
        }
      }
      std::cout << std::endl;
    }
  }

  int eval()
  {
    int retVal = 0;
    for (auto row : board)
    {
      for (auto val : row)
      {
        if (val >= 2)
        {
          retVal++;
        }
      }
    }
    return retVal;
  }

private:
  std::array<std::array<int, width>, height> board;
};

int main(int, char *[])
{
  constexpr bool readFile = true;
  constexpr int boardWidth = (readFile ? 1000 : 10);
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  std::vector<Command> commands;

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;
  while (std::getline(infile, line))
  {
    commands.emplace_back(line);
  }
  infile.close();

  if (commands.empty())
  {
    std::cerr << "inputfile empty" << std::endl;
    return -1;
  }

  Board<boardWidth, boardWidth> board;
  for (auto cmd : commands)
  {
    board.draw(cmd);
  }
  board.print();

  std::cout << "Result: " << board.eval() << std::endl;

  return 0;
}