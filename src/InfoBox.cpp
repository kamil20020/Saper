#include "InfoBox.h"

using namespace sf;
using namespace std;

InfoBox::InfoBox(shared_ptr <RenderWindow> &window1, const Color &color,  float backgroundSizeX, float backgroundSizeY,
                 float backgroundX, float backgroundY, string fontSource, string infoText): window(window1){

    background.setFillColor(color);
    background.setPosition(backgroundX, backgroundY);
    background.setSize(Vector2f(backgroundSizeX, backgroundSizeY));

    font.loadFromFile(fontSource);

    text.setFont(font);
    text.setString(infoText);
    text.setCharacterSize(36);
    text.setFillColor(Color::Black);
    text.setPosition(background.getPosition().x + background.getSize().x/2 - text.getGlobalBounds().width/2 - 5,
                     background.getPosition().y + background.getSize().y/2 - text.getGlobalBounds().height/2 - 10);

}

void InfoBox::updateFont(string infoText){

    text.setString(infoText);
}

void InfoBox::update(){

    window -> draw(background);
    window -> draw(text);
}

