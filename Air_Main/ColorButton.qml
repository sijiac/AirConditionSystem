import QtQuick 2.0


Rectangle {

    id: root
    signal clicked

    property int numId
    property alias text: label.text
    property color textColor: "white"
    height: Math.round(40 * scaleFactor)
    width: Math.round(80 * scaleFactor)
    color: (numId == modelId) || (numId == refreshId) || (numId == duId) || (numId == rateId) || (numId == strategyId) ? textColor : "white"
    radius: height/8

    Text {
        id: label
        anchors.centerIn: parent
        color: (numId == modelId) || (numId == refreshId) || (numId == duId) || (numId == rateId) || (numId == strategyId) ? "white" : "black"
        font.family: "微软雅黑"
        font.pixelSize: 15
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: root.clicked()
    }

}

