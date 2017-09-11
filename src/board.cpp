#include "board.h"


Board::Board(const QList<QList<int>> &_board) : board(_board) {}
Board::Board() : board(make()) {}
Board::~Board() {}


QList<QList<int>> Board::make() const {
    qsrand(QTime::currentTime().msec());

    auto _board = _make();
    while (! solvable(_board)) {
        _board = _make();
    }

    assert(solvable(_board));
    return _board;
}


const QList<int>& Board::operator [](const int index) const {
    assert(index <= board.size() - 1);
    return board[index];
}

QList<int>& Board::operator [] (const int index) {
    assert(index <= board.size() - 1);
    return board[index];
}


void Board::swap(int left_row, int left_col, int right_row, int right_col) {
    int temp = board[left_row][left_col];
    board[left_row][left_col] = board[right_row][right_col];
    board[right_row][right_col] = temp;
}



QList<QList<int>> Board::_make() const {
    QList<QList<int>> result = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15,  0},
    };
    for(int i = 0; i < 10; i++) {
        result.swap(RANDOM(0, 3), RANDOM(0, 3));
    }

    for(QList<int>& row: result) {
        row.swap(RANDOM(0, 3), RANDOM(0, 3));
    }

    for(int i = 0; i < 10; i++) {
        std::swap(
            result[RANDOM(0, 3)][RANDOM(0, 3)],
            result[RANDOM(0, 3)][RANDOM(0, 3)]
        );
    }

    return result;
}


int Board::findRow(const QList<QList<int>>& _board, int num) const {
    for(int i = 0; i < _board.size(); i++)
        for(int j = 0; j < _board[i].size(); j++)
            if(_board[i][j] == num)
                return i;

    assert(false);
    return -1;
}

int Board::findCol(const QList<QList<int>>& _board, int num) const {
    for(int i = 0; i < _board.size(); i++)
        for(int j = 0; j < _board[i].size(); j++)
            if(_board[i][j] == num)
                return j;

    assert(false);
    return -1;
}


int Board::findAmount(const QList<QList<int>>& _board, int num) const {
    int amount = 0;
    int num_row = findRow(_board, num);

    for (int i = num_row; i < _board.size(); i++) {
        if (i == num_row) {
            for (int j = findCol(_board, num); j < _board[i].size(); j++)
                if (_board[i][j] != 0 && _board[i][j] < num) {
                    ++amount;
                }
        } else {
            for (int j = 0; j < _board[i].size(); j++) {
                if(_board[i][j] != 0 && _board[i][j] < num) {
                    ++amount;
                }
            }
        }
    }

    return amount;
}


bool Board::solvable(const QList<QList<int>>& _board) const {
    int sum = 0;
    int e = findRow(_board, 0) + 1;

    assert(e != 0);

    for(int elem: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) {
        sum += findAmount(_board, elem) + e;
    }

    return ((sum % 2) == 0);
}
