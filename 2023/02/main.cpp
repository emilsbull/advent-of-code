#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "utils/fileinput.h"
#include "utils/string_utils.h"

struct Cube
{
    int red = 0;
    int blue = 0;
    int green = 0;

    bool operator<(const Cube& c)
    {
        return (red < c.red) || (blue < c.blue) || (green < c.green);
    }

    Cube min(const Cube& o)
    {
        return {std::max(red, o.red), std::max(blue, o.blue), std::max(green, o.green)};
    }

    int power()
    {
        return red * blue * green;
    }
};

class Game
{
public:
    Game(Cube limit)
        : mLimit(limit){

          };
    Cube mLimit;
    int ID = 0;
    std::vector<Cube> picks;

    bool possible()
    {
        bool win = true;
        std::for_each(picks.cbegin(), picks.cend(), [&win, this](const Cube& other) {
            if (this->mLimit < other) {
                win = false;
            }
        });
        return win;
    }

    Cube minSet()
    {
        Cube ret;

        for (auto& pick : picks) {
            ret = ret.min(pick);
        }

        return ret;
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
        Cube cubes;
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
    int power = 0;
    std::vector<Game> games;

    for (auto& command : commands) {
        games.emplace_back(parse(command));
    }

    for (auto& g : games) {
        if (g.possible()) {
            sum += g.ID;
        }
        power += g.minSet().power();
    }
    std::cout << "---------------------" << std::endl;
    std::cout << "output A:" << sum;
    std::cout << std::endl;

    std::cout << "---------------------" << std::endl;
    std::cout << "output b:" << power;
    std::cout << std::endl;
}

int main(int /*argc*/, char* argv[])
{
    constexpr bool realPuzzle = false;
    const std::string file{(realPuzzle ? "input1.txt" : "input.txt")};

    std::string file_path = utils::getInputFilePath(argv[0], file);
    if (file_path.empty()) {
        std::cerr << "Error: Could not determine the input file path for " << file_path << ".\n";
        return 1;
    }
    std::ifstream infile(file_path, std::ios::in);
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
