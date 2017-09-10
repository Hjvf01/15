#ifndef TESTMODEL_H
#define TESTMODEL_H


#include <QDebug>
#include <QAbstractListModel>
#include <QColor>


class TestModel : public QAbstractListModel {
    Q_OBJECT

    QList<QString> m_data;

public:
    enum Roles {
        ColorRole = Qt::UserRole + 1,
        TextRole
    };

public:
    TestModel(QObject* parent=nullptr);
    ~TestModel() = default;

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void moveLeft(const int, const int);
};

#endif // TESTMODEL_H
