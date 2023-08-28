#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>

#include "GameStatesController.h"
#include "Tile.h"
#include "Button.h"
#include "InfoBox.h"

using namespace sf;
using namespace std;

class Board: public GameStatesController{

    enum extraStates{lost = 3, won = 4};

    shared_ptr <RenderWindow> window;

    Texture texture;

    map <string, string> tileTextures;

    int leftMines;

    bool doHighestResult;

    shared_ptr <Clock> boardClock;

    bool boardEnded;

    int finalTime;

    vector <shared_ptr <Tile>> tiles;

    int howMuchTilesInX, howMuchTilesInY, howMuchMines;
    float tilesHeight, tilesWidth;

    float unclikedNumberTiles;

    map <string, shared_ptr <InfoBox>> infoBoxes;

    public:

    Board(shared_ptr <RenderWindow> window1);

    void updateTime();

    void updateLeftMines();

    void saveResultsToFile();

    bool checkDoLose(shared_ptr <Tile> tile);

    bool checkDoWin();
    void whatDoWhenWon();
    void whatDoWhenLost();
    void whatDoWhenBoardEnded();

    void whatDoWhenTileisLeftClicked(int index);
    void whatDoWhenTileIsLeftClickedWhenWasBeforeLeftClicked(int index);
    void updateTiles(int index);

    void loadTileTextures();

    void createTiles();

    vector <int> randomizeMines();

    vector <float> returnPosibleNumberSPositions(const int i);

    void putNumberTiles(vector <int> minesWek);

    vector <float> returnhavingZeroBorderers(const int index);

    void exploration0NumberTilesAfterClick0(const int index);

    void startState(){}

    void startState(int howMuchTilesInX, int howMuchTilesInY, int howMuchMines, int tilesWidth, int tilesHeight);

    void resetState();

    void events(Event event);

    void update();
};

#endif // BOARD_H
