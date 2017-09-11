#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

#include "board_model.h"
#include "game_controller.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<BoardModel>("Models", 1, 0, "BModel");
    qmlRegisterType<GameController>("Controllers", 1, 0, "GController");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    int res = app.exec();

    return res;
}
