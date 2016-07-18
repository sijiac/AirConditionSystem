import QtQuick 2.0
import "."
import "QChart.js"        as Charts
import "QChartGallery.js" as ChartsData


Rectangle {
    id: chart
    property int chart_spacing: chart.width/20
    property int text_height: 80
    property int row_height: 8
    property int typeID: 0

    Column{
        id: ll
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20
        Column {
            id: monthAnday
            anchors.right: parent.right
            anchors.rightMargin: 100
            spacing: 5
            ColorButtonOther {
                id: month
                textColor: "gainsboro"
                text: "日（元）"
                numId: 0

            }
            ColorButtonOther {
                id: day
                textColor: "cornflowerblue"
                text: "月（元）"
                numId: 1
            }
        }

        Rectangle {
            id: button;
            width: 100;
            height: 32;
            color: "salmon";
            radius: 8;
            anchors.left: monthAnday.left
            Text {
                anchors.centerIn: parent;
                color: "#ffffff";
                text: "Repaint";
                font.family: "微软雅黑"
                font.bold: true;
            }

            MouseArea {
                anchors.fill: parent;
                onPressed: {
                    button.color = "tomato"
                }
                onReleased: {
                    button.color = "#2d91ea"
                    //chart_line.repaint();

                    var ChartBarData5 = {
                        labels: [controller.chart_getRoomID(0),
                                controller.chart_getRoomID(1),
                                controller.chart_getRoomID(2),
                                controller.chart_getRoomID(3),
                                controller.chart_getRoomID(4)],
                      datasets: [{
                            fillColor: "rgba(220,220,220,0.5)",
                          strokeColor: "rgba(220,220,220,1)",
                                 data: [controller.chart_getMoney_day(0, controller.getMonth(), controller.getDay()),
                                        controller.chart_getMoney_day(1, controller.getMonth(), controller.getDay()),
                                        controller.chart_getMoney_day(2, controller.getMonth(), controller.getDay()),
                                        controller.chart_getMoney_day(3, controller.getMonth(), controller.getDay()),
                                        controller.chart_getMoney_day(4, controller.getMonth(), controller.getDay())]
                      }, {
                            fillColor: "rgba(151,187,205,0.5)",
                          strokeColor: "rgba(151,187,205,1)",
                                data: [controller.chart_getMoney_month(0, controller.getMonth()),
                                       controller.chart_getMoney_month(1, controller.getMonth()),
                                       controller.chart_getMoney_month(2, controller.getMonth()),
                                       controller.chart_getMoney_month(3, controller.getMonth()),
                                       controller.chart_getMoney_month(4, controller.getMonth())]
                      }]
//                        labels: [controller.chart_getRoomID(0),"February","March","April","May","June","July"],
//                      datasets: [{
//                            fillColor: "rgba(220,220,220,0.5)",
//                          strokeColor: "rgba(220,220,220,1)",
//                                 data: [controller.chart_getMoney_day(0, controller.getMonth(), controller.getDay()),59,90,81,56,55,40]
//                      }, {
//                            fillColor: "rgba(151,187,205,0.5)",
//                          strokeColor: "rgba(151,187,205,1)",
//                                 data: [controller.chart_getMoney_month(0, controller.getMonth()),48,40,19,96,27,100]
//                      }]
                  }

                    chart_bar.chartData = ChartBarData5
                    chart_bar.repaint();
                    chart_bar.requestPaint();
                }
            }
        }

    }
    QChart {
        id: chart_bar;
        width: parent.width;
        height: parent.height-4;
        anchors.bottom:parent.bottom
        anchors.bottomMargin: 5
        chartAnimated: true;
        chartAnimationEasing: Easing.OutBounce;
        chartAnimationDuration: 2000;
        chartData: ChartsData.ChartBarData;
        chartType: Charts.ChartType.BAR;
    }
    //Chart 数据由QChartGallery.js提供

}
