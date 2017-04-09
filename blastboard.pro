# POSTGRES: from bin to QT\5.8\ming43_32\bin: libpq.dll, ssleay32.dll, libeay32.dll
# Ensure database libraries are same as compiler (32/64 bit, ming32 for windows)

TEMPLATE = app
TARGET = blastboard

QT += core gui sql dbus widgets

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
CONFIG -= CONSOLE

QMAKE_CXXFLAGS += -std=c++11
QT_DEBUG_PLUGINS=1

SOURCES += \
    main.cpp \
    dashboard.cpp \
    chatboxhandler.cpp \
    toolbar.cpp \
    loginui.cpp

HEADERS += \
    dashboard.h \
    chatboxhandler.h \
    toolbar.h \
    loginui.h

RESOURCES     = resources.qrc

FORMS += \
    dashboard.ui \
    loginui.ui

DISTFILES += \
    ../Desktop/backups/Screen Shot 2016-12-05 at 1.39.01 PM.png

macx: LIBS += -L$$PWD/../../../usr/local/lib/ -lgloox
macx: INCLUDEPATH += $$PWD/../../../usr/local/include
macx: DEPENDPATH += $$PWD/../../../usr/local/include
macx: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/libgloox.a
macx: LIBS += -L$$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources/ -lJPEG
macx: INCLUDEPATH += $$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources
macx: DEPENDPATH += $$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources

win32: LIBS += -L$$PWD/../../Downloads/gloox/src/.libs/ -lgloox

win32:INCLUDEPATH += $$PWD/../../Downloads/gloox/src/.libs
win32:DEPENDPATH += $$PWD/../../Downloads/gloox/src/.libs

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../Downloads/gloox/src/.libs/gloox.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../../Downloads/gloox/src/.libs/libgloox.a

win32:INCLUDEPATH += $$PWD/'../../../../Program Files (x86)/PostgreSQL/9.6/include'
win32:DEPENDPATH += $$PWD/'../../../../Program Files (x86)/PostgreSQL/9.6/include'
