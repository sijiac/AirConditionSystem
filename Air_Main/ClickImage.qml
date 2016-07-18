import QtQuick 2.0

Image
{
    id: root
    signal clicked

    property int numId
    opacity: numId == listViewActive ? 1.5 : 0.2


    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: listViewActive = numId
    }

}
