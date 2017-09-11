TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES +=\
    main.cpp\
    cell.cpp\
    board.cpp\
    board_model.cpp \
    game_controller.cpp

HEADERS +=\
    cell.h\
    board.h \
    board_model.h \
    game_controller.h

RESOURCES += qml.qrc


QML_IMPORT_PATH =


include(deployment.pri)
