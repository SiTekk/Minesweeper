#include "MenuView.h"

using namespace sf;
using namespace std;

namespace minesweeper
{
    MenuView::MenuView()
    {
        viewId = ViewId::MENU_VIEW;

        initializeComponents();
    }

    void MenuView::initializeComponents()
    {
        font.loadFromFile("font\\NotoSansMono-Bold.ttf");

        buttonStart = Button(Text("Start", font), buttonStartPressed);
        buttonVector.push_back(&buttonStart);
        buttonQuit = Button(Text("Quit", font), buttonQuitPressed);
        buttonVector.push_back(&buttonQuit);

        textBoxBombCount = TextBox(Text("260", font));
        textBoxVector.push_back(&textBoxBombCount);
        textBoxCountX = TextBox(Text("48", font));
        textBoxVector.push_back(&textBoxCountX);
        textBoxCountY = TextBox(Text("27", font));
        textBoxVector.push_back(&textBoxCountY);

        textBombCount = Text("Mines:", font);
        textCountX = Text("Width:", font);
        textCountY = Text("Height:", font);
        textMenuHeader = Text("Minesweeper Collection!", font);

        textBombCount.setFillColor(Color::Red);
        textCountX.setFillColor(Color::Red);
        textCountY.setFillColor(Color::Red);
        textMenuHeader.setFillColor(Color::Red);

        textMenuHeader.setCharacterSize(64);
        textMenuHeader.setPosition(50, 50);
    }

    void MenuView::InitializeView(Vector2f displaySize)
    {
        buttonQuit.SetPosition(displaySize.x / 2 - buttonQuit.rectangleShape.getGlobalBounds().width - 20, displaySize.y / 2 + 200);
        buttonStart.SetPosition(displaySize.x / 2 + 20, displaySize.y / 2 + 200);

        textBoxBombCount.SetPosition(displaySize.x / 2 + 20, displaySize.y / 2 - 100);
        textBoxCountX.SetPosition(displaySize.x / 2 + 20, displaySize.y / 2);
        textBoxCountY.SetPosition(displaySize.x / 2 + 20, displaySize.y / 2 + 100);

        textBombCount.setPosition(textBoxBombCount.text.getPosition().x - textBombCount.getGlobalBounds().width - 40, textBoxBombCount.text.getPosition().y);
        textCountX.setPosition(textBoxCountX.text.getPosition().x - textCountX.getGlobalBounds().width - 40, textBoxCountX.text.getPosition().y);
        textCountY.setPosition(textBoxCountY.text.getPosition().x - textCountY.getGlobalBounds().width - 40, textBoxCountY.text.getPosition().y);
    }

    ViewId MenuView::MouseButtonPressedEvent(Event sfEvent, Vector2i mousePosition)
    {
        for (Button* button : buttonVector)
        {
            if (button->IsMouseOver(mousePosition))
            {
                return button->clickEventFunctionPointer(this);
            }
        }

        for (TextBox* textBox : textBoxVector)
        {
            if (textBox->IsMouseOver(mousePosition))
            {
                textBox->SetFocus(true);
                continue;
            }
            else if (textBox->GetFocus())
            {
                textBox->SetFocus(false);
            }
        }

        return this->viewId;
    }

    void MenuView::MouseButtonReleasedEvent(sf::Event sfEvent)
    {
        //Do nothing
    }

    void MenuView::MouseHoverEvent(sf::Vector2i mousePosition)
    {
        for (Button* button : buttonVector)
        {
            if (button->IsMouseOver(mousePosition))
                return;
        }
        for (TextBox* textBox : textBoxVector)
        {
            if (textBox->IsMouseOver(mousePosition))
                return;
        }
    }

    void MenuView::MouseWheelScrolledEvent(sf::Event sfEvent)
    {
        //Do nothing
    }

    void MenuView::TextEnteredEvent(sf::Event sfEvent)
    {
        for (TextBox* textBox : textBoxVector)
        {
            if (textBox->GetFocus())
            {
                textBox->SetText(sfEvent.text.unicode);
            }
        }
    }

    void MenuView::WindowResizedEvent(sf::Event sfEvent)
    {
        //TODO:: Implement Resize Funtctionality
    }

    ViewId MenuView::buttonQuitPressed(void* ptr)
    {
        return ViewId::EXIT;
    }

    ViewId MenuView::buttonStartPressed(void* ptr)
    {
        MenuView* menuView = (MenuView*)ptr;
        menuView->bombs = std::stoi(std::string(menuView->textBoxBombCount.text.getString()));
        menuView->x = std::stoi(std::string(menuView->textBoxCountX.text.getString()));
        menuView->y = std::stoi(std::string(menuView->textBoxCountY.text.getString()));
        return ViewId::GAME_VIEW;
    }

    void MenuView::DrawView(RenderWindow& renderWindow)
    {
        renderWindow.draw(textMenuHeader);
        for (Button* button : buttonVector)
        {
            renderWindow.draw(button->rectangleShape);
            renderWindow.draw(button->text);
        }
        for (TextBox* textBox : textBoxVector)
        {
            renderWindow.draw(textBox->rectangleShape);
            renderWindow.draw(textBox->text);
        }
        renderWindow.draw(textBombCount);
        renderWindow.draw(textCountX);
        renderWindow.draw(textCountY);
    }
}