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

// template <std::size_t heigth, std::size_t width>
class Board
{
public:
  explicit Board(const std::array<std::array<int, 5>, 5> &values)
  {
    for (auto i = 0U; i < values.size(); ++i)
    {
      for (auto j = 0U; j < values[i].size(); ++j)
      {
        board[i][j] = std::make_tuple(values[i][j], false);
      }
    }
  }

  std::pair<bool, int> bingo(int key)
  {
    for (auto i = 0U; i < board.size(); ++i)
    {
      for (auto j = 0U; j < board[i].size(); ++j)
      {
        auto [number, found] = board[i][j];
        if (number == key)
        {
          board[i][j] = std::make_tuple(number, true);
          if (checkBingo(i, j))
          {
            return {true, sumUnchecked()};
          }
        }
      }
    }
    return {false, -1};
  }
  friend std::ostream &operator<<(std::ostream &out, const Board &o);

private:
  std::array<std::array<std::tuple<int, bool>, 5>, 5> board;

  int sumUnchecked()
  {
    int retVal = 0;
    for (auto row : board)
    {
      for (auto val : row)
      {
        auto [num, hit] = val;
        if (!hit)
        {
          retVal += num;
        }
      }
    }
    return retVal;
  }

  bool checkHorizontal(std::size_t index)
  {
    auto row = board[index];
    bool retVal = true;
    for (auto val : row)
    {
      retVal &= std::get<1>(val);
    }
    return retVal;
  }

  bool checkVertical(std::size_t index)
  {
    bool retVal = true;
    for (auto row : board)
    {
      retVal &= std::get<1>(row[index]);
    }
    return retVal;
  }

  bool checkBingo(std::size_t row, std::size_t col)
  {
    return checkHorizontal(row) || checkVertical(col);
  }
};

std::ostream &operator<<(std::ostream &out, const Board &y)
{
  std::stringstream ss;
  for (auto row : y.board)
  {
    for (auto [val, hit] : row)
    {
      ss << std::setfill(' ') << std::setw(3) << val << std::setw(1) << (hit ? "*" : "");
    }
    ss << std::endl;
  }

  return out << ss.str();
}

int main(int, char *[])
{
  constexpr int boardWidth = 5;
  constexpr bool readFile = true;
  const std::string filename{(readFile ? "input.txt" : "input1.txt")};

  std::vector<int> numbers;
  std::vector<Board> boards;

  const std::string path{filename};
  std::ifstream infile(path, std::ios::in);
  std::string line;
  // parse numbers
  std::getline(infile, line);

  std::stringstream ss(line);

  for (int i; ss >> i;)
  {
    numbers.push_back(i);
    if (ss.peek() == ',')
    {
      ss.ignore();
    }
  }
  // empty line
  std::getline(infile, line);
  if (!line.empty())
  {
    std::cerr << "parser Error" << std::endl;
    return -3;
  }
  // parse boards
  std::array<std::array<int, 5>, 5> boardValues;
  int i = 0;

  while (std::getline(infile, line))
  {
    if (line.empty())
    {
      boards.emplace_back(boardValues);
      i = 0;
      continue;
    }
    std::istringstream iss(line);

    for (int j = 0; j < boardWidth; ++j)
    {
      int a;
      if (!(iss >> a))
      {
        continue;
      } // error
      boardValues[i][j] = a;
    }
    i++;
  }
  boards.emplace_back(boardValues);
  infile.close();

  if (boards.empty() || numbers.empty())
  {
    std::cerr << "inputfile empty" << std::endl;
    return -1;
  }

  bool bingo{false};
  int sumUnchecked{-1};
  int bingoNumber;

  for (auto number : numbers)
  {
    std::cout << "NUMBER: " << number << std::endl;
    for (auto &board : boards)
    {
      auto [b, sum] = board.bingo(number);
      std::cout << board << std::endl;
      std::cout << "-----" << std::endl;
      if (b)
      {
        bingo = true;
        bingoNumber = number;
        sumUnchecked = sum;
        break;
      }
    }
    if (bingo)
    {
      break;
    }
  }

  std::cout << "---------------------------" << std::endl;
  std::cout << (bingo ? "WE HAVE A BINGO!" : "no bingo :(") << std::endl;
  std::cout << "sum unchecked: " << sumUnchecked << " bingo number: " << bingoNumber << std::endl;
  std::cout << "Result 04: " << sumUnchecked * bingoNumber << std::endl;

  return 0;
}