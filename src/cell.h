#ifndef CELL_H
#define CELL_H


#include <QRect>
#include <QDebug>
#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QQuickPaintedItem>


class Cell : public QQuickPaintedItem {
    Q_PROPERTY(
        QString number READ getNumber WRITE setNumber NOTIFY numberChanged
    )
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)

    QString m_number;
    QColor m_color;

public:
    Cell(QQuickItem* parent=nullptr);
    ~Cell() override;


    void setNumber(const QString& num);
    void setColor(const QColor& _color);

    QString getNumber(void) const;
    QColor getColor(void) const;

    bool isNull(void) const { return m_number == "0"; }

    QRect cellRect(void) const;

    void paint(QPainter *painter) override;
signals:
    void numberChanged(int n);
    void colorChanged(const QColor& col);
};


#endif // CELL_H
