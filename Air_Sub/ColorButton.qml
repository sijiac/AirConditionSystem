import QtQuick 2.0


Rectangle {

    id: root
    signal clicked

    property int numId
    property alias text: label.text
    property alias pp: mouseArea.pressed
    property color textColor: "white"
    height: Math.round(40 * scaleFactor)
    width: Math.round(80 * scaleFactor)
    radius: height/8

    Text {
        id: label
        anchors.centerIn: parent
        color: textColor
        font.family: "微软雅黑"
        font.pixelSize: 15
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: root.clicked()
    }

}

