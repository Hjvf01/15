#include <QCoreApplication>
#include <QDebug>

#include "../../src/board.h"


int main(int, char**) {
    Board board;
    cout << board << endl;

    qDebug() << board.asStringList();

    assert(board.getRow(10) == 2 && board.getCol(10) == 2);
    assert(board.getRow(15) == 3 && board.getCol(15) == 3);
    assert(board.getRow(0) == 0 && board.getCol(0) == 0);

    for(int i = 0; i < 16; i++)
        cout << "i: " << i << " - " << board.getRow(i) << "   " << board.getCol(i) << endl;

    return 0;
}
