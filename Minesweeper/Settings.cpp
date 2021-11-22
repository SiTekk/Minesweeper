#include "Settings.h"

namespace minesweeper
{
	void minesweeper::Settings::DeserializeSettings()
	{
	}

	void minesweeper::Settings::SerializeSettings()
	{
	}

	sf::Vector2u Settings::ScreenSize;
	bool Settings::VSyncEnabled = true;

	unsigned int Settings::BombCount = 0;
	sf::Vector2u Settings::FieldSize;

}
