#include "Game.h"

#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;

Game::Game(){

    window = make_shared <RenderWindow> ();
    window -> create(VideoMode(1400, 800), "Saper");
    window -> setFramerateLimit(30);

    event = make_shared <Event> ();

    gameStates["Board"] = make_shared <Board> (window);
    gameStates["Options"] = make_shared <Options>(window, dynamic_pointer_cast <Board> (gameStates["Board"]));

    actualState = gameStates["Options"];
}

void Game::events(){

    actualState -> events(*event);
}

void Game::update(){

    actualState -> update();
}

void Game::gameLoop(){

    while (window -> isOpen()){

        while (window -> pollEvent(*event)){

            events();
        }

        if(actualState -> actualState == closeState){

            actualState -> actualState = running;

            actualState = gameStates[actualState -> nextState];
        }

        window -> clear(Color(220,220,220));

        update();

        window -> display();
    }
}


