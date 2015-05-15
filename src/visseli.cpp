/*
    visseli, Visseli
*/


#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QtQml>
#include <QScopedPointer>
#include <QQuickView>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <QCoreApplication>
#include "morse.h"


int main(int argc, char *argv[])
{
    qmlRegisterType<Morse>("visseli.Morse", 1, 0, "Morse");

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());
    view->setSource(SailfishApp::pathTo("qml/visseli.qml"));
    view->show();

    return app->exec();
}

