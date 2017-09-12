#include "board.h"


Board::Board(const QList<QList<int>> &_board) : board(_board) {}
Board::Board() : board(make()) {}


QList<QList<int>> Board::make() const {
    qsrand(QTime::currentTime().msec());

    auto _board = _make();
    while (! solvable(_board)) {
        _board = _make();
    }

    assert(solvable(_board));
    return _board;
}


int Board::getRow(const int i) const {
    assert(i <= height() * width() - 1);
    return i / SIZE;
}

int Board::getCol(const int i) const {
    assert(i <= height() * width() - 1);
    return i % SIZE;
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
    QList<QList<int>> result = make_final(SIZE);

    for(int i = 0; i < 10; i++) {
        result.swap(RANDOM(0, SIZE), RANDOM(0, SIZE));
    }

    for(QList<int>& row: result) {
        row.swap(RANDOM(0, SIZE), RANDOM(0, SIZE));
    }

    for(int i = 0; i < 100; i++) {
        std::swap(
            result[RANDOM(0, SIZE)][RANDOM(0, SIZE)],
            result[RANDOM(0, SIZE)][RANDOM(0, SIZE)]
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

    for(int elem = 1; elem <= SIZE * SIZE - 1; elem++) {
        sum += findAmount(_board, elem) + e;
    }

    return ((sum % 2) == 0);
}


QList<QList<int>> make_final(const int d) {
    int count = 1;
    QList<QList<int>> result;
    for (int i = 0; i < d; i++) {
        result.append(QList<int>());
        for (int j = 0; j < d; j++) {
            result[i].append(count);
            ++count;
        }
    }

    result[d - 1][d - 1] = 0;
    return result;
}
