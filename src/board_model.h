#ifndef TESTMODEL_H
#define TESTMODEL_H


#include <QDebug>
#include <QAbstractListModel>
#include <QColor>

#include "board.h"


enum class Direction {
    Stop = 0,
    Up = 1,
    Left = 2,
    Down = 3,
    Right = 4
};


class BoardModel : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor)

    Board m_final;
    Board m_board;
    QModelIndex empty;

    QColor m_color;
    QColor m_textColor;

public:
    enum Roles {
        ColorRole = Qt::UserRole + 1,
        TextColor,
        TextRole
    };

public:
    BoardModel(QObject* parent=nullptr);
    BoardModel(const Board& board);
    ~BoardModel() = default;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    bool isEmpty(const int i) const {
        return m_board[m_board.getRow(i)][m_board.getCol(i)] == 0;
    }

    bool isEnd() const { return m_board == m_final; }

    QColor color() const;
    QColor textColor() const;
    Board board() const { return m_board; }

    void setColor(const QColor& color);
    void setTextColor(const QColor& color);

    Direction direction(const int index) const;

    void moveUp(const int index);
    void moveLeft(const int index);
    void moveDown(const int index);
    void moveRight(const int index);
};

#endif // TESTMODEL_H
