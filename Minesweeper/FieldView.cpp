#include "FieldView.h"

namespace minesweeper
{
    FieldView::FieldView(int bombCount, int countX, int countY, Vector2u displaySize)
    {
        viewId = ViewId::GAME_VIEW;
        mouseCounter = false;
        initializeComponents();

        Vector2u size = textureFieldCovered.getSize();
        renderTextureGameField.create(size.x * countX, size.y * countY);
        InitializeFieldView(bombCount, countX, countY);
    }

    FieldView::FieldView()
    {
        viewId = ViewId::GAME_VIEW;
        mouseCounter = false;
        initializeComponents();
    }

    void FieldView::initializeComponents()
    {
        loadTextures();
        font.loadFromFile("font\\NotoSansMono-Bold.ttf");

        renderTextureSprite.setPosition(0, 40);
        textureReload.setSmooth(true);
        textureMenu.setSmooth(true);
        reloadSprite.setTexture(textureReload);

        buttonMenu = new Button(textureMenu, buttonMenuClick);
        buttonVector.push_back(buttonMenu);
        buttonReload = new Button(textureReload, buttonReloadClick);
        buttonVector.push_back(buttonReload);

        menuBar.setFillColor(Color(212, 212, 212));
        textBoxBombCount.setFillColor(Color::Black);
        textBoxElapsedTime.setFillColor(Color::Black);
        oldbuttonReload.setFillColor(Color::White);
        textBoxBombCount.setOutlineColor(Color::Red);
        textBoxElapsedTime.setOutlineColor(Color::Red);
        oldbuttonReload.setOutlineColor(Color::Red);
        textBoxBombCount.setOutlineThickness(2);
        textBoxElapsedTime.setOutlineThickness(2);
        oldbuttonReload.setOutlineThickness(2);

        textBombCount.setString(to_string(bombsCount));
        textBombCount.setFont(font);
        textBombCount.setStyle(Text::Regular);
        textBombCount.setFillColor(Color::Red);
        textBombCount.setCharacterSize(18);
        textBombCount.setPosition(25, 10);

        textElapsedTime.setString("Elapsed Time");
        textElapsedTime.setFont(font);
        textElapsedTime.setStyle(Text::Regular);
        textElapsedTime.setFillColor(Color::Red);
        textElapsedTime.setCharacterSize(18);
        textElapsedTime.setPosition(textBombCount.getGlobalBounds().width + 40, 10);
    }

    ViewId FieldView::buttonReloadClick(void* ptr)
    {
        FieldView* fieldView = (FieldView*)ptr;
        fieldView->InitializeFieldView(fieldView->bombsCount, fieldView->countX, fieldView->countY);
        return ViewId::GAME_VIEW;
    }

    ViewId FieldView::buttonMenuClick(void* ptr)
    {
        return ViewId::EXIT;
    }

    void FieldView::InitializeFieldView(int bombCount, int countX, int countY)
    {
        this->bombsCount = bombCount;  //Stores the Value of the Bombs, does not get changed
        this->bombCounter = bombCount; //Displays the Bombs on the top left corner of the field view
        this->countX = countX;
        this->countY = countY;

        createField();
    }

    void FieldView::loadTextures()
    {
        textureFieldBomb.loadFromFile("graphics\\minesweeper_bomb.png");
        textureFieldClickedBomb.loadFromFile("graphics\\minesweeper_clickedBomb.png");
        textureFieldFlag.loadFromFile("graphics\\minesweeper_flag.png");
        textureFieldWrongFlag.loadFromFile("graphics\\minesweeper_wrongFlag.png");
        textureFieldCovered.loadFromFile("graphics\\minesweeper_covered.png");
        textureField0.loadFromFile("graphics\\minesweeper_revealed.png");
        textureField1.loadFromFile("graphics\\minesweeper_1.png");
        textureField2.loadFromFile("graphics\\minesweeper_2.png");
        textureField3.loadFromFile("graphics\\minesweeper_3.png");
        textureField4.loadFromFile("graphics\\minesweeper_4.png");
        textureField5.loadFromFile("graphics\\minesweeper_5.png");
        textureField6.loadFromFile("graphics\\minesweeper_6.png");
        textureField7.loadFromFile("graphics\\minesweeper_7.png");
        textureField8.loadFromFile("graphics\\minesweeper_8.png");
        textureReload.loadFromFile("graphics\\reload24.png");
        textureMenu.loadFromFile("graphics\\liste24.png");
    }

