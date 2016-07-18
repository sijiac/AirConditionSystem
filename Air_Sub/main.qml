import QtQuick 2.4
import QtQuick.Window 2.2

Window {
    id: root
    width: 1000
    height: 700
    visible: true

    property real scaleFactor: Screen.pixelDensity / 5.0
    property int intScaleFactor: Math.max(1, scaleFactor)
    property string refreshValue: "1"
    property string hostIp: controller.getMainIp()
    property string subPortNumber: controller.getPortNum()
    property string subIp: controller.getLocalIp()
    property string roomId: controller.getRoomId()
    property int warm : 0
    property int windlevel: controller.getWindRate()
    property string timeCurrent: controller.getCurTime()
    property string innerTempText: controller.getInnerTemp()
    property string totalMoneyText: controller.getTotalMoney()
    property string targetTempText: controller.getObjectTemp()
    property string modeText: controller.getMode()
    property string localIpText: controller.getLocalIp()
    property string mainIpText: controller.getMainIp()
    property string portNumText: controller.getPortNum()
    property string numOfSubText: "23"
    property string totalvoltage: controller.getToatalVoltage()

    //本机Ip，主机Ip，端口号
    //当前温度，目标温度，模式
    //当前风速，钱数，电费
    Timer{
        interval: 1000; running: true; repeat: true
        onTriggered: {
            hostIp = controller.getMainIp()
            subPortNumber = controller.getPortNum()
            subIp = controller.getLocalIp()
            roomId = controller.getRoomId()
            windlevel = controller.getWindRate()
            timeCurrent = controller.getCurTime()
            innerTempText = controller.getInnerTemp()
            totalMoneyText = controller.getTotalMoney()
            targetTempText = controller.getObjectTemp()
            modeText = controller.getMode()
            localIpText = controller.getLocalIp()
            mainIpText = controller.getMainIp()
            portNumText = controller.getPortNum()
            totalvoltage = controller.getToatalVoltage()
        }
    }

    Rectangle {

        id: header
        x: 0
        height: 120
        anchors.top: parent.top
        width: parent.width
        color: "#6495ED"
        anchors.topMargin: 0
        visible: true

        Text {
            id: headText
            color: "white"
            font.family: "微软雅黑"
            font.pointSize: 40
            text: "Niao Air"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    Item {
        id: aimTemAndcurTem
        x: 409
        y: 126
        width: 112
        height: 24
        anchors.horizontalCenterOffset: -33
        anchors.horizontalCenter: parent.horizontalCenter
        Row {
            x: -20
            y: 0
            spacing: 35
            Text {
                id: curTem
                font.family: "微软雅黑"
                font.pointSize: 60
                color: "cornflowerblue"
                text:innerTempText
            }
            Text {
                id: aimTem
                font.family: "微软雅黑"
                font.pointSize: 60
                color: "tomato"
                text:targetTempText
            }
        }
        Row {
            x: -13
            y: 97
            anchors.bottom: parent.top
            anchors.bottomMargin: -121
            spacing: 5
            Text {
                id: cur
                font.family: "微软雅黑"
                font.pixelSize: 18
                color: "cornflowerblue"
                text:"当前温度(℃)"

            }
            Text {
                id: aim
                font.family: "微软雅黑"
                font.pixelSize: 18
                color: "tomato"
                text:"目标温度(℃)"
            }

        }
    }
    Grid {
        id: infolayout;
        width: parent.width;
        anchors.left: parent.left
        anchors.top: aimTemAndcurTem.bottom
        anchors.topMargin: parent.width/9
        anchors.leftMargin: parent.width/5
        columns: 3
        spacing: 100
        Text {
            text: "总用电量(度)：" + totalvoltage
            font.family: "微软雅黑"
            font.pixelSize: 20
        }
        Text {
            font.family: "微软雅黑"
            font.pixelSize: 20
        }
        Text {
            text: "总花费(元)：" + totalMoneyText
            font.family: "微软雅黑"
            font.pixelSize: 20
        }
        Text {
            text: "模式：" + modeText
            font.family: "微软雅黑"
            font.pixelSize: 20
        }
        Text {
            text: "本机IP：" + localIpText
            font.family: "微软雅黑"
            font.pixelSize: 20
        }

        Text {
            text:"主机IP：" + mainIpText
            font.family: "微软雅黑"
            font.pixelSize: 20
        }
        Text {
            text: "端口号：" + portNumText
            font.family: "微软雅黑"
            font.pixelSize: 20
        }
    }
    Row {
        id: windrate
        anchors.left: parent.left
        anchors.top: infolayout.bottom
        anchors.topMargin: parent.width/9
        anchors.leftMargin: parent.width/5
        spacing: 15
        Text {
            id: windrate_text
            //anchors.bottom: windrate_icon.bottom
            font.family: "微软雅黑"
            font.pixelSize: 20
            text: "风速: "
        }
        Row {
            id: windrate_icon
            spacing: 0
            ColorButton {
                id: one_icon
                color: numId == windlevel? "cornflowerblue":"white"
                text: "低"
                numId: 1
                textColor: numId == windlevel? "white":"black"
                onClicked: {
                    windlevel = numId
                    controller.setWindRate(numId);
                }
            }
            ColorButton {
                id: two_icon
                color:  numId == windlevel? "tomato":"white"
                text: "中"
                numId: 2
                textColor: numId == windlevel? "white":"black"
                onClicked: {
                    windlevel = numId
                    controller.setWindRate(numId);
                }
            }
            ColorButton {
                id: three_icon
                color:  numId == windlevel? "red":"white"
                text: "高"
                numId: 3
                textColor: numId == windlevel? "white":"black"
                onClicked: {
                    windlevel = numId
                    controller.setWindRate(numId);
                }
            }
        }
    }

    Row {
        id: aimTem_icon
        spacing: 0
        anchors.left: parent.left
        anchors.top: infolayout.bottom
        anchors.topMargin: parent.width/9
        anchors.leftMargin: parent.width/1.5
        ColorButton{
            id: plus_icon
            color: pp? "red":"tomato"
            textColor: "white"
            text: "升温"
            height: Math.round(80 * scaleFactor)
            width: Math.round(100 * scaleFactor)
            radius: 5
            onClicked:{
                controller.addTargetTemp()
                targetTempText = controller.getObjectTemp()
            }
        }
        ColorButton{
            id: minus_icon
            color: pp? "blueviolet":"cornflowerblue"
            textColor: "white"
            text: "降温"
            height: Math.round(80 * scaleFactor)
            width: Math.round(100 * scaleFactor)
            radius: 5
            onClicked: {
                controller.reduceTargetTemp()
                targetTempText = controller.getObjectTemp()
            }
        }
    }

    Row {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        anchors.rightMargin:7
        spacing: 17
        Text {
            text: "房间号: " + roomId
            font.family: "微软雅黑"
            font.pixelSize: 15
            color: "black"
        }
        Text {
            text: timeCurrent
            font.family: "微软雅黑"
            font.pixelSize: 15
            color: "black"
        }
    }
}
