/*
    visseli, Visseli
*/

import QtQuick 2.0
import Sailfish.Silica 1.0

Page
{
    id: page

    SilicaFlickable
    {
        anchors.fill: parent

        PullDownMenu
        {
            MenuItem
            {
                text: "About..."
                onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"),
                                          { "version": morse.version,
                                              "year": "2014",
                                              "name": "Visseli",
                                              "imagelocation": "/usr/share/icons/hicolor/86x86/apps/visseli.png"} )
            }
        }

        contentHeight: column.height

        Column
        {
            id: column

            width: page.width
            spacing: Theme.paddingLarge
            PageHeader
            {
                title: "Visseli"
            }

            Label
            {
                text: morse.vuValue
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Button
            {
                text: "Init"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: morse.init()
            }
            Button
            {
                text: "Start"
                enabled: morse.initialised
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: morse.rec()
            }
            Button
            {
                text: "Stop"
                enabled: morse.initialised
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: morse.stop()
            }
            Button
            {
                text: "Beep"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: morse.beep()
            }
        }
    }
}


