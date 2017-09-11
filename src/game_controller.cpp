#include "game_controller.h"

GameController::GameController(QObject* parent) :
    QObject(parent),
    m_amount(0)
{}


void GameController::move(const int index) {
    assert(m_model != nullptr);

    if (m_model->isEmpty(index)) return;

    Direction direction = m_model->direction(index);

    switch (direction) {
    case Direction::Up:
        m_model->moveUp(index);
        break;
    case Direction::Left:
        m_model->moveLeft(index);
        break;
    case Direction::Down:
        m_model->moveDown(index);
        break;
    case Direction::Right:
        m_model->moveRight(index);
        break;
    default:
        break;
    }

    ++m_amount;
    emit amountChanged(QString::number(m_amount));

    if (m_model->isEnd())
        emit endGame(QString::number(m_amount));
}


BoardModel* GameController::newModel() {
    m_amount = 0;
    m_model = new BoardModel;
    return m_model;
}


void GameController::setModel(BoardModel *_model) {
    m_model = _model;
}

BoardModel* GameController::model() const { return m_model; }
