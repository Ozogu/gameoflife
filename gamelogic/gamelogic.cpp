#include <limits.h>

#include "gamelogic/gamelogic.hpp"
#include "stringutils/stringutils.hpp"

GameLogic::GameLogic() : m_boardSize(0), m_board(0), m_killCandidates(0),
                         m_growthCandidates(0), m_aliveCells(0)
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::Step()
{
    CalculateUpdates();
    KillLonelyAndOverpopulatedCells();
    Regrowth();

    m_killCandidates.clear();
    m_growthCandidates.clear();
}

void GameLogic::ToggleCell(Coordinate_t coordinate)
{
    // ^= operator is not supported for vector
    m_board[coordinate.y][coordinate.x] = m_board[coordinate.y][coordinate.x] ^ true;

    std::string encoded = EncodeCoordinate(coordinate);
    if (m_aliveCells.contains(encoded))
    {
        m_aliveCells.erase(encoded);
    }
    else
    {
        m_aliveCells.insert(encoded);
    }
}

void GameLogic::SetBoardSize(const int size)
{
    m_boardSize = size;
    m_board = Board_t(size, std::vector<bool>(size, false));
}

int GameLogic::GetBoardSize()
{
    return m_boardSize;
}

GameLogic::Board_t GameLogic::GetBoard()
{
    return m_board;
}

// Private

inline std::string GameLogic::EncodeCoordinate(Coordinate_t coordinate)
{
    return std::to_string(coordinate.x) + " " + std::to_string(coordinate.y);
}

inline GameLogic::Coordinate_t GameLogic::DecodeCoordinate(std::string encoded)
{
    auto splitList = StringUtils::Split(encoded, ' ');
    return Coordinate_t(std::stoi(splitList[0]), std::stoi(splitList[1]));
}

inline bool GameLogic::Inbounds(Coordinate_t coordinate)
{
    return coordinate.x >= 0 && coordinate.x < m_boardSize &&
        coordinate.y >= 0 && coordinate.y < m_boardSize;
}

void GameLogic::CalculateUpdates()
{
    for (auto cell : m_aliveCells)
    {
        auto coordinate = DecodeCoordinate(cell);
        m_growthCandidates[EncodeCoordinate(coordinate)] = INT_MIN;

        auto neighbors = CalculateNeigborsAndUpdateGrowthCandidates(coordinate);
        if (neighbors <= static_cast<int>(NeighborCondition::DieLowerLimit) ||
            neighbors >= static_cast<int>(NeighborCondition::DieUpperLimit))
        {
            m_killCandidates.insert(cell);
        }
    }
}

void GameLogic::KillLonelyAndOverpopulatedCells()
{
    for (auto cell : m_killCandidates)
    {
        ToggleCell(DecodeCoordinate(cell));
    }
}

void GameLogic::Regrowth()
{
    for (auto cell : m_growthCandidates)
    {
        if (cell.second == static_cast<int>(NeighborCondition::RegrowLimit))
        {
            ToggleCell(DecodeCoordinate(cell.first));
        }
    }
}

int GameLogic::CalculateNeigborsAndUpdateGrowthCandidates(Coordinate_t coordinate)
{
    const auto neighbors = std::vector<Coordinate_t>
    {
        Coordinate_t(1, 1),
        Coordinate_t(1, 0),
        Coordinate_t(1, -1),

        Coordinate_t(-1, 1),
        Coordinate_t(-1, 0),
        Coordinate_t(-1, -1),

        Coordinate_t(0, -1),
        Coordinate_t(0, 1),
    };

    int neighborCount = 0;
    for (auto neighbor : neighbors)
    {
        int neighborX = neighbor.x + coordinate.x;
        int neighborY = neighbor.y + coordinate.y;
        if (Inbounds(Coordinate_t(neighborX, neighborY)))
        {
            neighborCount += static_cast<int>(m_board[neighborY][neighborX]);
            m_growthCandidates[EncodeCoordinate(Coordinate_t(neighborX, neighborY))] += 1;
        }
    }

    return neighborCount;
}