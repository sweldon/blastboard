TEMPLATE = app
TARGET = blastboard

QT += core gui sql dbus widgets


CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

SOURCES += \
    main.cpp \
    login.cpp \
    dashboard.cpp \
    bot.cpp

HEADERS += \
    login.h \
    dashboard.h

RESOURCES     = resources.qrc

FORMS += \
    dashboard.ui

DISTFILES += \
    ../Desktop/backups/Screen Shot 2016-12-05 at 1.39.01 PM.png


macx: LIBS += -L$$PWD/../../../usr/local/lib/ -lgloox

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include

macx: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/libgloox.a

macx: LIBS += -L$$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources/ -lJPEG

INCLUDEPATH += $$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources
DEPENDPATH += $$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources
