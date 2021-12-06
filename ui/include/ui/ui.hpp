#pragma once

#include <vector>
#include <string>

#include "gamelogic/gamelogic.hpp"

class UI
{
public:
    enum class PrerunCommand { Run, Step, Toggle };
    struct PrerunInput_t
    {
        bool success;
        PrerunCommand command;
        int x;
        int y;
    };

    UI();
    ~UI();
    void Draw(GameLogic& Game);
    void Clear();
    void Intro();
    void NotifyBoardSizeSet(const int size);
    void PrintPrerunInstruction();
    bool GetBoardSizeFromInput(int& gridSize);
    PrerunInput_t GetUserPrerunInput(GameLogic& Game);
};

