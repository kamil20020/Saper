#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <map>

#include "Button.h"
#include "GameStatesControler.h"
#include "Board.h"

using namespace sf;
using namespace std;

enum gameDifficults{easy = 0, medium, hard};

class Button;

class Options: public GameStatesControler{

    shared_ptr <RenderWindow> window;

    map <string, shared_ptr <Button>> buttons;

    int actualDifficult;

    shared_ptr <Board> board;

    public:

    Options(shared_ptr <RenderWindow> window1, shared_ptr <Board> board1);

    void setBoardsParameters(int gameDifficult1);

    void startState();

    void resetState();

    void resetBoard();

    void update();

    void events(Event event);
};

#endif // OPTIONS_H