    void FieldView::createField()
    {
        gameOver = 0;
        drawField = true;
        bombCounter = bombsCount;
        nonBombsCounter = countX * countY - bombsCount;

        bombField.clear();
        MinesweeperField::initializeBombField(bombField, textureFieldCovered, Vector2u(countX, countY), textureFieldCovered.getSize(), bombsCount);
        MinesweeperField::setSurroundingBombs(bombField);
        clock.restart();
    }

    void FieldView::setFlag(MinesweeperField& field)
    {
        field.s.setTexture(textureFieldFlag);
        field.isFlag = true;
        bombCounter--;
    }

    void FieldView::revealField()
    {
        for (vector<MinesweeperField>& line : bombField)
        {
            for (MinesweeperField& field : line)
            {
                if (field.isBomb && !field.isFlag)
                {
                    field.s.setTexture(textureFieldBomb);
                    continue;
                }
                if (field.isFlag && !field.isBomb)
                {
                    field.s.setTexture(textureFieldWrongFlag);
                    continue;
                }
            }
        }
    }

    void FieldView::setClickedFieldTexture(const uint64_t y, const uint64_t x)
    {
        MinesweeperField& field = bombField[y][x];

        if (field.isBomb)
        {
            revealField();
            field.s.setTexture(textureFieldClickedBomb);
            gameOver = 1;
            return;
        }

        field.clicked = true;
        nonBombsCounter--;
        switch (field.surroundingBombs)
        {
        case 0:
            field.s.setTexture(textureField0);
            revealSurroundingFields(y, x);
            break;
        case 1:
            field.s.setTexture(textureField1);
            break;
        case 2:
            field.s.setTexture(textureField2);
            break;
        case 3:
            field.s.setTexture(textureField3);
            break;
        case 4:
            field.s.setTexture(textureField4);
            break;
        case 5:
            field.s.setTexture(textureField5);
            break;
        case 6:
            field.s.setTexture(textureField6);
            break;
        case 7:
            field.s.setTexture(textureField7);
            break;
        case 8:
            field.s.setTexture(textureField8);
            break;

        default:
            break;
        }

        if (nonBombsCounter == 0)
            gameOver = -1;
    }

    void FieldView::revealSurroundingFields(const uint64_t y, const uint64_t x)
    {
        if (y > 0)
        {
            if (x > 0)
            {
                if (!bombField[y - 1][x - 1].clicked && !bombField[y - 1][x - 1].isFlag)
                    setClickedFieldTexture(y - 1, x - 1);
            }

            if (!bombField[y - 1][x].clicked && !bombField[y - 1][x].isFlag)
                setClickedFieldTexture(y - 1, x);
            if (x + 1 < bombField[y].size())
            {
                if (!bombField[y - 1][x + 1].clicked && !bombField[y - 1][x + 1].isFlag)
                    setClickedFieldTexture(y - 1, x + 1);
            }
        }
        if (x > 0)
        {
            if (!bombField[y][x - 1].clicked && !bombField[y][x - 1].isFlag)
                setClickedFieldTexture(y, x - 1);
        }
        if (x + 1 < bombField[y].size())
        {
            if (!bombField[y][x + 1].clicked && !bombField[y][x + 1].isFlag)
                setClickedFieldTexture(y, x + 1);
        }
        if (y + 1 < bombField.size())
        {
            if (x > 0)
            {
                if (!bombField[y + 1][x - 1].clicked && !bombField[y + 1][x - 1].isFlag)
                    setClickedFieldTexture(y + 1, x - 1);
            }
            if (!bombField[y + 1][x].clicked && !bombField[y + 1][x].isFlag)
                setClickedFieldTexture(y + 1, x);
            if (x + 1 < bombField[y].size())
            {
                if (!bombField[y + 1][x + 1].clicked && !bombField[y + 1][x + 1].isFlag)
                    setClickedFieldTexture(y + 1, x + 1);
            }
        }
    }

