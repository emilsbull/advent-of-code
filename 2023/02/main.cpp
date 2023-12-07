#include <fstream>
#include <iostream>
#include <vector>
#include <ranges>
#include <array>
#include <algorithm>
#include <sstream>

#include "string_utils.h"

struct Cubes
{
    int red = 0;
    int blue = 0;
    int green = 0;

    bool operator<(const Cubes& c)
    {
        return (red < c.red) || (blue < c.blue) || (green < c.green);
    }
};

class Game
{
public:
    Game(Cubes limit)
        : mLimit(limit){

          };
    Cubes mLimit;
    int ID = 0;
    std::vector<Cubes> picks;

    bool possible()
    {
        bool win = true;
        std::for_each(picks.cbegin(), picks.cend(), [&win, this](const Cubes& other) {
            if (this->mLimit < other) {
                win = false;
            }
        });
        return win;
    }
};

Game parse(std::string input)
{
    Game game({12, 14, 13});

    auto split = utils::splitString(input, ":");
    std::string gameStr = split.at(0);
    std::stringstream s(gameStr);

    std::string dummyStr;
    s >> dummyStr >> game.ID;

    auto picks = utils::splitString(split.at(1), ";");

    for (auto pick : picks) {
        Cubes cubes;
        auto in = utils::splitString(pick, ",");
        for (auto col : in) {
            col = utils::trim(col);
            int num;
            std::string color;
            std::stringstream ss(col);
            ss >> num >> color;
            if (color == "red") {
                cubes.red = num;
            } else if (color == "blue") {
                cubes.blue = num;
            } else if (color == "green") {
                cubes.green = num;
            }
        }
        game.picks.push_back(cubes);
    }

    return game;
}

void puzzle(const std::vector<std::string>& commands)
{
    int sum = 0;
    for (auto& command : commands) {
        Game g = parse(command);
        if (g.possible()) {
            sum += g.ID;
        }
    }
    std::cout << "---------------------" << std::endl;
    std::cout << "output A:" << sum;
    std::cout << std::endl;

    std::cout << "---------------------" << std::endl;
    std::cout << "output b:"
              << "sum";
    std::cout << std::endl;
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