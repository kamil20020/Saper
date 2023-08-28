#include "Board.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;
using namespace sf;

Board::Board(shared_ptr <RenderWindow> window1): window(window1){

    nextState = "Options";

    loadTileTextures();
}

void Board::startState(int howMuchTilesInX1, int howMuchTilesInY1, int howMuchMines1, int tilesWidth1, int tilesHeight1){

    actualState = "Board";

    boardEnded = false;

    howMuchTilesInX = howMuchTilesInX1;
    howMuchTilesInY = howMuchTilesInY1;

    howMuchMines = howMuchMines1;

    tilesWidth = tilesWidth1;
    tilesHeight = tilesHeight1;

    unclikedNumberTiles = howMuchTilesInX * howMuchTilesInY - howMuchMines;

    createTiles();

    leftMines = howMuchMines;

    finalTime = 0;

    doHighestResult = false;

    boardClock = nullptr;

    infoBoxes["timeBox"] = make_shared <InfoBox> (window, Color::Green, 100, 100, window -> getSize().x/2 - 50 + 500,
                                                  window -> getSize().y/2 - 50 - 300, "OpenSans-Regular.ttf", to_string(0));

    infoBoxes["leftMinesBox"] = make_shared <InfoBox> (window, Color::Green, 100, 100, window -> getSize().x/2 - 50 + 500,
                                                       window -> getSize().y/2 - 50 - 200, "OpenSans-Regular.ttf",
                                                       to_string(leftMines));
}

void Board::resetState(){

    if(tiles.size() > 0){

        tiles.clear();
    }

    infoBoxes.clear();
}

void Board::loadTileTextures(){

    tileTextures["bg"] = "img/bg.png";
    tileTextures["flag"] = "img/flag.png";
    tileTextures["mine"] = "img/mine.png";
    tileTextures["0"] = "img/0.png";
    tileTextures["1"] = "img/1.png";
    tileTextures["2"] = "img/2.png";
    tileTextures["3"] = "img/3.png";
    tileTextures["4"] = "img/4.png";
    tileTextures["5"] = "img/5.png";
    tileTextures["6"] = "img/6.png";
    tileTextures["7"] = "img/7.png";
    tileTextures["8"] = "img/8.png";
}

vector <int> Board::randomizeMines(){

    vector <int> minesWek;

    int index;

    bool check = false;

    for(int i=0; i < howMuchMines; i++){

        index = rand()%((howMuchTilesInX)*(howMuchTilesInY));

        for(int j=0; j < minesWek.size(); j++){

            if(index == minesWek[j]){

                check = true;

                break;
            }
        }

        if(check == true){

            index = rand()%((howMuchTilesInX)*(howMuchTilesInY));

            check = false;

            i--;
        }
        else{

            minesWek.push_back(index);
        }
    }

    sort(minesWek.begin(), minesWek.end());

    return minesWek;
}

vector <float> Board::returnPosibleNumberSPositions(const int i){

    vector <float> posibleMinesPositions(8);

    posibleMinesPositions[0] = i - howMuchTilesInX - 1;
    posibleMinesPositions[1] = i - howMuchTilesInX;
    posibleMinesPositions[2] = i - howMuchTilesInX + 1;
    posibleMinesPositions[3] = i - 1;
    posibleMinesPositions[4] = i + 1;
    posibleMinesPositions[5] = i + howMuchTilesInX - 1;
    posibleMinesPositions[6] = i + howMuchTilesInX;
    posibleMinesPositions[7] = i + howMuchTilesInX + 1;

    for(int j=0; j < posibleMinesPositions.size(); j++){

        if(posibleMinesPositions[j] >= 0 && posibleMinesPositions[j] < tiles.size() &&
           (abs(tiles[i] -> returnPosition().x - tiles[posibleMinesPositions[j]] -> returnPosition().x) <= tiles[i] -> returnSize().x &&
            abs(tiles[i] -> returnPosition().x + tiles[i] -> returnSize().x - tiles[posibleMinesPositions[j]] -> returnPosition().x - tiles[posibleMinesPositions[j]] -> returnSize().x) <= tiles[posibleMinesPositions[j]] -> returnSize().x) &&
            (abs(tiles[i] -> returnPosition().y - tiles[posibleMinesPositions[j]] -> returnPosition().y) <= tiles[i] -> returnSize().y ||
            abs(tiles[i] -> returnPosition().y + tiles[i] -> returnSize().y - tiles[posibleMinesPositions[j]] -> returnPosition().y - tiles[posibleMinesPositions[j]] -> returnSize().y) <= tiles[posibleMinesPositions[j]] -> returnSize().y)){

        }
        else{

            posibleMinesPositions.erase(posibleMinesPositions.begin() + j);

            j--;
        }
    }

    return posibleMinesPositions;
}

