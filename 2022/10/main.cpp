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

void puzzleA(std::vector<std::string> commands)
{
  int registerX = 1;
  int cycle = 0;
  int result = 0;

  std::vector<int> stops{20, 60, 100, 140, 180, 220};

  auto nextStep = [&]() {
    cycle++;
    if (std::find(stops.begin(), stops.end(), cycle) != stops.end())
    {
      result += (cycle * registerX);
    }
  };

  for (auto &line : commands)
  {
    nextStep();
    if (line.compare("noop") != 0)  {
      nextStep();
      auto addx = utils::splitString(line, " ");
      registerX += std::stoi(addx[1]);
    }
  }
  std::cout << "---------------------" << std::endl;
  std::cout << "output A:" << result;
  std::cout << std::endl;
}

struct Cpu
{
    uint64_t num_cycles{1};

    struct instruction
    { 
        enum opcode { NOOP, ADDX } opcode{NOOP};
        int64_t remaining_cycles{0};
        int64_t immediate{0};
    } instruction;

    char line[41]{'\0'};

    struct registers
    {
        int64_t X{1};
    } registers;

    bool is_instruction_finished() const {
        return instruction.remaining_cycles == 0;
    }

    void run_cycle() {
        // Update the line
        int64_t pos = (num_cycles - 1) % 40;
        if (std::abs(pos - registers.X) <= 1) {
            line[pos] = '#';
        } else {
            line[pos] = '.';
        }

        if (!is_instruction_finished()) {
            instruction.remaining_cycles--;
        }
        if (instruction.opcode == instruction.ADDX && is_instruction_finished()) {
            registers.X += instruction.immediate;
        }
        num_cycles++;
    }

    int64_t get_signal_strength() const 
    {
        return registers.X * num_cycles;
    }

    bool is_interesting_cycle() const
    {
        return num_cycles >= 20 && num_cycles <= 220 && ((num_cycles - 20) % 40 == 0);
    }
};

void puzzleB(std::vector<std::string> commands)
{
  std::cout << "---------------------" << std::endl;
  std::cout << "output B:";
  std::cout << std::endl;

  Cpu cpu;

  for(auto& line : commands) {
    std::stringstream ss{line};
    char dummy[5];
    int64_t immediate;

    // Fetch and decode
    if (line[0] == 'n') {
      cpu.instruction.opcode           = cpu.instruction.NOOP;
      cpu.instruction.remaining_cycles = 1;
    } else if (line[0] == 'a') {
      ss.read(dummy, 5);
      ss >> immediate;
      cpu.instruction.opcode           = cpu.instruction.ADDX;
      cpu.instruction.immediate        = immediate;
      cpu.instruction.remaining_cycles = 2;
    }
    
    // Execute
    while (!cpu.is_instruction_finished()) {
      cpu.run_cycle();
      if (cpu.num_cycles > 1 && (cpu.num_cycles - 1) % 40 == 0) {
        std::cout << cpu.line << std::endl;
      }
    }
  }
}

int main(int, char *[])
{
  constexpr bool realPuzzle = true;
  const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

  const std::string path{file};
  std::ifstream infile(path, std::ios::in);
  std::string line;

  std::vector<std::string> commands;

  while (std::getline(infile, line))
  {
    if (line.empty())
    {
      continue;
    }
    commands.push_back(line);
  }

  puzzleA(commands);
  puzzleB(commands);
  return 0;
}