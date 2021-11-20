#include "Button.h"

namespace minesweeper
{
    Button::Button()
    {
        clickEventFunctionPointer = nullptr;
        sprite = nullptr;
    }

    Button::Button(sf::Text text, ViewId(*clickEventFunctionPointer)(void*))
    {
        this->text = text;
        this->clickEventFunctionPointer = clickEventFunctionPointer;
        sprite = nullptr;

        rectangleShape.setFillColor(sf::Color::Black);
        rectangleShape.setOutlineColor(sf::Color::Red);
        rectangleShape.setOutlineThickness(2);

        rectangleShape.setSize(sf::Vector2f(this->text.getGlobalBounds().width + 20, 48));
        this->text.setFillColor(sf::Color::Red);
    }

    Button::Button(sf::Texture& texture, ViewId(*clickEventFunctionPointer)(void*))
    {
        sprite = new sf::Sprite(texture);
        this->clickEventFunctionPointer = clickEventFunctionPointer;

        rectangleShape.setFillColor(sf::Color::White);
        rectangleShape.setOutlineColor(sf::Color::Red);
        rectangleShape.setOutlineThickness(2);

        sf::FloatRect bounds = sprite->getGlobalBounds();
        rectangleShape.setSize(sf::Vector2f(bounds.width + 4, bounds.height + 4));
    }

    Button::~Button()
    {
        if (sprite != nullptr)
        {
            try
            {
                delete sprite;
            }
            catch (const std::exception& ex)
            {
                ex.what();
            }
        }
    }

    void Button::DrawWidget(sf::RenderTarget& renderTarget)
    {
        if (sprite)
        {
            renderTarget.draw(rectangleShape);
            renderTarget.draw(*sprite);
        }
        else
        {
            WidgetBase::DrawWidget(renderTarget);
        }
    }

    void Button::SetPosition(float x, float y)
    {
        WidgetBase::SetPosition(x, y);
        if (sprite)
        {
            sprite->setPosition(x + 2, y + 2);
        }
    }
}