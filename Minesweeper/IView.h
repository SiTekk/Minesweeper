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

        /// <summary>
        /// 
        /// </summary>
        /// <param name="renderWindow"></param>
        virtual void DrawView(sf::RenderWindow& renderWindow) = 0;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="displaySize"></param>
        virtual void InitializeView(sf::Vector2f displaySize) = 0;

        /// <summary>
        /// Abstract function to handle the mousebutton pressed event.
        /// </summary>
        /// <param name="sfEvent">Event parameters.</param>
        /// <param name="mousePosition">Position of the mouse.</param>
        /// <returns>
        /// Returns the ViewId of the current View if nothing should be changed.<para />
        /// Returns a different ViewId if the currentView should change or the application should exit.
        /// </returns>
        virtual ViewId MouseButtonPressedEvent(sf::Event sfEvent, sf::Vector2i mousePosition) = 0;

        /// <summary>
        /// Abstract function to handle the mousebutton released event.
        /// </summary>
        /// <param name="sfEvent">Event parameters.</param>
        virtual void MouseButtonReleasedEvent(sf::Event sfEvent) = 0;

        /// <summary>
        /// Abstract function to handle the mouse hover event.
        /// </summary>
        /// <param name="mousePosition">Position of the mouse.</param>
        virtual void MouseHoverEvent(sf::Vector2i mousePosition) = 0;

        /// <summary>
        /// Abstract function to handle the mouse wheel scroll event.
        /// </summary>
        /// <param name="sfEvent">Event parameters.</param>
        virtual void MouseWheelScrolledEvent(sf::Event sfEvent) = 0;

        /// <summary>
        /// Abstract function to handle the text entered event.
        /// </summary>
        /// <param name="sfEvent">Event parameters.</param>
        virtual void TextEnteredEvent(sf::Event sfEvent) = 0;

        /// <summary>
        /// Abstract function to handle the window resized event.
        /// </summary>
        /// <param name="sfEvent">Event parameters.</param>
        virtual void WindowResizedEvent(sf::Event sfEvent) = 0;

        ViewId viewId;

    protected:
        virtual void initializeComponents() = 0;
    };
}
#endif //!IVIEW_H