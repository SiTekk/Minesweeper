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
        for (int i = 0; i < bombField.size(); i++)
        {
            for (int k = 0; k < bombField[i].size(); k++)
            {
                try
                {
                    if (i - 1 >= 0)
                    {
                        if (k - 1 >= 0)
                            bombField.at(i).at(k).surroundingBombs += bombField.at(i - 1).at(k - 1).isBomb ? 1 : 0;
                        bombField.at(i).at(k).surroundingBombs += bombField.at(i - 1).at(k).isBomb ? 1 : 0;
                        if (k + 1 < bombField[i].size())
                            bombField.at(i).at(k).surroundingBombs += bombField.at(i - 1).at(k + 1).isBomb ? 1 : 0;
                    }
                    if (k - 1 >= 0)
                        bombField.at(i).at(k).surroundingBombs += bombField.at(i).at(k - 1).isBomb ? 1 : 0;
                    if (k + 1 < bombField[i].size())
                        bombField.at(i).at(k).surroundingBombs += bombField.at(i).at(k + 1).isBomb ? 1 : 0;
                    if (i + 1 < bombField.size())
                    {
                        if ((k - 1) >= 0)
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

    void MinesweeperField::initializeBombField(vector<vector<MinesweeperField>>& bombField, Texture& texture, Vector2u count, Vector2u size, int bombCount)
    {
        for (int i = 0; i < count.y; i++)
        {
            bombField.push_back(vector<MinesweeperField>());
            for (int k = 0; k < count.x; k++)
            {
                bombField.at(i).push_back(MinesweeperField(false));
                bombField[i][k].s.setTexture(texture);
                bombField[i][k].s.setPosition(size.x * k, size.y * i);
            }
        }

        int minesPerField = count.x * count.y / bombCount * 10;
        int x = 0, y = 0;
        int xRev = bombField[0].size() - 1, yRev = bombField.size() - 1;

        srand((unsigned)time(0));
        while (bombCount > 0)
        {
            if ((((int)rand() % minesPerField) + 1) == minesPerField && !bombField[y][x].isBomb)
            {
                bombField[y][x].isBomb = true;
                bombCount--;
            }
            if ((((int)rand() % minesPerField) + 1) == minesPerField && !bombField[yRev][xRev].isBomb)
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

    int MinesweeperField::countSurroundingFlags(vector<vector<MinesweeperField>> bombField, int y, int x)
    {
        int surroundingFlags = 0;
        if (y - 1 >= 0)
        {
            if (x - 1 >= 0)
                surroundingFlags += bombField.at(y - 1).at(x - 1).isFlag ? 1 : 0;
            surroundingFlags += bombField.at(y - 1).at(x).isFlag ? 1 : 0;
            if (x + 1 < bombField[y].size())
                surroundingFlags += bombField.at(y - 1).at(x + 1).isFlag ? 1 : 0;
        }
        if (x - 1 >= 0)
            surroundingFlags += bombField.at(y).at(x - 1).isFlag ? 1 : 0;
        if (x + 1 < bombField[y].size())
            surroundingFlags += bombField.at(y).at(x + 1).isFlag ? 1 : 0;
        if (y + 1 < bombField.size())
        {
            if ((x - 1) >= 0)
                surroundingFlags += bombField.at(y + 1).at(x - 1).isFlag ? 1 : 0;
            surroundingFlags += bombField.at(y + 1).at(x).isFlag ? 1 : 0;
            if (x + 1 < bombField[y].size())
                surroundingFlags += bombField.at(y + 1).at(x + 1).isFlag ? 1 : 0;
        }

        return surroundingFlags;
    }

    int MinesweeperField::countSurroundingClickedFields(vector<vector<MinesweeperField>> bombField, int y, int x)
    {
        int clickedFields = 0;
        if (y - 1 >= 0)
        {
            if (x - 1 >= 0)
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
        if (x - 1 >= 0)
            clickedFields += bombField.at(y).at(x - 1).clicked ? 1 : 0;
        else
            clickedFields++;
        if (x + 1 < bombField[y].size())
            clickedFields += bombField.at(y).at(x + 1).clicked ? 1 : 0;
        else
            clickedFields++;
        if (y + 1 < bombField.size())
        {
            if ((x - 1) >= 0)
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