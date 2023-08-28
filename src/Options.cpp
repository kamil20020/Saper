
#include "Options.h"

Options::Options(shared_ptr <RenderWindow> window1, shared_ptr <Board> board1):
    window(window1), board(board1){

    nextState = "Board";

    startState();

    buttons["NewGame"] = make_shared <Button>(window, 200, 100, 500, 100, "Nowa gra");
    buttons["Easy"] = make_shared <Button>(window, 200, 100, 500, 250, "Latwy");
    buttons["Medium"] = make_shared <Button>(window, 200, 100, 500, 400, "Sredni");
    buttons["Hard"] = make_shared <Button>(window, 200, 100, 500, 550, "Trudny");
    buttons["Quit"] = make_shared <Button>(window, 200, 100, 500, 700, "Wyjdz");

    actualDifficult = easy;

    actualState = "Board";
}

void Options::startState(){

    actualState = "Options";
}

void Options::resetState(){

    //startState();
}

void Options::update(){

    map <string, shared_ptr <Button>>::iterator it;

    for(it = buttons.begin(); it != buttons.end(); it++){

        it -> second -> update();
    }
}

void Options::events(Event event){

    if(event.type == Event::KeyPressed){

        if(Keyboard::isKeyPressed(Keyboard::Escape)){

            actualState = "Close";
        }
    }

    map <string, shared_ptr <Button>>::iterator it;

    for(it = buttons.begin(); it != buttons.end(); it++){

        it -> second -> events(event);
    }

    if(buttons["NewGame"] -> isButtonPressed()){

        resetBoard();
    }

    if(buttons["Easy"] -> isButtonPressed()){

        actualDifficult = easy;

        resetBoard();
    }

    if(buttons["Medium"] -> isButtonPressed()){

        actualDifficult = medium;

        resetBoard();
    }

    if(buttons["Hard"] -> isButtonPressed()){

        actualDifficult = hard;

        resetBoard();
    }

    if(buttons["Quit"] -> isButtonPressed()){

        window -> close();
    }
}

void Options::resetBoard(){

    board -> resetState();

    setBoardsParameters(actualDifficult);

    actualState = "Close";
}

void Options::setBoardsParameters(int gameDifficult1){

    actualDifficult = gameDifficult1;

    switch(gameDifficult1){

        case easy:

            board -> startState(10, 8, 10, 100, 100);

        break;

        case medium:

            board -> startState(18, 14, 40, 55, 55);

        break;

        case hard:

            board -> startState(24, 20, 99, 40, 40);

        break;
    }
}

