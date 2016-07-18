TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    controller.cpp \
    socketoperate.cpp \
    substate.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    controller.h \
    socketoperate.h \
    substate.h
