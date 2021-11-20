#ifndef BUTTON_H_H
#define BUTTON_H_H

#include "IView.h"
#include "WidgetBase.h"

namespace minesweeper
{
    class Button : public WidgetBase
    {
    public:
        Button();
        Button(sf::Text text, ViewId(*clickEventFunctionPointer)(void*));
        Button(sf::Texture& texture, ViewId(*clickEventFunctionPointer)(void*));
        ~Button();

        virtual void DrawWidget(sf::RenderTarget& renderTarget);
        virtual void SetPosition(float x, float y);

        sf::Sprite* sprite;
        ViewId(*clickEventFunctionPointer)(void*); //Takes a pointer to the corresponding view itself
    };
}
#endif // !BUTTON_H