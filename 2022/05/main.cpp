#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <cstdint>
#include <map>
#include <numeric>
#include <iterator>
#include <cstdio>

#include "string_utils.h"

namespace fs = std::filesystem;

struct Action {
  int n;
  int from;
  int to;
};

class Stacks {
  public:
  Stacks(std::vector<std::string> input) {
    auto numbers = input.back();
    input.pop_back();

    for(size_t i = 0; i < numbers.size(); ++i) {
      auto c = numbers.at(i);
      if(c != ' ') {
        crates.emplace_back();
        for(auto lineIter = input.rbegin(); lineIter != input.rend(); ++lineIter)
        {
          char crateChar = (*lineIter).at(i);
          if (crateChar == ' ')
            break;
          crates.back().push(crateChar);
        }
      }
    }
  }

  void move(Action a) {
    while(a.n > 0) {
      auto& fromStack = crates.at(a.from-1);
      auto& toStack = crates.at(a.to-1);
      auto tmp = fromStack.top();
      fromStack.pop();
      toStack.push(tmp);
      --a.n;
    }
  }

  

  void CrateMover9001(Action a) {
    auto& fromStack = crates.at(a.from-1);
    auto& toStack = crates.at(a.to-1);
    std::deque<char> tinyStack;

    while(a.n > 0) {
      auto tmp = fromStack.top();
      fromStack.pop();
      tinyStack.push_front(tmp);
      --a.n;
    }

    for(auto bla : tinyStack) {
      toStack.push(bla);
    }
  }

  void print() {
    for(auto stack : crates) {
      std::cout << stack.top();
    }
  }

  private:
    std::vector<std::stack<char>> crates;
};


void puzzleA(Stacks stacks, std::vector<Action> actions)
{
  for(auto a : actions) {
    stacks.move(a);
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "output A:";
  stacks.print();
  std::cout << std::endl;
}

void puzzleB(Stacks stacks, std::vector<Action> actions)
{
  for(auto a : actions) {
    stacks.CrateMover9001(a);
  }

  std::cout << "---------------------" << std::endl;
  std::cout << "output B:";
  stacks.print();
  std::cout << std::endl;
}

int main(int, char *[])
{
  constexpr bool readFile = false;
  const std::string file{(readFile ? "input.txt" : "input1.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::vector<std::string> state;
  std::vector<std::string> commands;

  std::vector<std::string>* pt = &state; 

  while (std::getline(infile, line))
  {
    if (line.empty())
    {
      pt = &commands;
      continue;
    }
    pt->push_back(line);
  }

  Stacks s(state);
  std::vector<Action> actions;

  for(auto &a : commands) {
    Action tmp;
    sscanf(a.c_str(), "move %d from %d to %d", &tmp.n, &tmp.from, &tmp.to);
    actions.push_back(tmp);
  }

  puzzleA(s, actions);
  puzzleB(s, actions);
  return 0;
}