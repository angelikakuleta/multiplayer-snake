QT -= gui
QT += network

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        gamemanager.cpp \
        main.cpp \
        messageparser.cpp \
        socketserver.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    gamemanager.h \
    messageparser.h \
    socketserver.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SnakeCommon/release/ -lSnakeCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SnakeCommon/debug/ -lSnakeCommon
else:unix: LIBS += -L$$OUT_PWD/../SnakeCommon/ -lSnakeCommon

INCLUDEPATH += $$PWD/../SnakeCommon
DEPENDPATH += $$PWD/../SnakeCommon
