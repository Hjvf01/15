#ifndef BOARD_H
#define BOARD_H

#include <algorithm>
using std::swap;
#include <cassert>

#include <QList>
#include <QtGlobal>
#include <QTime>

#define RANDOM(MIN, MAX) qrand() % (MAX) + (MIN)


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

    QList<QList<int>> make() const;

    int height(void) const { return board.size(); }
    int width(void) const { return board[0].size(); }

    int getRow(const int i) const { assert(i <= 15); return i / 4; }
    int getCol(const int i) const { assert(i <= 15); return i % 4; }

    void swap(int left_row, int left_col, int right_row, int right_col);

    friend bool operator == (const Board& left, const Board& right) {
        assert(left.board.size() == right.board.size());
        for(int i = 0; i < left.board.size(); ++i)
            assert(left[i].size() == right[i].size());

        int height = left.board.size();
        for(int row = 0; row < height; ++row) {
            int width = right.board[row].size();
            for(int col = 0; col < width; ++col) {
                if (left[row][col] != right[row][col]) {
                    return false;
                }
            }
        }

        return true;
    }

private:
    QList<QList<int>> _make() const;
    void shuffle(QList<QList<int>>& _board) const;
    bool solvable(const QList<QList<int>>& _board) const;

    int findRow(const QList<QList<int>>& _board, int num) const;
    int findCol(const QList<QList<int>>& _board, int num) const;
    int findAmount(const QList<QList<int>>& _board, int num) const;
};


#endif // BOARD_H
