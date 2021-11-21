#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>

class Settings
{
    //Display Settings
    static sf::Vector2u ScreenSize;
    static bool VSyncEnabled;

    //Game Settings
    static unsigned int BombCount;
    static sf::Vector2u FieldSize;
};

#endif