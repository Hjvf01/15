QT += core
QT -= gui

CONFIG += c++11

TARGET = board_test
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=\
    main.cpp\
    ../../src/board.cpp\

HEADERS +=\
    ../../src/board.h
