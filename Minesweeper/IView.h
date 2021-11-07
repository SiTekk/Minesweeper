#ifndef IVIEW_H
#define IVIEW_H

#include <SFML/Graphics.hpp>

namespace minesweeper
{
    enum class ViewId
    {
        EXIT, //To call that the game has to exit
        MENU_VIEW,
        GAME_VIEW //FieldView
    };

    class IView
    {
    public:

        virtual ~IView() {};
        virtual void DrawView(sf::RenderWindow& renderWindow) = 0;
        virtual void InitializeView(sf::Vector2f displaySize) = 0;
        virtual ViewId MouseButtonPressedEvent(sf::Event sfEvent, sf::Vector2i mousePosition) = 0;
        virtual void MouseButtonReleasedEvent(sf::Event sfEvent) = 0;
        virtual void MouseHoverEvent(sf::Vector2i mousePosition) = 0;
        virtual void MouseWheelScrolledEvent(sf::Event sfEvent) = 0;
        virtual void TextEnteredEvent(sf::Event sfEvent) = 0;
        virtual void WindowResizedEvent(sf::Event sfEvent) = 0;

        ViewId viewId;

    protected:
        virtual void initializeComponents() = 0;
    };
}
#endif //!IVIEW_H