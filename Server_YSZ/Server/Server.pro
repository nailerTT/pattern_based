QT       += core gui
QT       += sql
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activityhandler.cpp \
    activityinfomanager.cpp \
    activitysubscribinfomanager.cpp \
    activitysystem.cpp \
    addvisitor.cpp \
    connectedsocket.cpp \
    consolemessageshow.cpp \
    coursehandler.cpp \
    courseinfomanager.cpp \
    coursesystem.cpp \
    databaseaccess.cpp \
    decorateddatabaseaccess.cpp \
    delvisitor.cpp \
    departmenthandler.cpp \
    departmentinfomanager.cpp \
    disconnectedsocket.cpp \
    getvisitor.cpp \
    handler.cpp \
    handlerfactory.cpp \
    iexecute.cpp \
    infomanager.cpp \
    letterhandler.cpp \
    letterinfomanager.cpp \
    lettersystem.cpp \
    main.cpp \
    mainwindow.cpp \
    messageprint.cpp \
    networklisener.cpp \
    nulldatabase.cpp \
    observer.cpp \
    receiveinfomanager.cpp \
    sendinfomanager.cpp \
    socket.cpp \
    sqldatabase.cpp \
    staffcourseinfomanager.cpp \
    staffhandler.cpp \
    staffinfomanager.cpp \
    subject.cpp \
    system.cpp \
    texteditprinter.cpp \
    updatevisitor.cpp \
    visitor.cpp

HEADERS += \
    activityhandler.h \
    activityinfomanager.h \
    activitysubscribinfomanager.h \
    activitysystem.h \
    addvisitor.h \
    connectedsocket.h \
    consolemessageshow.h \
    coursehandler.h \
    courseinfomanager.h \
    coursesystem.h \
    databaseaccess.h \
    decorateddatabaseaccess.h \
    delvisitor.h \
    departmenthandler.h \
    departmentinfomanager.h \
    disconnectedsocket.h \
    getvisitor.h \
    handler.h \
    handlerfactory.h \
    iexecute.h \
    infomanager.h \
    letterhandler.h \
    letterinfomanager.h \
    lettersystem.h \
    mainwindow.h \
    messageprint.h \
    networklisener.h \
    nulldatabase.h \
    observer.h \
    receiveinfomanager.h \
    sendinfomanager.h \
    socket.h \
    sqldatabase.h \
    staffcourseinfomanager.h \
    staffhandler.h \
    staffinfomanager.h \
    subject.h \
    system.h \
    texteditprinter.h \
    updatevisitor.h \
    visitor.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
