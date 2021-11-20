#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <iostream>
#include <string>
#include <vector>
#include "Button.h"
#include "IView.h"
#include "TextBox.h"

namespace minesweeper
{
    class MenuView : public IView
    {
    public:
        MenuView();
        virtual void DrawView(sf::RenderTarget& renderTarget);
        virtual void InitializeView(sf::Vector2f displaySize);
        virtual ViewId MouseButtonPressedEvent(sf::Event sfEvent, sf::Vector2i mousePosition);
        virtual void MouseButtonReleasedEvent(sf::Event sfEvent);
        virtual void MouseHoverEvent(sf::Vector2i mousePosition);
        virtual void MouseWheelScrolledEvent(sf::Event sfEvent);
        virtual void TextEnteredEvent(sf::Event sfEvent);
        virtual void WindowResizedEvent(sf::Event sfEvent);

        int bombs;
        int x;
        int y;

    private:
        static ViewId buttonQuitPressed(void* ptr); //ptr has to be a pointer to the Object itself
        static ViewId buttonStartPressed(void* ptr); //ptr has to be a pointer to the Object itself
        virtual void initializeComponents();

        std::vector<Button*> buttonVector;
        std::vector<TextBox*> textBoxVector;

        sf::Font font;

        Button buttonQuit;
        Button buttonStart;

        TextBox textBoxBombCount;
        TextBox textBoxCountX;
        TextBox textBoxCountY;

        sf::Text textBombCount;
        sf::Text textCountX;
        sf::Text textCountY;
        sf::Text textMenuHeader;
    };
}
#endif // !MENUVIEW_H