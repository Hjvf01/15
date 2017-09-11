TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES +=\
    main.cpp\
    test_model.cpp\
    cell.cpp\
    board.cpp\

HEADERS +=\
    test_model.h\
    cell.h\
    board.h\

RESOURCES += qml.qrc


QML_IMPORT_PATH =


include(deployment.pri)
