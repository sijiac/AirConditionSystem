TEMPLATE = app

QT += qml quick sql network core
QT += declarative
CONFIG += c++11

SOURCES += main.cpp \
    controller.cpp \
    logincontroller.cpp \
    mangermapper.cpp \
    substate.cpp \
    request.cpp \
    requestque.cpp \
    socktoperate.cpp \
    strategy.cpp \
    diarydb.cpp \
    tools.cpp \
    submodel.cpp \
    diarymodel.cpp \
    uicontroller.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    controller.h \
    database.h \
    logincontroller.h \
    mangermapper.h \
    substate.h \
    request.h \
    requestque.h \
    socktoperate.h \
    strategy.h \
    diarydb.h \
    tools.h \
    submodel.h \
    diarymodel.h \
    uicontroller.h
