#include "ui/ui.hpp"
#include "gamelogic/gamelogic.hpp"
#include "statemachine/statemachine.hpp"

int main()
{
    GameLogic Game;
    UI Ui;
    Statemachine Machine;

    Ui.Clear();
    Ui.Intro();

    while (true)
    {
        Machine.Task(Ui, Game);
    }
}