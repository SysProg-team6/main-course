QT       += core gui \
            sql \
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../WordsInWordGame/database.cpp \
    ../WordsInWordGame/game.cpp \
    ../WordsInWordGame/gameservices.cpp \
    ../WordsInWordGame/gamesrepository.cpp \
    ../WordsInWordGame/playedgame.cpp \
    ../WordsInWordGame/playedgamesrepository.cpp \
    ../WordsInWordGame/playedgamesservices.cpp \
    ../WordsInWordGame/player.cpp \
    ../WordsInWordGame/playerservices.cpp \
    ../WordsInWordGame/playersrepository.cpp \
    ../WordsInWordGame/repository.cpp \
    main.cpp \
    server.cpp \
    serverunit.cpp \
    serverworker.cpp

HEADERS += \
    ../WordsInWordGame/database.h \
    ../WordsInWordGame/game.h \
    ../WordsInWordGame/gameservices.h \
    ../WordsInWordGame/gamesrepository.h \
    ../WordsInWordGame/playedgame.h \
    ../WordsInWordGame/playedgamesrepository.h \
    ../WordsInWordGame/playedgamesservices.h \
    ../WordsInWordGame/player.h \
    ../WordsInWordGame/playerservices.h \
    ../WordsInWordGame/playersrepository.h \
    ../WordsInWordGame/repository.h \
    server.h \
    serverunit.h \
    serverworker.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
