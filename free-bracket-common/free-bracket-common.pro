#-------------------------------------------------
#
# Project created by QtCreator 2014-09-15T15:16:40
#
#-------------------------------------------------

CONFIG += c++11

QT       += qml

QT       -= gui

TARGET = free-bracket-common
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    Bracket.cpp \
    BracketMatch.cpp \
    BracketRound.cpp \
    FreeBracketCommands.cpp \
    Team.cpp

HEADERS += \
    Bracket.h \
    BracketMatch.h \
    BracketRound.h \
    FreeBracketCommands.h \
    Team.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
