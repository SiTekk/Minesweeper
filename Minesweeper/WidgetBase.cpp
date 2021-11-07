#include "WidgetBase.h"

namespace minesweeper
{
    void WidgetBase::DrawWidget(sf::RenderWindow& renderWindow)
    {
        renderWindow.draw(rectangleShape);
        renderWindow.draw(text);
    }

    void WidgetBase::DrawWidget(sf::RenderTexture& renderTexture)
    {
        renderTexture.draw(rectangleShape);
        renderTexture.draw(text);
    }

    bool WidgetBase::IsMouseOver(sf::Vector2i mousePosition)
    {
        sf::Vector2f pos = rectangleShape.getPosition();
        if (mousePosition.x > pos.x && mousePosition.y > pos.y && mousePosition.x < pos.x + rectangleShape.getGlobalBounds().width && mousePosition.y < pos.y + rectangleShape.getGlobalBounds().height)
        {
            rectangleShape.setOutlineColor(sf::Color::Yellow);
            return true;
        }
        else if (rectangleShape.getOutlineColor() != sf::Color::Red)
        {
            rectangleShape.setOutlineColor(sf::Color::Red);
        }
        return false;
    }

    void WidgetBase::SetPosition(float x, float y)
    {
        rectangleShape.setPosition(x, y);
        text.setPosition(rectangleShape.getPosition().x + 8, rectangleShape.getPosition().y + 2);
    }
}