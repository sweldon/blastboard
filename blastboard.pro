TEMPLATE = app
TARGET = blastboard

QT += core gui sql dbus widgets


CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG -= CONSOLE

QMAKE_CXXFLAGS += -std=c++11

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

macx: LIBS += -L$$PWD/../../../usr/local/lib/ -lgloox
macx: INCLUDEPATH += $$PWD/../../../usr/local/include
macx: DEPENDPATH += $$PWD/../../../usr/local/include
macx: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/libgloox.a
macx: LIBS += -L$$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources/ -lJPEG
macx: INCLUDEPATH += $$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources
macx: DEPENDPATH += $$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources
