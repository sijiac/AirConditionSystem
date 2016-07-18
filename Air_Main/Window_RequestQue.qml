
import QtQuick 2.0

Rectangle {
    id: root
    width: 320
    height: 410
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    color: "white"

    property string currentStockId: ""
    property string currentStockName: ""

    ListView {

        id: view
        anchors.fill: parent
        width: parent.width
        clip: true
        keyNavigationWraps: true
        highlightMoveDuration: 0
        focus: true
        snapMode: ListView.SnapToItem
        model:requestModel
//            ListModel {
//            id: myModel
//            ListElement { RoomID: "1"; User: "响应中"; Time: "2016/6/5 23:00"; Content:"useername:123登陆成功"}
//            ListElement { RoomID: "设置"; User: ""; Time: "2016/6/5 23:10"; Content:"模式设置为制冷模式"}
//            ListElement { RoomID: "处理从控机请求"; User: "响应中"; Time: "2016/6/5 23:20"; Content:"模式设置为制冷模式"}
//        }
        delegate: Rectangle {
            height: 102
            width: parent.width
            color: "transparent"
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    view.currentIndex = index;
                }
            }
            Text {
                id: operationTypeText
                anchors.top: parent.top
                anchors.topMargin: parent.height/7
                anchors.leftMargin: parent.height/7
                anchors.left: parent.left
                width: 125
                height: 40
                color: "#000000"
                font.family: "微软雅黑"
                font.pointSize: 20
                font.weight: Font.Bold
                verticalAlignment: Text.AlignVCenter
                text:"RoomID: " + Type
            }
            Text {
                id: stockValueText
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.right: parent.right
                anchors.rightMargin: 0.31 * parent.width
                width: 190
                height: 40
                color: "#000000"
                font.family: "微软雅黑"
                font.pointSize: 20
                font.bold: true
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: Time
                Component.onCompleted: view.getCloseValue(index);
            }
            Text {
                id: contentText
                anchors.bottomMargin: parent.height/7
                anchors.leftMargin: parent.height/7
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                //width: 330
                height: 30
                color: "#000000"
                font.family: "微软雅黑"
                font.pointSize: 16
                font.bold: false
                elide: Text.ElideRight
                maximumLineCount: 1
                verticalAlignment: Text.AlignVCenter
                text: Content
            }
            Text {
                id: userText
                anchors.top: operationTypeText.bottom
                anchors.right: parent.right
                anchors.rightMargin: 20
                width: 120
                height: 30
                color: "red"
                font.family: "微软雅黑"
                font.pointSize: 18
                font.bold: false
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: User
            }

            Rectangle {
                id: endingLine
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                height: 1
                width: parent.width
                color: "#d7d7d7"
            }
        }

        highlight: Rectangle {
            width: parent.width
            color: "#eeeeee"
        }
    }
}
