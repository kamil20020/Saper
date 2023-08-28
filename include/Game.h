#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

#include "Options.h"
#include "Board.h"

using namespace sf;
using namespace std;

class Game{

    shared_ptr <RenderWindow> window;

    shared_ptr <Event> event;

    shared_ptr <GameStatesController> gameStatesControler;

    map <string, shared_ptr <GameStatesController>> gameStates;

    shared_ptr <GameStatesController> actualState;

    public:

    Game();

    void events();

    void update();

    void gameLoop();
};

#endif // GAME_H
