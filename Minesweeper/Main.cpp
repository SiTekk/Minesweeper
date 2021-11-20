#include "MinesweeperField.h"
#include "MenuView.h"
#include "FieldView.h"
#include "IView.h"
#include "Button.h"

using namespace std;
using namespace sf;

namespace minesweeper
{
    RenderWindow window;
    IView* currentView;

    /// <summary>
    /// Handles the Events that are thrown by SFML.
    /// </summary>
    void HandleEvents();
    /// <summary>
    /// Changes the currentView pointer to the new view that should be displayed.
    /// </summary>
    /// <param name="id">The ViewId of the view that should be displayed.</param>
    /// <returns>Returns true if the Program should exit.</returns>
    bool ChangeView(ViewId id);

    int main()
    {
        //Create the window and activate VSync
        window.create(VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Minesweeper Collection", Style::Fullscreen);
        window.setVerticalSyncEnabled(true);

        currentView = new MenuView();

        Vector2i oldMousePos;

        //Functionalities for the FPS counter
        Clock clock;
        Time dt;
        clock.restart();
        Font font;
        font.loadFromFile("font\\NotoSansMono-Bold.ttf");
        Text textFps = Text("0", font);
        textFps.setFillColor(Color::Yellow);
        sf::VideoMode screenSize = sf::VideoMode::getDesktopMode();
        Vector2i textFpsSize = Vector2i(textFps.getLocalBounds().width, textFps.getLocalBounds().height);
        textFps.setPosition(screenSize.width - textFpsSize.x * 4 - 5, screenSize.height - textFpsSize.y - 20);
        Int64 lastTime = 0;

        //Game Loop
        while (window.isOpen())
        {
            HandleEvents();

            if (Mouse::isButtonPressed(Mouse::Middle) && currentView->viewId == ViewId::GAME_VIEW)
            {
                //Move the field when the middle button is pressed
                Vector2i currentMousePosition = Mouse::getPosition();
                if (((FieldView*)currentView)->mouseCounter)
                {
                    ((FieldView*)currentView)->renderTextureSprite.move(currentMousePosition.x - oldMousePos.x, currentMousePosition.y - oldMousePos.y);
                }
                else
                {
                    ((FieldView*)currentView)->mouseCounter = true;
                }
                oldMousePos = currentMousePosition;

                /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    renderTextureSprite.move(-5.f, 0.f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    renderTextureSprite.move(0.f, -5.f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    renderTextureSprite.move(0.f, 5.f);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    renderTextureSprite.move(5.f, 0.f);
                }*/
            }

            window.clear();

            currentView->InitializeView(window.getDefaultView().getSize());
            currentView->DrawView(window);

            Int64 currentTime = clock.getElapsedTime().asMicroseconds();
            Int64 fps = 1000000 / (currentTime - lastTime);
            lastTime = currentTime;

            textFps.setString(std::to_string(fps));

            window.draw(textFps);

            window.display();
        }

        delete currentView;
        return 0;
    }

    void HandleEvents()
    {
        Event sfEvent;

        currentView->MouseHoverEvent(Mouse::getPosition(window));

        while (window.pollEvent(sfEvent))
        {
            switch (sfEvent.type)
            {
            case Event::Closed:
                window.close();
                break;

            case Event::Resized:
            {
                FloatRect visibleArea(0, 0, sfEvent.size.width, sfEvent.size.height);
                window.setView(View(visibleArea));
                //menuBar.setSize(Vector2f(event.size.width, 40));
                break;
            }

            case Event::MouseButtonPressed:
            {
                ViewId id = currentView->MouseButtonPressedEvent(sfEvent, Mouse::getPosition(window));
                if (currentView->viewId != id)
                {
                    if (ChangeView(id))
                    {
                        window.close();
                    }
                }
                break;
            }

            case Event::MouseButtonReleased:
                currentView->MouseButtonReleasedEvent(sfEvent);
                break;

            case Event::KeyPressed:
                if (sfEvent.key.code == Keyboard::Escape)
                    window.close();
                break;

            case Event::MouseWheelScrolled:
                currentView->MouseWheelScrolledEvent(sfEvent);
                break;

            case Event::TextEntered:
                currentView->TextEnteredEvent(sfEvent);
                break;
            }
        }
    }

    bool ChangeView(ViewId id)
    {
        switch (id)
        {
        case ViewId::EXIT:
            return true;

        case ViewId::MENU_VIEW:
            delete currentView;
            currentView = new MenuView();
            break;

        case ViewId::GAME_VIEW:
            //fieldView.InitializeFieldView(menuView.bombs, menuView.x, menuView.y);
            IView *temp= new FieldView(((MenuView*)currentView)->bombs, ((MenuView*)currentView)->x, ((MenuView*)currentView)->y, window.getSize());
            delete currentView;
            currentView = temp;
            break;
        }

        return false;
    }
}

int main()
{
    minesweeper::main();
}