#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <numeric>
#include <iterator>
#include <cstdio>
#include <variant>

#include "string_utils.h"

struct InstrNoop
{
    static constexpr std::string_view instruction = "noop";
    InstrNoop(){};
    InstrNoop(int64_t*){};
    bool tick()
    {
        return true;
    };
};

struct InstrAdd
{
    static constexpr std::string_view instruction = "addx";
    InstrAdd(int64_t* X, int64_t addr) : arg(addr), X(X)
    {
    }
    bool tick()
    {
        ++phase;
        if (phase != 2)
            return false;
        *X += arg;
        return true;
    }

private:
    int32_t phase{0};
    int64_t arg{0};
    int64_t* X{nullptr};
};

struct Program
{
    Program() : X(std::make_unique<int64_t>(1))
    {
    }

    std::unique_ptr<int64_t> X;
    std::vector<std::variant<InstrNoop, InstrAdd> > instructions;

    int64_t run(std::vector<std::string>& screen, const std::vector<int64_t>& breakpoints)
    {
        int64_t tick = 0;
        int64_t sum = 0;
        auto it = breakpoints.begin();
        for (auto& instruction : instructions) {
            do {
                ++tick;
                if (it != breakpoints.end() && *it == tick) {
                    // puzzle A
                    sum += tick * (*X);
                    ++it;
                }

                // puzzle B
                int64_t pos = (tick - 1) % 40;
                if (pos == 0)
                    screen.push_back("");
                if (pos >= *X - 1 && pos <= *X + 1)
                    screen.back().push_back('#');
                else
                    screen.back().push_back(' ');
            } while (!visit([](auto& i) { return i.tick(); }, instruction));
        }
        return sum;
    }
};

static std::variant<InstrNoop, InstrAdd> getInstruction(const std::string& command, const Program& program)
{
    std::variant<InstrNoop, InstrAdd> decoded;
    std::stringstream s(command);
    std::string encoded;
    s >> encoded;
    if (encoded == InstrNoop::instruction) {
        decoded = InstrNoop();
    } else if (encoded == InstrAdd::instruction) {
        int64_t addr{0};
        if(!(s >> addr)) {
            throw std::runtime_error("Failed parsing InstrAdd.");
        }
        decoded = InstrAdd(program.X.get(), addr);
    } else {
        throw std::runtime_error("Failed parsing program.");
    }
    return decoded;
}

void puzzle(std::vector<std::string> commands)
{
    Program program;
    for(auto& command: commands) {
        program.instructions.emplace_back(getInstruction(command, program));
    }

    std::vector<std::string> screen;

    std::cout << "---------------------" << std::endl;
    std::cout << "output A: " << program.run(screen, {20, 60, 100, 140, 180, 220}) << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "output B: ";
    std::cout << std::endl;
    for(auto& line : screen) {
        std::cout << line << std::endl;
    }
}

int main(int, char*[])
{
    constexpr bool realPuzzle = true;
    const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

    const std::string path{file};
    std::ifstream infile(path, std::ios::in);
    std::string line;

    std::vector<std::string> commands;

    while (std::getline(infile, line)) {
        if (line.empty()) {
            continue;
        }
        commands.push_back(line);
    }

    puzzle(commands);
    return 0;
}