import QtQuick 2.0
import QtQuick.Window 2.2
import QtQml.Models 2.1

Window  {
    id: mainRect
    width: 1000
    height: 700
    visible: true
    property int listViewActive: 0
    property real scaleFactor: Screen.pixelDensity / 5.0
    property int intScaleFactor: Math.max(1, scaleFactor)


    Rectangle {
        id: banner
        height: 80
        anchors.top: parent.top
        width: parent.width
        //color: "#000000"
        visible: true



        Row {
            id: row
            spacing: 20
            anchors.centerIn: parent
            //anchors.bottom: parent.bottom
            ClickImage {
                id: mainWindow
                width: banner.height
                height: width
                source: "images/Home.png"
                numId: 0
            }
            ClickImage {
                id: subWindow
                width: banner.height
                height: width
                source: "images/CrashPlan.png"
                numId: 1
            }

            ClickImage {
                id: settingWindow
                width: banner.height
                height: width
                source: "images/Configure.png"
                numId: 2
            }

            ClickImage {
                id: chartWindow
                width: banner.height
                height: width
                source: "images/Chart - Google Docs.png"
                numId: 3
            }
            ClickImage {
                id: requestWindow
                width: banner.height
                height: width
                source: "images/Inkscape.png"
                numId: 4
            }
            ClickImage {
                id: diaryWindow
                width: banner.height
                height: width
                source: "images/History.png"
                numId: 5
            }
//            Text {
//                id: stocText
//                anchors.verticalCenter: textItem.verticalCenter
//                color: "red"
//                font.family: "微软雅黑"
//                font.pointSize: 40
//                text: "Niao"
//            }
        }

        Item {
            id: textItem
            width: stocText.width + qtText.width
            height: stocText.height + qtText.height
            anchors.horizontalCenter: banner.horizontalCenter
            anchors.verticalCenter: banner.verticalCenter

//            Image {
//                id: logo
//                width:80
//                height:80
//                source: "images/Pipi.png"
//                anchors.centerIn: parent
//            }

//            Text {
//                id: stocText
//                anchors.verticalCenter: textItem.verticalCenter
//                color: "red"
//                font.family: "微软雅黑"
//                font.pointSize: 40
//                text: "Niao"
//            }
        }
    }

    ListView {
        id: root
        x: 0
        width: parent.width
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        anchors.top: banner.bottom
        anchors.bottom: parent.bottom
        snapMode: ListView.SnapOneItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveDuration: 250
        focus: false
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        currentIndex: listViewActive
        onCurrentIndexChanged: {
            listViewActive = currentIndex;
            console.log(currentIndex)
        }
        model : ObjectModel{

            Window_Main {
                id: main
                width: root.width
                height: root.height
            }
            Window_SubState {
                id: substate
                width: root.width
                height: root.height
                //anchors.top: banner.bottom
                //anchors.bottom: parent.bottom
            }
            Window_Setting {
                id: setting
                width: root.width
                height: root.height
                anchors.top: banner.bottom
                anchors.bottom: parent.bottom
            }

            Window_Chart {
                id: chart
                width: root.width
                height: root.height
                //anchors.top: banner.bottom
                //anchors.bottom: parent.bottom
            }
            Window_RequestQue {
                id: requestQue
                width: root.width
                height: root.height
                //anchors.top: banner.bottom
                //anchors.bottom: parent.bottom
            }
            Window_Diary {
                id: diary
                width: root.width
                height: root.height
                //anchors.top: banner.bottom
                //anchors.bottom: parent.bottom
            }
        }
    }


}
