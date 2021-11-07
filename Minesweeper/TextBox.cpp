#include <iomanip>
#include "TextBox.h"

namespace minesweeper
{
    TextBox::TextBox()
    {
        isFocused = false;
    }

    TextBox::TextBox(sf::Text text)
    {
        isFocused = false;

        this->text = text;

        rectangleShape.setFillColor(sf::Color::Black);
        rectangleShape.setOutlineColor(sf::Color::Red);
        rectangleShape.setOutlineThickness(2);

        rectangleShape.setSize(sf::Vector2f(this->text.getGlobalBounds().width + 20, 48));

        this->text.setFillColor(sf::Color::Red);
    }

    void TextBox::SetText(sf::Uint32 character)
    {
        if (character == 8)
        {
            std::string str = static_cast<std::string>(text.getString());
            str = str.substr(0, str.size() - 1);
            text.setString(str);
        }
        else
        {
            if (character >= 48 && character < 58)
            {
                sstream << std::fixed << std::setprecision(2) << static_cast<std::string>(text.getString()) << static_cast<char>(character);
                text.setString(sstream.str());
                sstream.str("");
            }
        }

        rectangleShape.setSize(sf::Vector2f(this->text.getGlobalBounds().width + 20, rectangleShape.getSize().y));
    }

    void TextBox::SetText(std::string string)
    {
        text.setString(string);
        rectangleShape.setSize(sf::Vector2f(this->text.getGlobalBounds().width + 20, rectangleShape.getSize().y));
    }

    bool TextBox::GetFocus()
    {
        return isFocused;
    }

    void TextBox::SetFocus(bool isFocused)
    {
        this->isFocused = isFocused;
        if (isFocused)
        {
            rectangleShape.setFillColor(sf::Color::White);
        }
        else
        {
            rectangleShape.setFillColor(sf::Color::Black);
        }
    }
}