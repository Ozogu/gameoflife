#pragma once

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

class GameLogic
{
public:
    using Board_t = std::vector<std::vector<bool>>;
    struct Coordinate_t
    {
        int x;
        int y;
        explicit Coordinate_t(int _x, int _y) : x(_x), y(_y) { }
    };

    GameLogic();
    ~GameLogic();
    void Step();
    void SetBoardSize(const int size);
    int GetBoardSize();
    void ToggleCell(Coordinate_t coordinate);
    Board_t GetBoard();

private:
    enum class NeighborCondition { DieLowerLimit = 1, DieUpperLimit = 4, RegrowLimit = 3 };

    std::string EncodeCoordinate(Coordinate_t coordinate);
    Coordinate_t DecodeCoordinate(std::string encoded);
    bool Inbounds(Coordinate_t coordinate);
    void CalculateUpdates();
    int CalculateNeigborsAndUpdateGrowthCandidates(Coordinate_t coordinate);
    void KillLonelyAndOverpopulatedCells();
    void Regrowth();


    int m_boardSize;
    // Current game state
    Board_t m_board;
    // Keep unordered set/map of alive cells and candidates for faster lookup
    std::unordered_set<std::string> m_killCandidates;
    std::unordered_map<std::string, int> m_growthCandidates;
    std::unordered_set<std::string> m_aliveCells;
};

