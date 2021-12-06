#include <iostream>

#include "ui/ui.hpp"
#include "stringutils/stringutils.hpp"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Intro()
{
    std::cout << "Welcome to the game of life!" << std::endl << std::endl;
}

bool UI::GetBoardSizeFromInput(int& BoardSize)
{
    bool success = false;
    std::string input;
    std::cout << "Input Board size" << std::endl << ">> ";
    std::getline(std::cin, input);
    if (StringUtils::isNumber(input))
    {
        BoardSize = std::stoi(input);
        success = true;
    }
    else
    {
        std::cout << "Not a number!" << std::endl;
    }

    return success;
}

void UI::Clear()
{
    auto retval = system("clear");
    (void)retval;
}

void UI::Draw(GameLogic& Game)
{
    // Print board and Y coordinate
    int indexY = 0;
    for (auto i : Game.GetBoard())
    {
        for (auto j : i)
        {
            auto token = j ? "X" : ".";
            std::cout << token << " ";
        }
        std::cout << indexY << std::endl;
        indexY++;
    }

    // Print X coordinate.
    int size = Game.GetBoardSize();
    for (int i = 0; i < size; i++)
    {
        std::cout << i % 10 << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < size; i++)
    {
        if (i % 10 == 0)
        {
            std::cout << i % 100 / 10 << " ";
        }
        else
        {
            std::cout << "  ";
        }
    }
    std::cout << std::endl;
}

void UI::NotifyBoardSizeSet(const int size)
{
    std::cout << "Board size set to " << size << std::endl;
}

void UI::PrintPrerunInstruction()
{
    std::cout << "Toggle cells in Board by entering space separated coordinate (Ex. \"1 3\")" << std::endl;
    std::cout << "Start the game with \"run\" or \"step\"" << std::endl;
}

UI::PrerunInput_t UI::GetUserPrerunInput(GameLogic& Game)
{
    PrerunInput_t retval = { false, PrerunCommand::Run, 0, 0 };
    std::string input;

    std::cout << ">> ";

    std::getline(std::cin, input);
    auto splitList = StringUtils::Split(input, ' ');

    int boardSize = Game.GetBoardSize();
    if (input == "run")
    {
        retval.command = PrerunCommand::Run;
        retval.success = true;
    }
    else if (input == "step")
    {
        retval.command = PrerunCommand::Step;
        retval.success = true;
    }
    else if (splitList.size() != 2)
    {
        std::cout << "Incorrect format: wrong number of elements!" << std::endl;
    }
    else if (!StringUtils::isNumber(splitList[0]) || !StringUtils::isNumber(splitList[1]))
    {
        std::cout << "Incorrect format: Input is not a number!" << std::endl;
    }
    else
    {
        int x = std::stoi(splitList[0]);
        int y = std::stoi(splitList[1]);

        if (x >= boardSize || y >= boardSize || x < 0 || y < 0)
        {
            std::cout << "Incorrect format: Input is out of Board range! (0-" << boardSize-1 << ")" << std::endl;
        }
        else
        {
            retval.command = PrerunCommand::Toggle;
            retval.success = true;
            retval.x = x;
            retval.y = y;
        }
    }

    return retval;
}
