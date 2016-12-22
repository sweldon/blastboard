TEMPLATE = app
TARGET = blastboard

QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    login.cpp \
    dashboard.cpp

HEADERS += \
    login.h \
    dashboard.h

RESOURCES     = resources.qrc

FORMS += \
    dashboard.ui

DISTFILES += \
    ../Desktop/backups/Screen Shot 2016-12-05 at 1.39.01 PM.png
