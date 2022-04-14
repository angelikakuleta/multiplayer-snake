QT += quick

SOURCES += \
        ViewModel/gameboardvm.cpp \
        clientmanager.cpp \
        gameboard.cpp \
        main.cpp \
        socketclient.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ViewModel/gameboardvm.h \
    clientmanager.h \
    gameboard.h \
    socketclient.h
