QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    connexionfen.cpp \
    database.cpp \
    main.cpp \
    chifoumivue.cpp \
    modele.cpp \
    parametrage.cpp \
    presentation.cpp

HEADERS += \
    chifoumivue.h \
    connexionfen.h \
    database.h \
    modele.h \
    parametrage.h \
    presentation.h

FORMS += \
    chifoumivue.ui \
    connexionfen.ui \
    parametrage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images/images.qrc

DISTFILES +=
