QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changepass.cpp \
    changeusr.cpp \
    displayer.cpp \
    functions.cpp \
    info.cpp \
    main.cpp \
    mainclasses.cpp \
    mainform.cpp \
    mainwindow.cpp \
    recommender.cpp \
    singupentry.cpp \
    userentry.cpp

HEADERS += \
    changepass.h \
    changeusr.h \
    displayer.h \
    functions.h \
    info.h \
    mainclasses.h \
    mainform.h \
    mainwindow.h \
    recommender.h \
    singupentry.h \
    userentry.h

FORMS += \
    changepass.ui \
    changeusr.ui \
    displayer.ui \
    info.ui \
    mainform.ui \
    mainwindow.ui \
    recommender.ui \
    singupentry.ui \
    userentry.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
