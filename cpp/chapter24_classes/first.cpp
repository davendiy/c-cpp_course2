// Created by David Zashkolny on 22.03.19.
// 2 course, comp math
// Taras Shevchenko National University of Kyiv
// email: davendiy@gmail.com
//

#include <iostream>

enum ChessPiece{
    EMPTY_SQUARE,
    WHITE_PAWN,
};


enum PlayerColor{
    WHITE,
    BLACK
};


class ChessBoard{
public:
    ChessBoard();
    ChessBoard(int board_size);
    ChessPiece getPiece(int x, int y);
    PlayerColor getMove();
    void makeMove(int from_x, int from_y, int to_x, int to_y);

private:
    ChessPiece _board[8][8];
    PlayerColor _whose_move;
};


ChessBoard::ChessBoard() {
    _whose_move = WHITE;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            _board[i][j] = EMPTY_SQUARE;
        }
    }
}


ChessBoard::ChessBoard(int board_size) {
    ChessBoard **_board;
    _board = new ChessBoard* [board_size];
    for (int i = 0; i < board_size; i++){
        _board[i] = new ChessBoard [board_size];
        for (int j = 0; j < board_size; j++){
            _board[i][j] = EMPTY_SQUARE;
        }
    }
    _whose_move = WHITE;
}


PlayerColor ChessBoard::getMove() {
    return _whose_move;
}


ChessPiece ChessBoard::getPiece(int x, int y) {
    return _board[x][y];
}


void ChessBoard::makeMove(int from_x, int from_y, int to_x, int to_y) {
    _board[to_x][to_y] = _board[from_x][from_y];
    _board[from_x][from_y] = EMPTY_SQUARE;
}



class LinkedListNode{
public:
    ~LinkedListNode();
    int val;
    LinkedListNode *p_next;
};


LinkedListNode::~LinkedListNode() {
    delete p_next;
}


class LinkedList{
public:
    LinkedList();     // constructor
    ~LinkedList();    // destructor
    LinkedList&operator=(const LinkedList& rhs);
    void insert(int val);
    LinkedList(const LinkedList& other);

private:
    LinkedListNode *_p_head;
};


LinkedList::LinkedList() {

}

LinkedList::LinkedList(const LinkedList &other)
    :_p_head(NULL)
{
    LinkedListNode *p_itr = other._p_head;
    while(p_itr != NULL){
        insert(p_itr->val);
    }

}


void LinkedList::insert(int val) {

}


LinkedList::~LinkedList() {
    delete _p_head;
}


LinkedList& LinkedList::operator= (const LinkedList& other){
    if (this == &other){
        return *this;
    }

    delete _p_head;
    _p_head = NULL;
    LinkedListNode *p_itr = other._p_head;
    while (p_itr != NULL){
        insert(p_itr->val);
    }
    return *this;
}