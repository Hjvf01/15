#ifndef BOARD_H
#define BOARD_H


#include <iostream>
using std::cout;
using std::endl;
#include <ostream>
using std::ostream;
#include <cassert>
#include <string>
using std::string;
using std::to_string;
#include <algorithm>
using std::shuffle;
using std::swap;
#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

#include <QtCore/QList>


class Board {
    QList<QList<int>> board = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15,  0}
    };

public:
    Board(const QList<QList<int>>& _board);
    Board();
    ~Board();

    const QList<int>& operator [] (const int index) const;
    QList<int>& operator [] (const int index);
    QList<QString> asStringList() const;

    QList<QList<int>> make();

    string str(void) const;

    int height(void) const { return board.size(); }
    int width(void) const { return board[0].size(); }

    int getRow(const int i) const { assert(i <= 15); return i / 4; }
    int getCol(const int i) const { assert(i <= 15); return i % 4; }

    void swap(int left_row, int left_col, int right_row, int right_col);

    friend ostream& operator << (ostream& os, const Board& board) {
        return os << board.str();
    }

    friend bool operator == (const Board& left, const Board& right) {
        assert(left.board.size() == right.board.size());
        for(int i = 0; i < left.board.size(); ++i)
            assert(left[i].size() == right[i].size());

        int height = left.board.size();
        for(int row = 0; row < height; ++row) {
            int width = right.board[row].size();
            for(int col = 0; col < width; ++col) {
                if(left[row][col] != right[row][col])
                    return false;
            }
        }

        return true;
    }

private:
    QList<QList<int>> _make(
        mt19937& gen, uniform_int_distribution<int>& distrub
    );
    bool solvable(const QList<QList<int>>& _board) const;

    int findRow(int num) const;
    int findCol(int num) const;
    int findAmount(int num) const;
};


#endif // BOARD_H
