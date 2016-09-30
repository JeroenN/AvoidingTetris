TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBS += -LC:/SFML/lib -LC:/SFML/bin

INCLUDEPATH += C:/SFML/include
DEPENDPATH += C:/SFML/include
