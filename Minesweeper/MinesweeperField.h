#ifndef MINESWEEPERFIELD_H
#define MINESWEEPERFIELD_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace minesweeper
{
    /// <summary>
    /// Provides the attributes of a single minesweeper field and provides additional functionalities through static methods.
    /// </summary>
    class MinesweeperField
    {
    public:
        /// <summary>
        /// Sets the amount of surrounding bombs for each field.
        /// </summary>
        /// <param name="bombField">The vector that stores the field.</param>
        static void setSurroundingBombs(std::vector<std::vector<MinesweeperField>>& bombField);
        /// <summary>
        /// Initializes the Minesweeper field.
        /// </summary>
        /// <param name="bombField">The vector that stores the field.</param>
        /// <param name="texture">The texture that the field should be initialized with.</param>
        /// <param name="count">the size of the field.</param>
        /// <param name="size">the size of the provided texture.</param>
        /// <param name="bombCount">The amount of bobms that the field should have.</param>
        static void initializeBombField(std::vector<std::vector<MinesweeperField>>& bombField, sf::Texture& texture, const sf::Vector2u fieldSize, const sf::Vector2u size, int bombCount);
        /// <summary>
        /// Counts the amount of flags that are set around the clicked fields.
        /// </summary>
        /// <param name="bombField">The vector that stores the field.</param>
        /// <param name="y">The y coordinate of the clicked field.</param>
        /// <param name="x">The x coordinate of the clicked field.</param>
        /// <returns>The amount of flags that surrounds the clicked field.</returns>
        static int countSurroundingFlags(const std::vector<std::vector<MinesweeperField>>& bombField, const uint64_t y, const uint64_t x);
        /// <summary>
        /// Counts the amount of fields who have been clicked around the selected field.
        /// </summary>
        /// <param name="bombField">The vector that stores the field.</param>
        /// <param name="y">The y coordinate of the clicked field.</param>
        /// <param name="x">The x coordinate of the clicked field.</param>
        /// <returns>The amount of fields that have been clicked around the selected field.</returns>
        static int countSurroundingClickedFields(const std::vector<std::vector<MinesweeperField>>& bombField, const uint64_t y, const uint64_t x);

        MinesweeperField(bool isBomb);

        bool isBomb;
        bool clicked;
        bool isFlag;
        short surroundingBombs;
        sf::Sprite s;
    };
}
#endif // !MINESWEEPERFIELD_H