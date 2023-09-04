QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chess/bing.cpp \
    chess/cchessboard.cpp \
    chess/cchessman.cpp \
    chess/jiang.cpp \
    chess/ju.cpp \
    chess/ma.cpp \
    chess/none.cpp \
    chess/pao.cpp \
    chess/shi.cpp \
    chess/xiang.cpp \
    gameoverwidget.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    chess/bing.h \
    chess/cchessboard.h \
    chess/cchessman.h \
    chess/jiang.h \
    chess/ju.h \
    chess/ma.h \
    chess/none.h \
    chess/pao.h \
    chess/shi.h \
    chess/xiang.h \
    gameoverwidget.h \
    setting.h \
    widget.h

FORMS += \
    gameoverwidget.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
