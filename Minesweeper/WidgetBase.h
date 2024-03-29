#ifndef WIDGETBASE_H
#define WIDGETBASE_H

#include <SFML/Graphics.hpp>

namespace minesweeper
{
    class WidgetBase //Abstract
    {
    public:
        ~WidgetBase() {};
        virtual void DrawWidget(sf::RenderTarget& renderTarget);
        virtual bool IsMouseOver(sf::Vector2i mousePosition);
        virtual void SetPosition(float x, float y);

        sf::Text text;
        sf::RectangleShape rectangleShape;
    };
}
#endif //!WIDGERTBASE_H