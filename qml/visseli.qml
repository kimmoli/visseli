/*
    visseli, Visseli
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import visseli.Morse 1.0

ApplicationWindow
{
    id: visseli

    property string coverActionLeftIcon: "image://theme/icon-cover-pause"
    property string coverActionRightIcon: "image://theme/icon-cover-play"

    property string valueFromCover : "not set yet"

    initialPage: Qt.resolvedUrl("pages/Mainpage.qml")
    cover: Qt.resolvedUrl("cover/CoverPage.qml")

    function coverActionLeft()
    {
        console.log("Left cover action")
        valueFromCover = "Pause"
    }

    function coverActionRight()
    {
        console.log("Right cover action")
        valueFromCover = "Play"
    }

    Morse
    {
        id: morse
    }
}


