import QtQuick 2.0
import "."
import "QChart.js"        as Charts
import "QChartGallery.js" as ChartsData


Item {
    id: root
    property int chart_width: chartANDinfo.width;
    property int chart_height: 400;
    property int chart_spacing: chartANDinfo.width/20;
    property int text_height: 80;
    property int row_height: 8;
    property string ipText: ""
    property string portNumText: ""
    property string innerTemText: ""
    property string temText: ""
    property string totalMoneyText: ""
    property string windRateText: ""
    property string workStateText: ""
    property string totalVoltage: ""
    property string openNumText:""

    Rectangle {
        id: subInfo
        height: parent.height
        width: parent.width/6
        anchors.left: parent.left

        border.color: "black"
        //border.width: 5
        radius: height/30

        ListView {
            id: view
            anchors.fill: parent
            anchors.topMargin: 2
            anchors.bottomMargin: 2
            anchors.rightMargin: 2
            anchors.leftMargin: 2
            width: parent.width
            clip: true
            keyNavigationWraps: true
            highlightMoveDuration: 0
            focus: true
            snapMode: ListView.SnapToItem
            model:subModel
                /* ListModel {
                id: myModel
                ListElement { roomId: "1"}
                ListElement { roomId: "2"}
                ListElement { roomId: "3"}
                ListElement { roomId: "4"}
                ListElement { roomId: "5"}
            }*/

//            currentIndex:1

//            Timer {
//                interval: 1000; running: true; repeat: true
//                onTriggered:{
//                    ipText = controller.getSubState(view.currentIndex,1)
//                    portNumText = controller.getSubState(view.currentIndex,2)
//                    innerTemText = controller.getSubState(view.currentIndex,3)
//                    temText = controller.getSubState(view.currentIndex,4)
//                    totalMoneyText = controller.getSubState(view.currentIndex,5)
//                    windRateText = controller.getSubState(view.currentIndex,6)
//                    workStateText = controller.getSubState(view.currentIndex,7)
//                    totalVoltage = controller.getSubState(view.currentIndex, 8)
//                    openNumText = controller.getSubState(view.currentIndex, 9)
//                }
//            }
            delegate: Rectangle {
                height: 50
                width: parent.width
                color: "transparent"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        view.currentIndex = index;
                        ipText = controller.getSubState(view.currentIndex,1)
                        portNumText = controller.getSubState(view.currentIndex,2)
                        innerTemText = controller.getSubState(view.currentIndex,3)
                        temText = controller.getSubState(view.currentIndex,4)
                        totalMoneyText = controller.getSubState(view.currentIndex,5)
                        windRateText = controller.getSubState(view.currentIndex,6)
                        workStateText = controller.getSubState(view.currentIndex,7)
                        totalVoltage = controller.getSubState(view.currentIndex, 8)
                        openNumText = controller.getSubState(view.currentIndex,9)

                        //console.log("index NUM *********************:"+view.currentIndex);
                    }
                }
                Text {
                    id: idText
                    color: "black"
                    font.family: "微软雅黑"
                    font.pixelSize: 20
                    font.weight: Font.Bold
                    text: modelData.roomId
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
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
                //border.color: "black"
                radius: subInfo.radius
            }
        }
    }
    Rectangle {
        id: chartANDinfo
        width: parent.width - subInfo.width
        height:subInfo.height
        anchors.right: parent.right

//        Rectangle {
//            Rectangle { color: "#282b36"; width: parent.width/1.0; height: row_height; anchors.right: parent.right;}
//            Rectangle { color: "#f33e6f"; width: parent.width/3.0; height: row_height; anchors.right: parent.right; anchors.rightMargin:50}
//            Rectangle { color: "#46bfbd"; width: parent.width/3.0; height: row_height; x: 1*width; y: height; }
//            Rectangle { color: "#fbd45c"; width: parent.width/3.0; height: row_height; x: 2*width; y: height; }
//        }
        Rectangle {
            id: button;
            width: 100;
            height: 32;
            color: "#2d91ea";
            radius: 8;
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.topMargin: 10
            Text {
                anchors.centerIn: parent;
                color: "#ffffff";
                text: "Repaint";
                font.bold: true;
            }

            MouseArea {
                anchors.fill: parent;
                onPressed: {
                    button.color = "#1785e6"
                }
                onReleased: {
                    button.color = "#2d91ea"
                    //chart_line.repaint();

                    if (controller.getNumOfSub() === 0) return;

                    var ChartLineData20 = {
                          labels: [controller.getTemTime(view.currentIndex,0),
                            controller.getTemTime(view.currentIndex,1),
                            controller.getTemTime(view.currentIndex,2),
                            controller.getTemTime(view.currentIndex,3),
                            controller.getTemTime(view.currentIndex,4),
                            controller.getTemTime(view.currentIndex,5),
                            controller.getTemTime(view.currentIndex,6),
                            controller.getTemTime(view.currentIndex,7),
                            controller.getTemTime(view.currentIndex,8),
                            controller.getTemTime(view.currentIndex,9)/*,
                            controller.getTemTime(view.index,10),
                            controller.getTemTime(view.index,11),
                            controller.getTemTime(view.index,12),
                            controller.getTemTime(view.index,13),
                            controller.getTemTime(view.index,14),
                            controller.getTemTime(view.index,15),
                            controller.getTemTime(view.index,16),
                            controller.getTemTime(view.index,17),
                            controller.getTemTime(view.index,18),
                            controller.getTemTime(view.index,19)*/],
                        datasets: [ {
                                   fillColor: "rgba(151,187,205,0.5)",
                                 strokeColor: "rgba(151,187,205,1)",
                                  pointColor: "rgba(151,187,205,1)",
                            pointStrokeColor: "#ffffff",
                                        data: [ controller.getTemTem(view.currentIndex,0),
                                    controller.getTemTem(view.currentIndex,1),
                                    controller.getTemTem(view.currentIndex,2),
                                    controller.getTemTem(view.currentIndex,3),
                                    controller.getTemTem(view.currentIndex,4),
                                    controller.getTemTem(view.currentIndex,5),
                                    controller.getTemTem(view.currentIndex,6),
                                    controller.getTemTem(view.currentIndex,7),
                                    controller.getTemTem(view.currentIndex,8),
                                    controller.getTemTem(view.currentIndex,9)/*,
                                    controller.getTemTem(view.index,10),
                                    controller.getTemTem(view.index,11),
                                    controller.getTemTem(view.index,12),
                                    controller.getTemTem(view.index,13),
                                    controller.getTemTem(view.index,14),
                                    controller.getTemTem(view.index,15),
                                    controller.getTemTem(view.index,16),
                                    controller.getTemTem(view.index,17),
                                    controller.getTemTem(view.index,18),
                                    controller.getTemTem(view.index,19)*/
                                    ]
                        }]
                    }

                    chart_line.chartData = ChartLineData20
                    chart_line.repaint();
                    chart_line.requestPaint();
                }
            }
        }
        //Chart 数据由QChartGallery.js提供
        QChart {
          id: chart_line;
          width: chart_width;
          height: chart_height;
          anchors.right: parent.right
          anchors.top: button.bottom
          anchors.topMargin: 10
          chartAnimated: true;
          chartAnimationEasing: Easing.InOutElastic;
          chartAnimationDuration: 2000;
          chartData: ChartsData.ChartLineData;
          chartType: Charts.ChartType.LINE;
        }

        Grid {
          id: infolayout;
          width: parent.width;
          anchors.left: chart_line.left
          anchors.top: chart_line.bottom
          anchors.topMargin: chart_width/20
          anchors.leftMargin: chart_width/7
          columns: 4
          spacing: chart_spacing;
          Text {
            text: "总用电量(度)：" + totalVoltage
            font.family: "微软雅黑"
            font.pixelSize: 20
          }
          Text {
            text: "当前室温(℃)：" + innerTemText
            font.family: "微软雅黑"
            font.pixelSize: 20
          }
          Text {
            text: "端口号：" + portNumText
            font.family: "微软雅黑"
            font.pixelSize: 20
          }
          Text {
            text: "开关机次数：" + openNumText
            font.family: "微软雅黑"
            font.pixelSize: 20
          }

          Text {
            text: "目标温度(℃)/风速：" + temText + "/" + windRateText
            font.family: "微软雅黑"
            font.pixelSize: 20
          }

          Text {
            text: "ip地址：" + ipText
            font.family: "微软雅黑"
            font.pixelSize: 20
          }
          Text {
            text: "总花费(元)：" + totalMoneyText
            font.family: "微软雅黑"
            font.pixelSize: 20
          }

          Text {
            text: "当前状态：" + workStateText
            font.family: "微软雅黑"
            font.pixelSize: 20
          }
        }
    }
}
