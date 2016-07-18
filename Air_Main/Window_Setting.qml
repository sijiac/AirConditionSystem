import QtQuick 2.0

Item {
    id: item1

    property int modelId: 1 - controller.getMainState("mode")
    property int refreshId: 10 - 1 + controller.getMainState("refreshRate")
    property int duId: 100 - 1 + controller.getMainState("subInitalState")
    property int rateId: 1000 - 1 + controller.getMainState("timeRate")
    property int strategyId: 10000 - 1 + controller.getMainState("strategyNum")

    Column {
        width: 200
        height: 266
        anchors.verticalCenterOffset: 5
        anchors.horizontalCenterOffset: -140
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.top: parent.top
        anchors.topMargin: 112
        anchors.centerIn: parent.Center
        //anchors.top: Item.top
        spacing: 45
        Row {

            id: model
            spacing: 15

            Text {
                id: model_text
                anchors.bottom: model_icon.bottom
                font.family: "微软雅黑"
                font.pointSize: 18
                text: "模式选择"
            }

            Row {
                id: model_icon
                spacing: 0

                ColorButton {
                    id: cold
                    textColor: "cornflowerblue"
                    text: "冷"
                    numId: 0
                    onClicked: {modelId = numId ;controller.setMainState("mode",1)}

                }
                ColorButton {
                    id: warm
                    textColor: "tomato"
                    text: "热"
                    numId: 1
                    onClicked: {modelId = numId; controller.setMainState("mode",0)}
                }
            }
        }
        Row {

            id: refresh
            spacing: 15

            Text {
                id: refresh_text
                anchors.bottom: refresh_icon.bottom
                font.family: "微软雅黑"
                font.pointSize: 18
                text: "刷新频率"
            }

            Row {
                id: refresh_icon
                spacing: 0

                ColorButton {
                    id: a
                    textColor: "mediumaquamarine"
                    text: "1"
                    numId: 10
                    onClicked: {refreshId = numId; controller.setMainState("refreshRate",1)}

                }
                ColorButton {
                    id: b
                    textColor: "orange"
                    text: "5"
                    numId: 11
                    onClicked: {refreshId = numId; controller.setMainState("refreshRate",2)}
                }
                ColorButton {
                    id: c
                    textColor: "orangered"
                    text: "10"
                    numId: 12
                    onClicked: {refreshId = numId; controller.setMainState("refreshRate",3)}
                }

            }
        }
        Row {

            id: strategy
            spacing: 15

            Text {
                id: strategy_text
                anchors.bottom: refresh_icon.bottom
                font.family: "微软雅黑"
                font.pointSize: 18
                text: "策略选择"
            }

            Row {
                id: stragety_icon
                spacing: 0

                ColorButton {
                    id: strategy1
                    textColor: "mediumaquamarine"
                    text: "先来先服务"
                    width: Math.round(120 * scaleFactor)
                    numId: 10000
                    onClicked: {strategyId = numId; controller.setMainState("strategyNum",1)}

                }
                ColorButton {
                    id: strategy2
                    textColor: "orange"
                    text: "时间片轮转"
                    width: Math.round(120 * scaleFactor)
                    numId: 10001
                    onClicked: {strategyId = numId; controller.setMainState("strategyNum",2)}
                }
                ColorButton {
                    id: strategy3
                    textColor: "orangered"
                    text: "短作业优先"
                    width: Math.round(120 * scaleFactor)
                    numId: 10002
                    onClicked: {strategyId = numId; controller.setMainState("strategyNum",3)}
                }

            }
        }
//        Row {

//            id: du
//            spacing: 15

//            Text {
//                id: du_text
//                anchors.bottom: refresh_icon.bottom
//                font.family: "微软雅黑"
//                font.pointSize: 18
//                text: "初始温度"
//            }

//            Row {
//                id: du_icon
//                spacing: 0

//                ColorButton {
//                    id: i
//                    textColor: "blueviolet"
//                    text: "16"
//                    numId: 100
//                    onClicked: {duId = numId; controller.setMainState("subInitalState",1)}

//                }
//                ColorButton {
//                    id: ii
//                    textColor: "coral"
//                    text: "18"
//                    numId: 101
//                    onClicked: {duId = numId; controller.setMainState("subInitalState",2)}
//                }
//                ColorButton {
//                    id: iv
//                    textColor: "crimson"
//                    text: "20"
//                    numId: 102
//                    onClicked: {duId = numId; controller.setMainState("subInitalState",3)}
//                }
//                ColorButton {
//                    id: v
//                    textColor: "darkorange"
//                    text: "23"
//                    numId: 103
//                    onClicked: {duId = numId; controller.setMainState("subInitalState",4)}
//                }
//                ColorButton {
//                    id: vi
//                    textColor: "darkviolet"
//                    text: "26"
//                    numId: 104
//                    onClicked: {duId = numId; controller.setMainState("subInitalState",5)}
//                }

//            }
//        }
//        Row {

//            id: rate
//            spacing: 15

//            Text {
//                id: rate_text
//                anchors.bottom: refresh_icon.bottom
//                font.family: "微软雅黑"
//                font.pointSize: 18
//                text: "时间比例"
//            }

//            Row {
//                id: rate_icon
//                spacing: 0

//                ColorButton {
//                    id: rate1
//                    textColor: "dodgerblue"
//                    text: "1"
//                    numId: 1000
//                    onClicked: {rateId = numId; controller.setMainState("timeRate",1)}
//                    width: Math.round(65 * scaleFactor)
//                }
//                ColorButton {
//                    id: rate10
//                    textColor: "indigo"
//                    text: "10"
//                    numId: 1001
//                    onClicked: {rateId = numId; controller.setMainState("timeRate",2)}
//                    width: Math.round(65 * scaleFactor)
//                }
//                ColorButton {
//                    id: rate50
//                    textColor: "lightseagreen"
//                    text: "50"
//                    numId: 1002
//                    onClicked: {rateId = numId; controller.setMainState("timeRate",3)}
//                    width: Math.round(65 * scaleFactor)
//                }
//                ColorButton {
//                    id: rate100
//                    textColor: "lightslategrey"
//                    text: "100"
//                    numId: 1003
//                    onClicked: {rateId = numId; controller.setMainState("timeRate",4)}
//                    width: Math.round(65 * scaleFactor)
//                }
//                ColorButton {
//                    id: rate300
//                    textColor: "mediumpurple"
//                    text: "300"
//                    numId: 1004
//                    onClicked: {rateId = numId; controller.setMainState("timeRate",5)}
//                    width: Math.round(65 * scaleFactor)
//                }
//                ColorButton {
//                    id: rate500
//                    textColor: "orangered"
//                    text: "500"
//                    numId: 1005
//                    onClicked: {rateId = numId; controller.setMainState("timeRate",6)}
//                    width: Math.round(65 * scaleFactor)
//                }
//                ColorButton {
//                    id: rate1000
//                    textColor: "red"
//                    text: "1000"
//                    numId: 1006
//                    onClicked: {rateId = numId; controller.setMainState("timeRate",7)}
//                    width: Math.round(65 * scaleFactor)
//                }

//            }
//        }

    }
}
