#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include "rapidxml-1.13/rapidxml.hpp"

namespace minesweeper
{
    class Settings
    {
    public:
        static void DeserializeSettings();
        static void SerializeSettings();

        //Display Settings
        static sf::Vector2u ScreenSize;
        static bool VSyncEnabled;

        //Game Settings
        static unsigned int BombCount;
        static sf::Vector2u FieldSize;
    };
}

#endif