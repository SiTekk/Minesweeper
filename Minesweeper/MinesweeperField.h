#ifndef MINESWEEPERFIELD_H
#define MINESWEEPERFIELD_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace minesweeper
{
    class MinesweeperField
    {
    public:
        MinesweeperField(bool isBomb);
        static void setSurroundingBombs(std::vector<std::vector<MinesweeperField>>& bombField);
        static void initializeBombField(std::vector<std::vector<MinesweeperField>>& bombField, sf::Texture& texture, sf::Vector2u count, sf::Vector2u size, int bombCount);
        static int countSurroundingFlags(std::vector<std::vector<MinesweeperField>> bombField, int y, int x);
        static int countSurroundingClickedFields(std::vector<std::vector<MinesweeperField>> bombField, int y, int x);
        bool isBomb;
        bool clicked;
        bool isFlag;
        short surroundingBombs;
        sf::Sprite s;
    };
}
#endif // !MINESWEEPERFIELD_H