#ifndef GAMESTATESCONTROLLER_H
#define GAMESTATESCONTROLLER_H

using namespace sf;
using namespace std;

class GameStatesController {

public:

    string actualState;
    string nextState;

    virtual void startState() = 0;

    virtual void resetState() = 0;

    virtual void events(Event event) = 0;

    virtual void update() = 0;
};

#endif // GAMESTATESCONTROLLER_H