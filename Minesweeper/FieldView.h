#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Button.h"
#include "IView.h"
#include "MinesweeperField.h"
#include "Settings.h"
#include "TextBox.h"

using namespace sf;
using namespace std;

namespace minesweeper
{
    class FieldView : public IView
    {
    public:

        FieldView(int bombCount, int countX, int countY, Vector2u displaySize);
        FieldView();
        void InitializeFieldView(int bombCount, int countX, int countY);
        virtual void InitializeView(Vector2f displaySize);
        virtual void DrawView(RenderTarget& renderTarget);
        virtual ViewId MouseButtonPressedEvent(Event sfEvent, Vector2i mousePosition);
        virtual void MouseButtonReleasedEvent(sf::Event sfEvent);
        virtual void MouseHoverEvent(sf::Vector2i mousePosition);
        virtual void MouseWheelScrolledEvent(sf::Event sfEvent);
        virtual void TextEnteredEvent(sf::Event sfEvent);
        virtual void WindowResizedEvent(sf::Event sfEvent);

        Button* buttonMenu;
        Button* buttonReload;

        RenderTexture renderTextureGameField;
        RenderTexture renderTextureMenuBar;

        RectangleShape menuBar;
        RectangleShape textBoxBombCount;
        RectangleShape textBoxElapsedTime;
        RectangleShape oldbuttonReload;

        Sprite renderTextureSprite;
        Sprite menuBarSprite;
        Sprite reloadSprite;

        Text textBombCount;
        Text textElapsedTime;

        Clock clock;
        Time dt;

        vector<vector<MinesweeperField>> bombField;

        int gameOver;
        bool drawField;
        bool mouseCounter;

    private:

        void oldbuttonReloadClick(Vector2i mousePosition);
        void buttonReloadReleased();
        void createField();
        void loadTextures();
        void fieldLeftClicked(Vector2i mousePosition);
        void fieldRightClicked(Vector2i mousePosition);
        void revealField();
        void revealSurroundingFields(const uint64_t y, const uint64_t x);
        void setClickedFieldTexture(const uint64_t y, const uint64_t x);
        void setFlag(MinesweeperField& field);
        void setSurroundingFlags(const uint64_t y, const uint64_t x);
        virtual void initializeComponents();

        static ViewId buttonReloadClick(void* ptr); // ptr has to be a pointer to the Object itself
        static ViewId buttonMenuClick(void* ptr); // ptr has to be a pointer to the Object itself

        Texture textureFieldBomb;
        Texture textureFieldClickedBomb;
        Texture textureFieldFlag;
        Texture textureFieldWrongFlag;
        Texture textureFieldCovered;
        Texture textureField0;
        Texture textureField1;
        Texture textureField2;
        Texture textureField3;
        Texture textureField4;
        Texture textureField5;
        Texture textureField6;
        Texture textureField7;
        Texture textureField8;

        Texture textureReload;
        Texture textureMenu;

        stringstream sstream;

        std::vector<Button*> buttonVector;
        std::vector<TextBox*> textBoxVector;

        Font font;

        int bombsCount;  //Stores the Value of the Bombs, does not get changed
        int bombCounter; //Displays the Bombs on the top left corner of the field view
        int nonBombsCounter;
        int countX;
        int countY;
    };
}
#endif // !FIELDVIEW_H