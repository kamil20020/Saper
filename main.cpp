#include <SFML/Graphics.hpp>
#include <memory>

#include "Game.h"

using namespace sf;
using namespace std;

int main(){

    srand(time(0));

    shared_ptr <Game> game = make_shared <Game>();

    game -> gameLoop();

    return 0;
}
