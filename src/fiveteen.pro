TEMPLATE = app

QT += qml quick
CONFIG += c++14 qtquickcompiler

SOURCES +=\
    main.cpp\
    board.cpp\
    board_model.cpp \
    game_controller.cpp

HEADERS +=\
    board.h\
    board_model.h\
    game_controller.h

RESOURCES += qml.qrc


QML_IMPORT_PATH =


EVERYTHING = $$SOURCES $$HEADERS
message("The project contains the following files:")
message($$EVERYTHING)

include(deployment.pri)
