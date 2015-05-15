#
# Project visseli, Visseli
#

TARGET = visseli

CONFIG += sailfishapp pkgconfig
PKGCONFIG += audioresource-qt
QT += multimedia

DEFINES += "APPVERSION=\\\"$${SPECVERSION}\\\""

message($${DEFINES})

SOURCES += src/visseli.cpp \
	src/morse.cpp \
    src/qmultimediaaudiorecorder.cpp \
    src/generator.cpp
	
HEADERS += src/morse.h \
    src/qmultimediaaudiorecorder.h \
    src/generator.h

OTHER_FILES += qml/visseli.qml \
    qml/cover/CoverPage.qml \
    qml/pages/Mainpage.qml \
    qml/pages/AboutPage.qml \
    rpm/visseli.spec \
	visseli.png \
    visseli.desktop