void Board::putNumberTiles(vector <int> minesWek){

    vector <float> posibleMinesPositions;

    int howMuchBordererMines;

    for(int i=0; i < tiles.size(); i++){

        posibleMinesPositions = returnPosibleNumberSPositions(i);

        howMuchBordererMines = 0;

        if(tiles[i] -> realTexture != tileTextures["mine"]){ //2

            for(int j=0; j < posibleMinesPositions.size(); j++){

                if(tiles[posibleMinesPositions[j]] -> realTexture == tileTextures["mine"]){ //2

                    howMuchBordererMines++;
                }
            }

            tiles[i] -> realTexture = tileTextures[to_string(howMuchBordererMines)];
        }
    }

    posibleMinesPositions.clear();
}

void Board::createTiles(){

    vector <int> minesWek = randomizeMines();

    float x = 0;

    float y = 0;

    int mainIndex;

    int minesWekIndex = 0;

    for(int i=0; i < howMuchTilesInY; i++){

        for(int j=0; j < howMuchTilesInX; j++){

            tiles.push_back(make_shared <Tile> (tilesHeight, tilesWidth, x, y, tileTextures["bg"],
                                                tileTextures["bg"], window));

            mainIndex = i * howMuchTilesInX + j;

            if(minesWek[minesWekIndex] == mainIndex){

                tiles[mainIndex] -> realTexture = tileTextures["mine"];

                if(minesWekIndex + 1 < minesWek.size()){

                   minesWekIndex++;
                }
            }
            else{

                tiles[mainIndex] -> realTexture = tileTextures["bg"];
            }

            x = x + tilesWidth;
        }

        x = 0;

        y = y + tilesHeight;
    }

    putNumberTiles(minesWek);

    minesWek.clear();
}

vector <float> Board::returnhavingZeroBorderers(const int index){

    vector <float> borderers = returnPosibleNumberSPositions(index);

    vector <float> havingZeroBorderers;

    for(int i=0; i < borderers.size(); i++){

        if(tiles[borderers[i]] -> realTexture != tiles[borderers[i]] -> actualTexture){

            if(tiles[borderers[i]] -> realTexture != tileTextures["mine"]){ // && tiles[borderers[i]] -> actualTexture != tileTextures["flag"] <- tu ¿eby blokowaæ niszczenie flag

                tiles[borderers[i]] -> putTexture(tiles[borderers[i]] -> realTexture);

                tiles[borderers[i]] -> actualState = nonActive;

                unclikedNumberTiles--;

                if(tiles[borderers[i]] -> realTexture == tileTextures["0"]){

                    havingZeroBorderers.push_back(borderers[i]);
                }
            }
        }
    }

    return havingZeroBorderers;
}

void Board::exploration0NumberTilesAfterClick0(const int index){

    if(tiles[index] -> realTexture == tileTextures["0"]){

        vector <float> firstBorderers = returnhavingZeroBorderers(index);

        vector <vector<float>> havingZeroBorderers;

        for(int j=0; j < firstBorderers.size(); j++){

            havingZeroBorderers.push_back(returnhavingZeroBorderers(firstBorderers[j]));
        }

        vector <float> bufor;

        while(havingZeroBorderers.size() > 0){

            vector <vector<float>> borderersToThis;

            for(int j=0; j < havingZeroBorderers.size(); j++){

                for(int k=0; k < havingZeroBorderers[j].size(); k++){

                    bufor = returnhavingZeroBorderers(havingZeroBorderers[j][k]);

                    if(bufor.size() > 0){

                        borderersToThis.push_back(bufor);
                    }
                }
            }

            havingZeroBorderers = borderersToThis;
        }
    }
}

