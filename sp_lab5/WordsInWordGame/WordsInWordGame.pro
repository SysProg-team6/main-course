QT       += core gui \
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    formaddgame.cpp \
    formhistory.cpp \
    formmenu.cpp \
    formnewgame.cpp \
    formprofile.cpp \
    game.cpp \
    gameservices.cpp \
    gamesrepository.cpp \
    main.cpp \
    mainwindow.cpp \
    playedgame.cpp \
    playedgamesrepository.cpp \
    playedgamesservices.cpp \
    player.cpp \
    playerservices.cpp \
    playersrepository.cpp \
    repository.cpp

HEADERS += \
    database.h \
    formaddgame.h \
    formhistory.h \
    formmenu.h \
    formnewgame.h \
    formprofile.h \
    game.h \
    gameservices.h \
    gamesrepository.h \
    mainwindow.h \
    playedgame.h \
    playedgamesrepository.h \
    playedgamesservices.h \
    player.h \
    playerservices.h \
    playersrepository.h \
    repository.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