    void FieldView::setSurroundingFlags(const uint64_t y, const uint64_t x)
    {
        if (y > 0)
        {
            if (x > 0)
            {
                if (!bombField[y - 1][x - 1].clicked && !bombField[y - 1][x - 1].isFlag)
                    setFlag(bombField[y - 1][x - 1]);
            }

            if (!bombField[y - 1][x].clicked && !bombField[y - 1][x].isFlag)
                setFlag(bombField[y - 1][x]);
            if (x + 1 < bombField[y].size())
            {
                if (!bombField[y - 1][x + 1].clicked && !bombField[y - 1][x + 1].isFlag)
                    setFlag(bombField[y - 1][x + 1]);
            }
        }
        if (x > 0)
        {
            if (!bombField[y][x - 1].clicked && !bombField[y][x - 1].isFlag)
                setFlag(bombField[y][x - 1]);
        }
        if (x + 1 < bombField[y].size())
        {
            if (!bombField[y][x + 1].clicked && !bombField[y][x + 1].isFlag)
                setFlag(bombField[y][x + 1]);
        }
        if (y + 1 < bombField.size())
        {
            if (x > 0)
            {
                if (!bombField[y + 1][x - 1].clicked && !bombField[y + 1][x - 1].isFlag)
                    setFlag(bombField[y + 1][x - 1]);
            }
            if (!bombField[y + 1][x].clicked && !bombField[y + 1][x].isFlag)
                setFlag(bombField[y + 1][x]);
            if (x + 1 < bombField[y].size())
            {
                if (!bombField[y + 1][x + 1].clicked && !bombField[y + 1][x + 1].isFlag)
                    setFlag(bombField[y + 1][x + 1]);
            }
        }
    }

    void FieldView::fieldLeftClicked(Vector2i mousePosition)
    {
        FloatRect spriteSize = renderTextureSprite.getGlobalBounds();

        if (mousePosition.x > spriteSize.left && mousePosition.y > spriteSize.top && mousePosition.x < spriteSize.left + spriteSize.width && mousePosition.y < spriteSize.top + spriteSize.height && mousePosition.y > 40)
        {
            int x = (mousePosition.x - spriteSize.left) / (spriteSize.width / countX);
            int y = (mousePosition.y - spriteSize.top) / (spriteSize.height / countY);

            if (!bombField[y][x].isFlag)
            {
                if (bombField[y][x].clicked)
                {
                    if (bombField[y][x].surroundingBombs > 0)
                    {
                        if (MinesweeperField::countSurroundingFlags(bombField, y, x) == bombField[y][x].surroundingBombs)
                        {
                            revealSurroundingFields(y, x);
                        }
                    }
                }
                else
                {
                    setClickedFieldTexture(y, x);
                }
            }
        }
    }

    void FieldView::fieldRightClicked(Vector2i mousePosition)
    {
        FloatRect spriteSize = renderTextureSprite.getGlobalBounds();

        if (mousePosition.x > spriteSize.left && mousePosition.y > spriteSize.top && mousePosition.x < spriteSize.left + spriteSize.width && mousePosition.y < spriteSize.top + spriteSize.height && mousePosition.y > 40)
        {
            int x = (mousePosition.x - spriteSize.left) / (spriteSize.width / countX);
            int y = (mousePosition.y - spriteSize.top) / (spriteSize.height / countY);

            if (!bombField[y][x].clicked)
            {
                if (bombField[y][x].isFlag)
                {
                    bombField[y][x].s.setTexture(textureFieldCovered);
                    bombField[y][x].isFlag = false;
                    bombCounter++;
                }
                else
                {
                    setFlag(bombField[y][x]);
                }
            }
            else
            {
                int count = MinesweeperField::countSurroundingClickedFields(bombField, y, x);
                if (bombField[y][x].surroundingBombs > 0 && 8 - bombField[y][x].surroundingBombs == MinesweeperField::countSurroundingClickedFields(bombField, y, x))
                {
                    setSurroundingFlags(y, x);
                }
            }
        }
    }

    void FieldView::oldbuttonReloadClick(Vector2i mousePosition)
    {
        FloatRect buttonPos = oldbuttonReload.getGlobalBounds();
        if (mousePosition.x > buttonPos.left && mousePosition.y > buttonPos.top && mousePosition.x < buttonPos.left + buttonPos.width && mousePosition.y < buttonPos.height)
        {
            oldbuttonReload.setFillColor(Color(255, 136, 0));
            createField();
            renderTextureSprite.setPosition(0, 40);
            renderTextureSprite.setScale(1, 1);
            clock.restart();
        }
    }

    void FieldView::buttonReloadReleased()
    {
        oldbuttonReload.setFillColor(Color::White);
    }