void Board::events(Event event){

    if(event.type == Event::KeyPressed){

        if(Keyboard::isKeyPressed(Keyboard::Escape)){

            actualState = "Close";
        }
    }

    if(actualState == "Board" && boardEnded == false) {

        for(int i=0; i < tiles.size(); i++){

            tiles[i] -> events(event);
        }
    }
}

void Board::saveResultsToFile(){

    fstream file;

    file.open("results.txt", ios::in | ios::out);

    string check = to_string(howMuchTilesInX) + "x" + to_string(howMuchTilesInY) + "m" + to_string(howMuchMines);

    string bufor;

    vector <string> allFile;

    string sNumber = "";

    bool checkDoSame = true;

    int line;

    int countLine = 0;

    while(file.eof() == false){

        getline(file, bufor);

        if(bufor != ""){

            allFile.push_back(bufor);
        }
        else{

            break;
        }

        checkDoSame = true;

        for(int i=0; i < check.size(); i++){

            if(bufor[i] != check[i]){

                checkDoSame = false;

                break;
            }
        }

        if(checkDoSame == true){

            int index;

            for(int i=0; i < bufor.size(); i++){

                if(bufor[i] == 't'){

                    index = i;

                    break;
                }
            }

            for(int i=index+1; i < bufor.size(); i++){ //1 bo pomijam t

                sNumber = sNumber + bufor[i];
            }

            line = countLine;
        }

        countLine++;
    }

    file.close();

    if(sNumber != ""){

        if(finalTime < stoi(sNumber)){

            file.open("results.txt", ios::out);

            allFile[line] = check + "t" + to_string(finalTime);

            for(int i=0; i < allFile.size(); i++){

                file << allFile[i] <<endl;
            }

            infoBoxes["highestResult"] = make_shared <InfoBox> (window, Color::Green, 600, 200, window -> getSize().x/2 - 300,
                                                          window -> getSize().y/2 - 50 - 300, "OpenSans-Regular.ttf",
                                                          "Osiagnieto najwyzszy wynik: " + to_string(finalTime) + "\n" +
                                                          "A poprzedni najwyzszy to: " + sNumber);

            doHighestResult = true;
        }
    }
    else{

        file.open("results.txt", ios::out | ios::app);

        file << check << "t" << finalTime <<endl;

        infoBoxes["highestResult"] = make_shared <InfoBox> (window, Color::Green, 600, 200, window -> getSize().x/2 - 300,
                                                          window -> getSize().y/2 - 50 - 300, "OpenSans-Regular.ttf",
                                                          "Osiagnieto najwyzszy wynik: " + to_string(finalTime) + "\n" +
                                                          "A poprzedni najwyzszy to: " + sNumber);

        doHighestResult = true;
    }

    file.close();
}

void Board::whatDoWhenWon(){

    actualState = won;

    whatDoWhenBoardEnded();

    infoBoxes["endInfo"] = make_shared <InfoBox> (window, Color::Green, 300, 120, window -> getSize().x/2 - 150,
                                                  window -> getSize().y/2 - 40, "OpenSans-Regular.ttf", "Win");
    saveResultsToFile();
}

void Board::whatDoWhenLost(){

    actualState = lost;

    whatDoWhenBoardEnded();

    infoBoxes["endInfo"] = make_shared <InfoBox> (window, Color::Green, 300, 120, window -> getSize().x/2 - 150,
                                                  window -> getSize().y/2 - 40, "OpenSans-Regular.ttf", "Lost");
}

void Board::whatDoWhenBoardEnded(){

    boardEnded = true;

    finalTime = boardClock -> getElapsedTime().asSeconds();

    boardClock = nullptr;

    infoBoxes["endText"] = make_shared <InfoBox> (window, Color::Green, 1000, 150, window -> getSize().x/2 - 500,
                                                   window -> getSize().y/2 - 75 + 200, "OpenSans-Regular.ttf",
                                                   "Nacisnij klawisz ESC aby przejsc do menu gry");
}

