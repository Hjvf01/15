#include <QCoreApplication>
#include <QDebug>

#include "../../src/board.h"

#include <iostream>
#include <ostream>
using namespace std;


ostream& operator << (ostream& os, const Board& board) {
    for (int i = 0; i < board.height(); i++) {
        for (int j = 0; j < board.width(); j++) {
            if (board[i][j] < 10) {
                os << "  " << board[i][j] << ", ";
            } else {
                os << " " << board[i][j] << ", ";
            }
        }
        os << endl;
    }
    return os;
}


int main(int, char**) {
    Board board;
    cout << board << endl;

    qsrand(QTime::currentTime().msec());
    for (int i = 0; i < 10; i++)
        cout << RANDOM(0, 3) << endl;

    assert(board.getRow(10) == 2 && board.getCol(10) == 2);
    assert(board.getRow(15) == 3 && board.getCol(15) == 3);
    assert(board.getRow(0) == 0 && board.getCol(0) == 0);

    for(int i = 0; i < 16; i++)
        cout << "i: " << i << " - " << board.getRow(i) << "   " << board.getCol(i) << endl;


    board = Board(make_final(10));
    cout << board << endl;

    return 0;
}