    void FieldView::InitializeView(Vector2f displaySize)
    {
        renderTextureMenuBar.create(displaySize.x, 40);
        menuBar.setSize(Vector2f(displaySize.x, 40));

        if (drawField)
        {
            renderTextureGameField.clear();
            for (int i = 0; i < bombField.size(); i++)
            {
                for (MinesweeperField field : bombField[i])
                {
                    renderTextureGameField.draw(field.s);
                }
            }
            if (gameOver != 0)
            {
                drawField = false;
            }

            renderTextureGameField.display();
            renderTextureSprite.setTexture(renderTextureGameField.getTexture());
        }
        else
        {
        }

        renderTextureMenuBar.clear();

        if (gameOver == 0)
            dt = clock.getElapsedTime();
        textBombCount.setString(to_string(bombCounter));
        sstream << std::fixed << std::setprecision(2) << dt.asSeconds();
        textElapsedTime.setString(sstream.str());
        sstream.str("");

        buttonMenu->SetPosition(displaySize.x - 40, 7);
        buttonReload->SetPosition(textBoxBombCount.getGlobalBounds().width + textBoxElapsedTime.getGlobalBounds().width + 60, 7);

        textBoxBombCount.setSize(Vector2f((int)textBombCount.getGlobalBounds().width / 10 * 10 + 20, 26));
        textBoxElapsedTime.setSize(Vector2f((int)textElapsedTime.getGlobalBounds().width / 10 * 10 + 20, 26));
        oldbuttonReload.setSize(Vector2f(30, 30));
        textBoxBombCount.setPosition(20, 8);
        textBoxElapsedTime.setPosition(textBoxBombCount.getGlobalBounds().width + 40, 8);
        textElapsedTime.setPosition(textBoxElapsedTime.getPosition().x + 5, 10);
        oldbuttonReload.setPosition(textBoxBombCount.getGlobalBounds().width + textBoxElapsedTime.getGlobalBounds().width + 60, 7);
        reloadSprite.setPosition(textBoxBombCount.getGlobalBounds().width + textBoxElapsedTime.getGlobalBounds().width + 62, 9);

        renderTextureMenuBar.draw(menuBar);
        renderTextureMenuBar.draw(textBoxBombCount);
        renderTextureMenuBar.draw(textBoxElapsedTime);
        buttonMenu->DrawWidget(renderTextureMenuBar);
        buttonReload->DrawWidget(renderTextureMenuBar);
        renderTextureMenuBar.draw(textBombCount);
        renderTextureMenuBar.draw(textElapsedTime);
        renderTextureMenuBar.display();

        menuBarSprite.setTexture(renderTextureMenuBar.getTexture());
    }

    void FieldView::DrawView(RenderTarget& renderTarget)
    {
        renderTarget.draw(this->renderTextureSprite);
        renderTarget.draw(this->menuBarSprite);
    }

    ViewId FieldView::MouseButtonPressedEvent(Event sfEvent, Vector2i mousePosition)
    {
        if (sfEvent.mouseButton.button == Mouse::Left)
        {
            if (mousePosition.y > 40)
            {
                fieldLeftClicked(mousePosition);
            }
            else
            {
                for (Button* button : buttonVector)
                {
                    if (button->IsMouseOver(mousePosition))
                    {
                        button->rectangleShape.setFillColor(sf::Color::Yellow);
                        return button->clickEventFunctionPointer(this);
                    }
                }
            }
        }
        else if (sfEvent.mouseButton.button == Mouse::Right)
        {
            fieldRightClicked(mousePosition);
        }

        return this->viewId;
    }

    void FieldView::MouseButtonReleasedEvent(sf::Event sfEvent)
    {
        if (sfEvent.mouseButton.button == Mouse::Left)
            buttonReloadReleased();

        if (sfEvent.mouseButton.button == Mouse::Middle)
            mouseCounter = false;
    }

    void FieldView::MouseHoverEvent(sf::Vector2i mousePosition)
    {
        for (Button* button : buttonVector)
        {
            if (button->IsMouseOver(mousePosition))
            {
                if (button->rectangleShape.getFillColor() == sf::Color::Yellow)
                    button->rectangleShape.setFillColor(sf::Color::White);
                return;
            }
        }
        for (TextBox* textBox : textBoxVector)
        {
            if (textBox->IsMouseOver(mousePosition))
                return;
        }
    }

    void FieldView::MouseWheelScrolledEvent(sf::Event sfEvent)
    {
        if (sfEvent.mouseWheelScroll.delta > 0)
        {
            for (int i = 0; i < sfEvent.mouseWheelScroll.delta; i++)
                renderTextureSprite.scale(1.1, 1.1);
        }
        else
        {
            for (int i = sfEvent.mouseWheelScroll.delta; i < 0; i++)
                renderTextureSprite.scale(1 / 1.1, 1 / 1.1);
        }
    }

    void FieldView::TextEnteredEvent(sf::Event sfEvent)
    {
        //Does not have any textboxes
    }
    void FieldView::WindowResizedEvent(sf::Event sfEvent)
    {
    }
}