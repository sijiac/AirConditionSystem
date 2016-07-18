import QtQuick 2.0

Item {
    id: item2

    property string hhtext : "20"
    property string mmtext: "16"
    property string ddddtext: "星期三"
    property string mmmmtext: "六月"
    property string ddtext: "3"
    property string sstext: "24"
    property string numOfSubText:"0"
    property string ipAddressText: controller.getLocalIP()
    property string portNumText: "6665"

    //    Image {
    //        id: windmill
    //        width: 100
    //        height: 100
    //        anchors.right: parent.right
    //        anchors.bottom: parent.bottom
    //        anchors.leftMargin: 8
    //        anchors.bottomMargin: 8
    //        source: "images/windmill.png"
    //        RotationAnimation on rotation {
    //            to: 360
    //            duration: 4000
    //            loops: Animation.Infinite
    //        }
    //    }


    Item {
        id: item1
        anchors.horizontalCenter: parent.horizontalCenter
        Timer {
            interval: 1000; running: true; repeat: true
            //onTriggered: time.text = controller.getNowTime()
            //onTriggered: time.text = Qt.formatDateTime(new Date(), "hh:mm:ss\nyyyy-MM-dd\ndddd")
            /*
            property string hhtext : "20"
            property string mmtext: "16"
            property string ddddtext: "星期三"
            property string mmmmtext: "六月"
            property string ddtext: "3"*/
            // 星期 年份 月份 号 大月份
            onTriggered:{
                hhtext = controller.getH()
                mmtext = controller.getM()
                ddddtext = controller.getWeekNum()
                mmmmtext = controller.getMonth()
                ddtext = controller.getDay()
                sstext = controller.getSec()
                numOfSubText = controller.getNumOfSub()
            }
        }
        Text {
            id: hhmm
            font.family: "微软雅黑"
            font.pointSize: 60
            color: "black"
            text:hhtext + ":" + mmtext
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            id: ss
            y: 61
            anchors.bottom: hhmm.bottom
            anchors.left: hhmm.right
            font.family: "微软雅黑"
            font.pixelSize: 18
            color: "black"
            text: sstext
            anchors.bottomMargin: 19
            anchors.leftMargin: 11
        }
        Text {
            id: ddddMMdd
            anchors.top: hhmm.bottom
            font.family: "微软雅黑"
            font.pixelSize: 18
            color: "black"
            text:"星期"+ddddtext + ", " + mmmmtext +"月"+ " " + ddtext+"日"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Row {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.rightMargin:7
        spacing: 17
        Text {
            text: "链接数: " + numOfSubText
            font.family: "微软雅黑"
            font.pixelSize: 15
            color: "black"
        }
        Text {
            text: "IP: " + ipAddressText
            font.family: "微软雅黑"
            font.pixelSize: 15
            color: "black"
        }
        Text {
            text: "端口号：" + portNumText
            font.family: "微软雅黑"
            font.pixelSize: 15
            color: "black"
        }
    }
}
