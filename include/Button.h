#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <functional>
#include <map>

enum buttonState{withoutActivity = 0, buttonPressed, buttonHovered};

using namespace sf;
using namespace std;

class Button{

    protected:

    RectangleShape rect;

    Font font;

    Text text;

    int actualState;

    shared_ptr <RenderWindow> window;

    map <string, int> buttonStates;

    public:

    Button(shared_ptr <RenderWindow> window1, float width, float height, float x, float y, string message);

    template <class T>
    void drawShape(T graphic);

    void pushFont(string fontSource, string message);

    bool isButtonPressed();

    bool isButtonHovered();

    void update();

    void events(Event event);
};

#endif // BUTTON_H
