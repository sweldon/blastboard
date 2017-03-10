TEMPLATE = app
TARGET = blastboard

QT += core gui sql dbus widgets


CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

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

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include

macx: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/libgloox.a

macx: LIBS += -L$$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources/ -lJPEG

INCLUDEPATH += $$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources
DEPENDPATH += $$PWD/../../../System/Library/Frameworks/ImageIO.framework/Versions/A/Resources

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lgloox
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lgloox
else:unix:!macx: LIBS += -L$$PWD/../../../usr/local/lib/ -lgloox

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/libgloox.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/libgloox.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/gloox.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/gloox.lib
else:unix:!macx: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/libgloox.a
