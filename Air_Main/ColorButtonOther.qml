import QtQuick 2.0


Rectangle {

    id: root
    signal clicked

    property int numId
    property alias text: label.text
    property color textColor: "white"
    height: Math.round(40 * scaleFactor)
    width: Math.round(80 * scaleFactor)
    color: textColor
    radius: height/8

    Text {
        id: label
        anchors.centerIn: parent
        color: "white"
        font.family: "微软雅黑"
        font.pixelSize: 15
    }

}

