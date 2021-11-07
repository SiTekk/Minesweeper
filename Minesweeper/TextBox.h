#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <sstream>
#include "WidgetBase.h"

namespace minesweeper
{
    class TextBox : public WidgetBase
    {
    public:
        TextBox();
        TextBox(sf::Text text);
        void SetText(sf::Uint32 character);
        void SetText(std::string string);
        bool GetFocus();
        void SetFocus(bool isFocused);

    private:
        std::stringstream sstream;
        bool isFocused;
    };
}
#endif // !TEXTBOX_H