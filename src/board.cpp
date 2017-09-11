#include "board.h"


Board::Board(const QList<QList<int>> &_board) : board(_board) {}

Board::Board() : board(make()) {}

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


QList<QString> Board::asStringList() const {
    QList<QString> result;
    for (const QList<int>& row: board)
        for (int elem: row)
            result.append(QString::number(elem));

    return result;
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


int Board::findRow(int num) const {
    for(int i = 0; i < board.size(); i++)
        for(int j = 0; j < board[i].size(); j++)
            if(board[i][j] == num)
                return i;

    assert(false);
    return -1;
}

int Board::findCol(int num) const {
    for(int i = 0; i < board.size(); i++)
        for(int j = 0; j < board[i].size(); j++)
            if(board[i][j] == num)
                return j;

    assert(false);
    return -1;
}


int Board::findAmount(int num) const {
    int amount = 0;
    int num_row = findRow(num);

    for (int i = num_row; i < board.size(); i++) {
        if (i == num_row) {
            for (int j = findCol(num); j < board[i].size(); j++)
                if (board[i][j] != 0 && board[i][j] < num) {
                    ++amount;
                }
        } else {
            for (int j = 0; j < board[i].size(); j++) {
                if(board[i][j] != 0 && board[i][j] < num) {
                    ++amount;
                }
            }
        }
    }

    return amount;
}


bool Board::solvable(const QList<QList<int>>& _board) const {
    int sum = 0;
    int e = findRow(0) + 1;

    assert(e != 0);

    for(int elem: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) {
        sum += findAmount(elem) + e;
    }

    return ((sum % 2) == 0);
}
