#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "test_model.h"
#include "cell.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<TestModel>("MyModels", 1, 0, "TestModel");
    qmlRegisterType<Cell>("Cells", 1, 0, "Cell");

    QQuickView view;
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    return app.exec();
}
