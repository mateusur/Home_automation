QT       += core gui
QT += mqtt
QT += multimedia
QT += multimediawidgets

win32:RC_ICONS += logo.ico

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
    author.cpp \
    chickencoop.cpp \
    droplet.cpp \
    main.cpp \
    choosewindow.cpp \
    settingsmqtt.cpp \
    settingsstream.cpp \
    settingsweather.cpp \
    watering.cpp \
    weather.cpp

HEADERS += \
    author.h \
    chickencoop.h \
    choosewindow.h \
    droplet.h \
    settingsmqtt.h \
    settingsstream.h \
    settingsweather.h \
    watering.h \
    weather.h

FORMS += \
    author.ui \
    chickencoop.ui \
    choosewindow.ui \
    settingsmqtt.ui \
    settingsstream.ui \
    settingsweather.ui \
    watering.ui \
    weather.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc \
    languages.qrc
