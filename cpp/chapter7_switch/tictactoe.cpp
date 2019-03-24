// Created by David Zashkolny on 18.02.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

// tic tac toe pvp in the console using enum

#include <iostream>
using namespace std;

// possible values on the game desk
enum TicTacToeSquare {TTTS_BLANK = ' ', TTTS_O = 'o', TTTS_X = 'x'};

// possible statuses of the game result
enum ResGame {WIN_X = 'x', WIN_O = 'o', DRAW, IN_GAME};

// possible values of player
enum Player {X = 'x', O = 'o'};


// main desk (array 3x3 transformed into array 1x9)
TicTacToeSquare MainDesk[9];


void startGame();
    // function that fills main desk with start values

int user2program(int x, int y);
    // transform user coordinates into array index

    // :param x: number of row
    // :param y: number of column
    // :return: index of array

bool checkDraw();
    // function that checks main desk if there is any free place

    // :return: true if there is no free place

bool checkWin(Player player);
    // function that checks if there are 3 respective symbols
    // in a row for such player

    // :param player: x or o
    // :return: true if there are 3 symbols in a row

void turn(Player player);
    // player's turn on the desk

void printDesk();
    // should be obvious

Player changePlayer(Player player);
    // returns opposite player

int main(){

    ResGame gameStatus = IN_GAME;
    Player tmpPlayer = X;
    char tmpAnswer;
    cout << "Do you wanna play? (y/n): ";
    cin >> tmpAnswer;
    if (tmpAnswer != 'y' && tmpAnswer != 'Y'){
        cout << "Exit.." << endl;
        return 0;
    }

    startGame();          // prepare desk for game
    while (gameStatus == IN_GAME){
        printDesk();      // print desk on each turn
        turn(tmpPlayer);  // doing turn

        // check for the end of game
        if (checkWin(tmpPlayer)) {
            if (tmpPlayer == X) gameStatus = WIN_X;
            else gameStatus = WIN_O;
        }
        else if (checkDraw()) gameStatus = DRAW;

        tmpPlayer = changePlayer(tmpPlayer);  // swap player
    }

    if (gameStatus == DRAW) cout << "Draw!" << endl;
    else cout << char(gameStatus) << " win!" << endl;
    return 0;
}


void startGame(){
    // function that fills main desk with start values
    for (int i=0; i<9; i++){
        MainDesk[i] = TTTS_BLANK;
    }
}


int user2program(int x, int y){
    // transform user coordinates into array index

    // :param x: number of row
    // :param y: number of column
    // :return: index of array

    return 3 * (x - 1) + y - 1;
}


bool checkWin(Player player){
    // function that checks if there are 3 respective symbols
    // in a row for such player

    // :param player: x or o
    // :return: true if there are 3 symbols in a row

    bool res;
    TicTacToeSquare tmpTTTS;  // value that will be searched
    if (player == X) tmpTTTS = TTTS_X;
    else tmpTTTS = TTTS_O;

    // check all possible triples in a row
    res = (MainDesk[0] == tmpTTTS && MainDesk[1] == tmpTTTS && MainDesk[2] == tmpTTTS)        // rows
          || (MainDesk[3] == tmpTTTS && MainDesk[4] == tmpTTTS && MainDesk[5] == tmpTTTS)
          || (MainDesk[6] == tmpTTTS && MainDesk[7] == tmpTTTS && MainDesk[8] == tmpTTTS)

          || (MainDesk[0] == tmpTTTS && MainDesk[3] == tmpTTTS && MainDesk[6] == tmpTTTS)   // columns
          || (MainDesk[1] == tmpTTTS && MainDesk[4] == tmpTTTS && MainDesk[7] == tmpTTTS)
          || (MainDesk[2] == tmpTTTS && MainDesk[5] == tmpTTTS && MainDesk[8] == tmpTTTS)

          || (MainDesk[0] == tmpTTTS && MainDesk[4] == tmpTTTS && MainDesk[8] == tmpTTTS)   // diagonals
          || (MainDesk[2] == tmpTTTS && MainDesk[4] == tmpTTTS && MainDesk[6] == tmpTTTS);
    return res;
}


bool checkDraw(){
    // function that checks main desk if there is any free place

    // :return: true if there is no free place
    bool res = true;
    for (int i=0; i<9; i++)
        if (MainDesk[i] == TTTS_BLANK){
            res = false;
            break;
        }
    return res;
}


void turn(Player player){
    // player's turn on the desk

    int user_x, user_y, index;                 // params entered by user
    cout << "\n\nYour turn, " << char(player) << " (row, column):" << endl;
    while (true){
        cout << "--> ";
        cin >> user_x >> user_y;               // input
        index = user2program(user_x, user_y);  // transform

        // check correctness
        if (index > 8 || index < 0 || MainDesk[index] != TTTS_BLANK)
            cout << "incorrect coordinates, try again" << endl;
        else break;
    }
    
    // put respective symbol on entered place
    if (player == O) MainDesk[index] = TTTS_O;
    else MainDesk[index] = TTTS_X;
}


void printDesk(){
    // should be obvious
    cout << "   1   2   3" << endl;
    cout << "1  " << char(MainDesk[0]) << "   " << char(MainDesk[1]) << "   " << char(MainDesk[2]) << endl;
    cout << "2  " << char(MainDesk[3]) << "   " << char(MainDesk[4]) << "   " << char(MainDesk[5]) << endl;
    cout << "3  " << char(MainDesk[6]) << "   " << char(MainDesk[7]) << "   " << char(MainDesk[8]) << endl;
}


Player changePlayer(Player player){
    // swap player to opposite
    if (player == X) return O;
    else return X;
}