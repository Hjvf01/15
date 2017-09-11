#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QQuickItem>

#include "board_model.h"

class GameController : public QObject {
    Q_OBJECT

    Q_PROPERTY(BoardModel* model READ model WRITE setModel)

    BoardModel* m_model = nullptr;
    int m_amount;

public:
    explicit GameController(QObject* parent=nullptr);
    ~GameController() override = default;

    Q_INVOKABLE void move(const int index);

    int amount() const;
    BoardModel* model() const;

    Q_INVOKABLE BoardModel* newModel() {
        m_amount = 0;
        m_model = new BoardModel;
        return m_model;
    }

    void setModel(BoardModel* _model);
    void setAmount(int a);

signals:
    void amountChanged(const QString& a);

    void endGame(const QString& turns);
};

#endif // GAMECONTROLLER_H
