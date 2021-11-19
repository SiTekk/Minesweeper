#include <iostream>
#include "MinesweeperField.h"

using namespace std;
using namespace sf;

namespace minesweeper
{
    MinesweeperField::MinesweeperField(bool isBomb)
    {
        this->isBomb = isBomb;
        surroundingBombs = 0;
        clicked = false;
        isFlag = false;
    }

    void MinesweeperField::setSurroundingBombs(vector<vector<MinesweeperField>>& bombField)
    {
        for (uint64_t i = 0; i < bombField.size(); i++)
        {
            for (uint64_t k = 0; k < bombField[i].size(); k++)
            {
                try
                {
                    if (i > 0)
                    {
                        if (k > 0)
                            bombField.at(i).at(k).surroundingBombs += bombField.at(i - 1).at(k - 1).isBomb ? 1 : 0;
                        bombField.at(i).at(k).surroundingBombs += bombField.at(i - 1).at(k).isBomb ? 1 : 0;
                        if (k + 1 < bombField[i].size())
                            bombField.at(i).at(k).surroundingBombs += bombField.at(i - 1).at(k + 1).isBomb ? 1 : 0;
                    }
                    if (k > 0)
                        bombField.at(i).at(k).surroundingBombs += bombField.at(i).at(k - 1).isBomb ? 1 : 0;
                    if (k + 1 < bombField[i].size())
                        bombField.at(i).at(k).surroundingBombs += bombField.at(i).at(k + 1).isBomb ? 1 : 0;
                    if (i + 1 < bombField.size())
                    {
                        if (k  > 0)
                            bombField.at(i).at(k).surroundingBombs += bombField.at(i + 1).at(k - 1).isBomb ? 1 : 0;
                        bombField.at(i).at(k).surroundingBombs += bombField.at(i + 1).at(k).isBomb ? 1 : 0;
                        if (k + 1 < bombField[i].size())
                            bombField.at(i).at(k).surroundingBombs += bombField.at(i + 1).at(k + 1).isBomb ? 1 : 0;
                    }
                }
                catch (const std::exception& ex)
                {
                    cout << ex.what() << endl;
                }
            }
        }
    }

    void MinesweeperField::initializeBombField(vector<vector<MinesweeperField>>& bombField, Texture& texture, const Vector2u fieldSize, const Vector2u size, int bombCount)
    {
        for (uint64_t i = 0; i < fieldSize.y; i++)
        {
            bombField.push_back(vector<MinesweeperField>());
            for (uint64_t k = 0; k < fieldSize.x; k++)
            {
                bombField.at(i).push_back(MinesweeperField(false));
                bombField[i][k].s.setTexture(texture);
                bombField[i][k].s.setPosition(size.x * k, size.y * i);
            }
        }

        const int minesPerField = fieldSize.x * fieldSize.y / bombCount * 10;
        unsigned int x = 0, y = 0;
        unsigned int xRev = bombField[0].size() - 1, yRev = bombField.size() - 1;

        srand((unsigned)time(0));
        while (bombCount > 0)
        {
            if ((((unsigned int)rand() % minesPerField) + 1) == minesPerField && !bombField[y][x].isBomb)
            {
                bombField[y][x].isBomb = true;
                bombCount--;
            }
            if ((((unsigned int)rand() % minesPerField) + 1) == minesPerField && !bombField[yRev][xRev].isBomb)
            {
                bombField[yRev][xRev].isBomb = true;
                bombCount--;
            }

            x++;
            xRev--;

            if (x >= bombField[0].size() || xRev < 0)
            {
                x = 0;
                xRev = bombField[0].size() - 1;
                y++;
                yRev--;
                if (y >= yRev)
                {
                    y = 0;
                    yRev = bombField.size() - 1;
                }
            }
        }
    }

    int MinesweeperField::countSurroundingFlags(const vector<vector<MinesweeperField>>& bombField, const uint64_t y, const uint64_t x)
    {
        int surroundingFlags = 0;
        if (y > 0)
        {
            if (x > 0)
                surroundingFlags += bombField.at(y - 1).at(x - 1).isFlag ? 1 : 0;
            surroundingFlags += bombField.at(y - 1).at(x).isFlag ? 1 : 0;
            if (x + 1 < bombField[y].size())
                surroundingFlags += bombField.at(y - 1).at(x + 1).isFlag ? 1 : 0;
        }
        if (x > 0)
            surroundingFlags += bombField.at(y).at(x - 1).isFlag ? 1 : 0;
        if (x + 1 < bombField[y].size())
            surroundingFlags += bombField.at(y).at(x + 1).isFlag ? 1 : 0;
        if (y + 1 < bombField.size())
        {
            if (x > 0)
                surroundingFlags += bombField.at(y + 1).at(x - 1).isFlag ? 1 : 0;
            surroundingFlags += bombField.at(y + 1).at(x).isFlag ? 1 : 0;
            if (x + 1 < bombField[y].size())
                surroundingFlags += bombField.at(y + 1).at(x + 1).isFlag ? 1 : 0;
        }

        return surroundingFlags;
    }

    int MinesweeperField::countSurroundingClickedFields(const vector<vector<MinesweeperField>>& bombField, const uint64_t y, const uint64_t x)
    {
        int clickedFields = 0;
        if (y > 0)
        {
            if (x > 0)
                clickedFields += bombField.at(y - 1).at(x - 1).clicked ? 1 : 0;
            else
                clickedFields++;
            clickedFields += bombField.at(y - 1).at(x).clicked ? 1 : 0;
            if (x + 1 < bombField[y].size())
                clickedFields += bombField.at(y - 1).at(x + 1).clicked ? 1 : 0;
            else
                clickedFields++;
        }
        else
            clickedFields += 3;
        if (x > 0)
            clickedFields += bombField.at(y).at(x - 1).clicked ? 1 : 0;
        else
            clickedFields++;
        if (x + 1 < bombField[y].size())
            clickedFields += bombField.at(y).at(x + 1).clicked ? 1 : 0;
        else
            clickedFields++;
        if (y + 1 < bombField.size())
        {
            if (x > 0)
                clickedFields += bombField.at(y + 1).at(x - 1).clicked ? 1 : 0;
            else
                clickedFields++;
            clickedFields += bombField.at(y + 1).at(x).clicked ? 1 : 0;
            if (x + 1 < bombField[y].size())
                clickedFields += bombField.at(y + 1).at(x + 1).clicked ? 1 : 0;
            else
                clickedFields++;
        }
        else
            clickedFields += 3;

        return clickedFields;
    }
}