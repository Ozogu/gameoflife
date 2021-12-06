#pragma once

#include "gamelogic/gamelogic.hpp"
#include "ui/ui.hpp"

class Statemachine
{
public:
    Statemachine();
    ~Statemachine();
    void Task(UI &Ui, GameLogic &Game);
private:
    enum class State { GetBoardSize, PreRun, Run };

    State GetBoardSize(UI &Ui, GameLogic &Game);
    State PreRun(UI &Ui, GameLogic &Game);
    void Run(UI &Ui, GameLogic &Game);

    State m_state;
    int m_refreshrate_us;
};

