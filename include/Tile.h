#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>

enum tileState{nonActive = 0, clickedLeft, disabled, clickedRight, doubleClickedRight};

using namespace sf;
using namespace std;

class Tile{

    public:

    RectangleShape tile;

    Texture texture;

    public:

    string realTexture;

    string actualTexture;

    string startTexture;

    shared_ptr <RenderWindow> window;

    map <string, int> tileStates;

    int actualState;

    public:

    Tile(float height, float width, float x, float y, string startTexture1, string tileTexture, shared_ptr <RenderWindow> window1);

    void putTexture(string tileTexture);

    template <class T>
    void drawShape(T graphic);

    void update();

    void events(Event event);

    RectangleShape &returnGraphic();

    Vector2f returnPosition();

    Vector2f returnSize();
};

#endif // TILE_H
