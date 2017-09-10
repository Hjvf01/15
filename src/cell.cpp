#include "cell.h"


Cell::Cell(QQuickItem *parent) :
        QQuickPaintedItem(parent),
        m_number("2"),
        m_color(QColor(240, 240, 240))
{
    qDebug() << __PRETTY_FUNCTION__;
}


Cell::~Cell() {
    qDebug() << __PRETTY_FUNCTION__;
}


QRect Cell::cellRect() const {
    return QRect(x(), y(), width(), height());
}


void Cell::setNumber(const QString& num) { m_number = num; }
void Cell::setColor(const QColor& color) { m_color = color; }


QString Cell::getNumber() const { return m_number; }
QColor Cell::getColor() const { return m_color; }



void Cell::paint(QPainter *painter) {
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << m_number;

    int font_size = width() < height() ? width() : height();

    if(m_number != "0") {
        painter->setBrush(QBrush(m_color));
        painter->drawRect(QRect(x(),  y(), width(), height()));

        painter->setBrush(QBrush(Qt::black));
        QFont font = painter->font();
        font.setPixelSize(font_size - 20);
        painter->setFont(font);
        painter->drawText(
            QRect(x(), y(), width(), height()),
            Qt::AlignCenter,
            m_number
        );
    }
}
