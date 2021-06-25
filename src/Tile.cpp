#include "Tile.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

using namespace sf;
using namespace std;

Tile::Tile(float height, float width, float x, float y, string startTexture1, string tileTexture, shared_ptr <RenderWindow> window1):
    window(window1){

    tile.setSize(Vector2f(height, width));
    tile.setPosition(x, y);

    putTexture(startTexture1);

    realTexture = tileTexture;

    startTexture = startTexture1;

    tileStates["nonActive"] = nonActive;
    tileStates["clickedRight"] = clickedLeft;
    tileStates["clickedRight"] = clickedRight;
    tileStates["disabled"] = disabled;

    actualState = nonActive;
}

void Tile::putTexture(string tileTexture){

    texture.loadFromFile(tileTexture);
    tile.setTexture(&texture);

    actualTexture = tileTexture;
}

template <class T>
void Tile::drawShape(T graphic){

    window -> draw(graphic);
}

void Tile::update(){

    drawShape(tile);
}

void Tile::events(Event event){

    if(event.type == Event::MouseButtonPressed){

        if(event.mouseButton.button == Mouse::Left){

            if(tile.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y) == true){

                if(actualState != clickedRight){

                    actualState = clickedLeft;
                }
            }
        }
        else if(event.mouseButton.button == Mouse::Right){

            if(tile.getGlobalBounds().contains(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y) == true){

                if(actualState == clickedRight){

                    actualState = doubleClickedRight;

                }
                else if(actualState == nonActive){

                    actualState = clickedRight;
                }
            }
        }
    }
}

RectangleShape &Tile::returnGraphic(){

    return tile;
}

Vector2f Tile::returnPosition(){

    return tile.getPosition();
}

Vector2f Tile::returnSize(){

    return tile.getSize();
}
