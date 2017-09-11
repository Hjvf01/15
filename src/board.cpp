#include "board.h"


Board::Board(const QList<QList<int>> &_board) : board(_board) {}
Board::Board() {}
Board::~Board() {}


QList<QList<int>> Board::make() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distributor(0, 3);

    auto _board = _make(gen, distributor);
    while (! solvable(_board)) {
        _board = _make(gen, distributor);
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


string Board::str(void) const {
    string out;
    for(const QList<int>& row: board) {
        for(int elem: row) {
            if(elem < 10)
                out += " " + to_string(elem) + " ";
            else
                out += to_string(elem) + " ";
        }
        out += "\n";
    }

    return out;
}


void Board::swap(int left_row, int left_col, int right_row, int right_col) {
    int temp = board[left_row][left_col];
    board[left_row][left_col] = board[right_row][right_col];
    board[right_row][right_col] = temp;
}


QList<QList<int>> Board::_make(
        mt19937& gen, uniform_int_distribution<int> &distrub
) {
    QList<QList<int>> result = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15,  0},
    };

    shuffle(result.begin(), result.end(), gen);

    for(QList<int>& row: result)
        shuffle(row.begin(), row.end(), gen);

    for(int i = 0; i < 10; i++)
        std::swap(
            result[distrub(gen)][distrub(gen)],
            result[distrub(gen)][distrub(gen)]
        );

    return result;
}


bool Board::solvable(const QList<QList<int> > &board) {
    return true;
}
