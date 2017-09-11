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
    Q_INVOKABLE BoardModel* newModel();

    BoardModel* model() const;
    void setModel(BoardModel* _model);

signals:
    void amountChanged(const QString& a);
    void endGame(const QString& turns);
};

#endif // GAMECONTROLLER_H
