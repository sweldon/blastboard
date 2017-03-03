TEMPLATE = app
TARGET = blastboard

QT += core gui sql dbus widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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

INCLUDEPATH += /usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lgloox
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lgloox
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -lgloox

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/libgloox.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/libgloox.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/release/gloox.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/debug/gloox.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/local/lib/libgloox.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lgloox.17
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lgloox.17
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -lgloox.17

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lgloox.17
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lgloox.17
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -lgloox.17

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/Cellar/gloox/1.0.14/lib/release/ -lgloox.13
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/Cellar/gloox/1.0.14/lib/debug/ -lgloox.13
else:unix: LIBS += -L$$PWD/../../../usr/local/Cellar/gloox/1.0.14/lib/ -lgloox.13

INCLUDEPATH += $$PWD/../../../usr/local/Cellar/gloox/1.0.14/include
DEPENDPATH += $$PWD/../../../usr/local/Cellar/gloox/1.0.14/include
