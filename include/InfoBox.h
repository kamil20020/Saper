#ifndef INFOBOX_H
#define INFOBOX_H

#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
using namespace std;

class InfoBox{

    RectangleShape background;

    Font font;
    Text text;

    shared_ptr <RenderWindow> window;

    public:

    InfoBox(shared_ptr <RenderWindow> &window1, const Color &color,  float backgroundSizeX, float backgroundSizeY, float backgroundX, float backgroundY,
            string fontSource, string infoText);

    void updateFont(string infoText);
    void update();
};

#endif // INFOBOX_H
