#include <algorithm>

#include "board_model.h"

BoardModel::BoardModel(QObject* parent) :
    QAbstractListModel(parent),
    m_final(Board({
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15,  0},
    }))
{}


int BoardModel::rowCount(const QModelIndex &) const {
    return m_board.width() * m_board.height();
}


QVariant BoardModel::data(const QModelIndex &index, int role) const {
    if (! index.isValid()) { return QVariant(); }

    switch (role) {
    case Roles::ColorRole:
        if (isEmpty(index.row())) {
            return QVariant(QColor(0, 0, 0, 0));
        } else {
            return QVariant(QColor(245, 245, 240));
        }
    case Roles::TextRole:
        if (isEmpty(index.row())) {
            return QVariant(QString(""));
        } else {
            return QVariant(
                QString::number(
                    m_board
                        [m_board.getRow(index.row())]
                        [m_board.getCol(index.row())]
                )
            );
        }
    case Roles::TextColor:
        if (isEmpty(index.row())) {
            return QVariant(QColor(0, 0, 0, 0));
        } else {
            return QVariant(QColor(0, 0, 0));
        }
    default:
        return QVariant();
    }
}


QHash<int, QByteArray> BoardModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Roles::ColorRole] = "color";
    roles[Roles::TextRole] = "text";
    roles[Roles::TextColor] = "textColor";

    return roles;
}


Direction BoardModel::direction(const int index) const {
    int row = m_board.getRow(index);
    int col = m_board.getCol(index);

    Direction result = Direction::Stop;
        if (row != 0 && m_board[row - 1][col] == 0)
            result = Direction::Up;
        else if (col != m_board.width() - 1 && m_board[row][col + 1] == 0)
            result = Direction::Right;
        else if (row != m_board.height() - 1 && m_board[row + 1][col] == 0)
            return Direction::Down;
        else if (col != 0 && m_board[row][col - 1] == 0)
            result = Direction::Left;

    return result;
}


void BoardModel::moveUp(const int index) {
    beginMoveRows(empty, index, index, empty, index - 4);
    m_board.swap(
        m_board.getRow(index), m_board.getCol(index),
        m_board.getRow(index - 4), m_board.getCol(index - 4)
    );
    endMoveRows();

    beginMoveRows(empty, index - 3, index - 3, empty, index + 1);
    endMoveRows();
}


void BoardModel::moveRight(const int index) {
    beginMoveRows(empty, index, index, empty, index + 2);
    m_board.swap(
        m_board.getRow(index), m_board.getCol(index),
        m_board.getRow(index + 1), m_board.getCol(index + 1)
    );
    endMoveRows();
}


void BoardModel::moveDown(const int index) {
    beginMoveRows(empty, index, index, empty, index + 5);
    m_board.swap(
        m_board.getRow(index), m_board.getCol(index),
        m_board.getRow(index + 4), m_board.getCol(index + 4)
    );
    endMoveRows();

    beginMoveRows(empty, index + 3, index + 3, empty, index);
    endMoveRows();
}


void BoardModel::moveLeft(const int index) {
    beginMoveRows(empty, index, index, empty, index - 1);
    m_board.swap(
        m_board.getRow(index), m_board.getCol(index),
        m_board.getRow(index - 1), m_board.getCol(index - 1)
    );
    endMoveRows();
}
