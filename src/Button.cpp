#include <iostream>

#include "Button.h"
#include "Board.h"

Button::Button(shared_ptr <RenderWindow> window1, float width, float height, float x, float y, string message):
    window(window1){

    rect.setSize(Vector2f(width, height));
    rect.setPosition(window1 -> getSize().x/2 - width/2, y);
    rect.setFillColor(Color::White);

    pushFont("OpenSans-Regular.ttf", message);

    buttonStates["withoutActivity"] = withoutActivity;
    buttonStates["buttonPressed"] = buttonPressed;
    buttonStates["buttonHovered"] = buttonHovered;

    actualState = withoutActivity;
}

template <class T>
void Button::drawShape(T graphic){

    window -> draw(graphic);
}

void Button::pushFont(string fontSource, string message){

    font.loadFromFile(fontSource);

    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(22);
    text.setFillColor(Color::Black);
    text.setPosition(rect.getPosition().x + rect.getSize().x/2 - text.getGlobalBounds().width/2 - 1, rect.getPosition().y + rect.getSize().y/2 - text.getGlobalBounds().height/2 - 5);
}

void Button::update(){

    drawShape(rect);
    drawShape(text);
}

void Button::events(Event event){

    if(rect.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y) == true){

        actualState = buttonStates["buttonPressed"];

        if(Mouse::isButtonPressed(Mouse::Left)){

            actualState = buttonPressed;
        }
        else{

            actualState = buttonHovered;
        }
    }
    else{

        actualState = withoutActivity;
    }
}

bool Button::isButtonPressed(){

    if(actualState == buttonPressed){

        return true;
    }

    return false;
}

bool Button::isButtonHovered(){

    if(actualState == buttonHovered){

        return true;
    }

    return false;
}

