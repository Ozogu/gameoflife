#include <unistd.h>

#include "statemachine/statemachine.hpp"

Statemachine::Statemachine() : m_state(State::GetBoardSize), m_refreshrate_us(500'000)
{
}

Statemachine::~Statemachine()
{
}

void Statemachine::Task(UI &Ui, GameLogic &Game)
{
    switch (m_state)
    {
    case State::GetBoardSize:
        m_state = GetBoardSize(Ui, Game);
        break;
    case State::PreRun:
        m_state = PreRun(Ui, Game);
        break;
    case State::Run:
        Run(Ui, Game);
    default:
        break;
    }
}

// Private

Statemachine::State Statemachine::GetBoardSize(UI &Ui, GameLogic &Game)
{
    State NextState = State::GetBoardSize;
    int BoardSize = 0;
    if (Ui.GetBoardSizeFromInput(BoardSize))
    {
        NextState = State::PreRun;
        Game.SetBoardSize(BoardSize);
        Ui.Clear();
        Ui.Draw(Game);
        Ui.PrintPrerunInstruction();
    }

    return NextState;
}

Statemachine::State Statemachine::PreRun(UI &Ui, GameLogic &Game)
{
    State nextState = State::PreRun;

    UI::PrerunInput_t input = Ui.GetUserPrerunInput(Game);
    if (input.success)
    {
        switch (input.command)
        {
        case UI::PrerunCommand::Run:
            nextState = State::Run;
            break;
        case UI::PrerunCommand::Step:
            Game.Step();
            break;
        case UI::PrerunCommand::Toggle:
            Game.ToggleCell(GameLogic::Coordinate_t(input.x, input.y));
            break;
        default:
            break;
        }

        Ui.Clear();
        Ui.Draw(Game);
        Ui.PrintPrerunInstruction();
    }

    return nextState;
}

void Statemachine::Run(UI &Ui, GameLogic &Game)
{
    while (true)
    {
        Game.Step();
        Ui.Clear();
        Ui.Draw(Game);
        usleep(m_refreshrate_us);
    }
}

