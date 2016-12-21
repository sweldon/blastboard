TEMPLATE = app
TARGET = blastboard

QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    login.cpp \
    home.cpp

HEADERS += \
    login.h \
    home.h

RESOURCES     = resources.qrc
