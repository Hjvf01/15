#ifndef BOARD_H
#define BOARD_H

#include <algorithm>
using std::swap;
#include <cassert>

#include <QList>
#include <QtGlobal>
#include <QTime>

#define RANDOM(MIN, MAX) qrand() % (MAX) + (MIN)


static const int SIZE = 8;


QList<QList<int>> make_final(const int d);


class Board {
    QList<QList<int>> board;

public:
    Board(const QList<QList<int>>& _board);
    Board();
    ~Board() = default;

    const QList<int>& operator [] (const int index) const;
    QList<int>& operator [] (const int index);
    QList<QString> asStringList() const;

    QList<QList<int>> make() const;

    int height(void) const { return board.size(); }
    int width(void) const { return board[0].size(); }

    int getRow(const int i) const;
    int getCol(const int i) const;

    void swap(int left_row, int left_col, int right_row, int right_col);

    friend bool operator == (const Board& left, const Board& right) {
        assert(left.board.size() == right.board.size());
        for(int i = 0; i < left.board.size(); ++i)
            assert(left[i].size() == right[i].size());

        return left.board == right.board;
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