void Board::whatDoWhenTileisLeftClicked(int index){

    tiles[index] -> putTexture(tiles[index] -> realTexture);

    if(checkDoLose(tiles[index]) == false){

        unclikedNumberTiles--;

        exploration0NumberTilesAfterClick0(index);

        if(checkDoWin() == true){

            whatDoWhenWon();
        }
    }
    else{

        whatDoWhenLost();
    }

    tiles[index] -> actualState = nonActive;
}

void Board::whatDoWhenTileIsLeftClickedWhenWasBeforeLeftClicked(int index){

    vector <float> posibleMinesPositions = returnPosibleNumberSPositions(index);

    int howMuchFlags = 0;

    for(int j=0; j < posibleMinesPositions.size(); j++){

        if(tiles[posibleMinesPositions.at(j)] -> actualTexture == tileTextures["flag"]){

            howMuchFlags++;
        }
    }

    cout<< howMuchFlags <<endl;

    if(howMuchFlags > 0 && int(tiles[index] -> realTexture[4] - '0') == howMuchFlags){

        for(int j=0; j < posibleMinesPositions.size(); j++){

            if(tiles[posibleMinesPositions.at(j)] -> actualTexture != tiles[posibleMinesPositions.at(j)] -> realTexture &&
               tiles[posibleMinesPositions.at(j)] -> actualTexture != tileTextures["flag"]){

                whatDoWhenTileisLeftClicked(posibleMinesPositions.at(j));
            }
        }

    }

    tiles[index] -> actualState = nonActive;
}

void Board::updateTiles(int index){

    if(boardEnded != true){

        //cout<< tiles[index] -> actualState <<endl;

        switch (tiles[index] -> actualState){

            if(Keyboard::isKeyPressed(Keyboard::S)){

                cout<< tiles[index] -> actualState <<endl;
            }

            case clickedRight:

                if(tiles[index] -> actualTexture != tiles[index] -> realTexture){

                    if(tiles[index] -> actualTexture != tileTextures["flag"]){

                        tiles[index] -> putTexture(tileTextures["flag"]);

                        leftMines--;

                        updateLeftMines();
                    }
                }

            break;

            case doubleClickedRight:

                if(tiles[index] -> actualTexture != tiles[index] -> realTexture){

                    if(tiles[index] -> actualTexture == tileTextures["flag"]){

                        tiles[index] -> putTexture(tileTextures["bg"]);

                        tiles[index] -> actualState = nonActive;

                        leftMines++;

                        updateLeftMines();
                    }
                }

            break;

            case clickedLeft:

                //cout<< 1 <<endl;

                if(boardClock == nullptr){

                    boardClock = make_shared <Clock> ();
                }

                if(tiles[index] -> actualTexture != tiles[index] -> realTexture){

                    whatDoWhenTileisLeftClicked(index);

                }
                else{

                    whatDoWhenTileIsLeftClickedWhenWasBeforeLeftClicked(index);
                }

            break;
        }

    }
}

void Board::updateLeftMines(){

    infoBoxes["leftMinesBox"] -> updateFont(to_string(leftMines));
}

void Board::updateTime(){

    if(boardEnded == false && boardClock != nullptr){

        infoBoxes["timeBox"] -> updateFont(to_string(int(boardClock -> getElapsedTime().asSeconds())));
    }
}

void Board::update(){

    for(int i=0; i < tiles.size(); i++){

        tiles[i] -> update();

        updateTiles(i);
    }

    map <string, shared_ptr <InfoBox>>::iterator it;

    for(it = infoBoxes.begin(); it != infoBoxes.end(); it++){

        it -> second -> update();
    }

    updateTime();
}

bool Board::checkDoLose(shared_ptr <Tile> tile){

    if(tile -> actualTexture == tileTextures["mine"]){

        return true;
    }

    return false;
}

bool Board::checkDoWin(){

    if(unclikedNumberTiles == 0){

        return true;
    }

    return false;
}
