#include <algorithm>

#include "test_model.h"

TestModel::TestModel(QObject* parent) : QAbstractListModel(parent) {
    qDebug() << __PRETTY_FUNCTION__;
    for (int i = 1; i < 16; i++) {
        m_data.append(QString::number(i));
    }
    m_data.append("0");
}


int TestModel::rowCount(const QModelIndex &) const { return m_data.size(); }


QVariant TestModel::data(const QModelIndex &index, int role) const {
    if (! index.isValid()) {
        return QVariant();
    }

    switch (role) {
    case Roles::ColorRole:
        return QVariant(
            index.row() == 15 ? QColor(0, 0, 0, 0) : QColor(240, 240, 240)
        );
    case Roles::TextRole:
        return index.row() == 15 ? "" : m_data[index.row()];
    default:
        return QVariant();
    }
}


QHash<int, QByteArray> TestModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Roles::ColorRole] = "color";
    roles[Roles::TextRole] = "text";

    return roles;
}


void TestModel::moveLeft(const int index, const int index2) {
    qDebug() << __PRETTY_FUNCTION__;

    beginMoveRows(QModelIndex(), index, index, QModelIndex(), index2 + 1);
    m_data.swap(index, index2);
    qDebug() << m_data;
    endMoveRows();
}
